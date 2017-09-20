#define C_PAD 0
#define C_FIRST 1
#define C_LAST 2
#define C_COMMENT 3
#define C_DICT 4
#define C_MODULE 5
#define C_ENTRYPT 6
#define C_SIZE 7
#define C_CONTENTS 8
#define C_REF 9
#define C_COMPREF 10


/* DATA STRUCTURES */

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned long ulong;
typedef unsigned short id;


/* Ugh! */
#ifndef __GNUC__
#define ntohs
#define ntohl
#define htons
#define htonl
#endif
#define NULL 0


ushort shortfrom(char *b)
{
	return ntohs(*(ushort *)b);
}

void setshort(char *b, ushort to)
{
	*(ushort *)b = htons(to);
}

ulong longfrom(char *b)
{
	return ntohl(*(ulong *)b);
}

void setlong(char *b, ulong to)
{
	*(ulong *)b = htonl(to);
}



/* Wraps an MPW Object buffer */
struct obj
{
	char *buf, *at;
	id next_id;
};


/* PASCAL STRING COMPARISON, CASE-INSENSITIVE */

int cisc(uchar *a, uchar *b)
{
	int i;

	if(*a != *b) return 0;

	for(i=1; i<=*a; i++)
	{
		uchar c, d;
		c = a[i];
		d = b[i];
		// if(c >= 'a' && c <= 'z') c &= 223;
		// if(d >= 'a' && d <= 'z') d &= 223;
		if(c == d) continue;
		return 0;
	}
	return 1;
}

void upperpas(uchar *a)
{
	int i;

	for(i=1; i<=*a; i++)
	{
		if(a[i] >= 'a' && a[i] <= 'z') a[i] &= 223;
	}
}


/* ACCESSOR FUNCTIONS */

/* Valid for all types */
char obj_type(struct obj *o)
{
	return o->at[0];
}

/* Valid for First, Dict, Module, EntryPt, Size, Contents, Ref, CompRef */
char obj_flags(struct obj *o)
{
	return o->at[1];
}

/* Valid for Module, EntryPt */
id obj_id(struct obj *o)
{
	return ntohs(*(id *)(o->at + 2));
}

/* Valid for Dict */
id obj_dictfirst(struct obj *o)
{
	return ntohs(*(id *)(o->at + 4));
}

/* Valid for Comment, Dict, Contents, Ref, CompRef */
unsigned short obj_recsize(struct obj *o)
{
	return ntohs(*(unsigned short *)(o->at + 2));
}

/* Valid for Size */
unsigned short obj_contsize(struct obj *o)
{
	return ntohs(*(unsigned long *)(o->at + 2));
}

/* Valid for all types */
unsigned long obj_size(struct obj *o)
{
	char t;

	t = obj_type(o);

	if(t == C_COMMENT || t == C_DICT || t == C_CONTENTS || t == C_REF || t == C_COMPREF)
	{
		return obj_recsize(o);
	}
	else if(t == C_PAD)
	{
		return 1;
	}
	else if(t == C_FIRST)
	{
		return 4;
	}
	else if(t == C_MODULE)
	{
		return 6;
	}
	else if(t == C_ENTRYPT)
	{
		return 8;
	}
	else if(t == C_SIZE)
	{
		return 6;
	}
	else if(t == C_LAST)
	{
		return 2;
	}
	else
	{
		printf("Illegal object type at offset 0x%x: %d\n", (ulong)o->at - (ulong)o->buf, t);
		return 1;
	}
}


/* CURSOR MANIPULATOR FUNCTIONS */

void obj_init(struct obj *o, char *buf)
{
	o->at = o->buf = buf;
}

void _obj_next_general(struct obj *o, int can_loop)
{
	if((long)o->at & 1) o->at ++;

	if(obj_type(o) == C_LAST)
	{
		//printf("Got a lastie\n");
		if(can_loop) o->at = o->buf;
	}
	else
	{
		//printf("Got a %d %d\n", obj_type(o), obj_size(o));
		o->at += obj_size(o);
	}

	if((long)o->at & 1) o->at ++;
}

/* Gets the next object without looping */
void obj_next(struct obj *o)
{
	_obj_next_general(o, 0);
}

/* Gets the specified module with looping */
void obj_findmod(struct obj *o, id mod_id)
{
	char *first;

	first = o->at;

	while(obj_type(o) != C_MODULE || obj_id(o) != mod_id)
	{
		_obj_next_general(o, 1);

		if(o->at == first)
		{
			o->at = o->buf;
		}
	}
}

/* Gets the next dict with looping */
void dict_next(struct obj *o)
{
	do
	{
		printf("xx %d\n", obj_type(o));
		_obj_next_general(o, 1);
	}
	while(obj_type(o) != C_DICT);
}

void obj_pad(struct obj *o)
{
	if((long)o->at & 1) *o->at++ = 0;
}

int obj_nextinmod(struct obj *o)
{
	char *at = o->at;

	if(obj_type(o) == C_LAST) return 0;

	_obj_next_general(o, 0);

	if(obj_type(o) == C_LAST || obj_type(o) == C_MODULE)
	{
		return 0;
		o->at = at;
	}

	return 1;
}

int obj_nextmod(struct obj *o)
{
	char *at = o->at;

	if(obj_type(o) == C_LAST) return 0;

	do
	{
		_obj_next_general(o, 0);
		if(obj_type(o) == C_LAST) return 0;
	} while(obj_type(o) != C_MODULE);

	return 1;
}



/* DICT APPEND FUNCTION */

void dict_append_v(struct obj *o, uchar *s, id hint_id)
{
	ushort oldlen;

	if(obj_type(o) != C_DICT || shortfrom(o->at + 2) > 10000)
	{
		obj_next(o);
		o->at[0] = C_DICT;
		o->at[1] = 0;						/* flags */
		setshort(o->at+2, 6);				/* size */
		setshort(o->at+4, hint_id);			/* first id */
	}

	oldlen = shortfrom(o->at + 2);

	o->at[oldlen+0] = *s + 5;
	o->at[oldlen+1] = '_';
	o->at[oldlen+2] = '_';
	o->at[oldlen+3] = 'v';
	o->at[oldlen+4] = '_';
	o->at[oldlen+5] = '_';

	memcpy(o->at + oldlen + 6, s + 1, *s);

	setshort(o->at + 2, oldlen + *s + 6);
}



/* DICT SEARCH FUNCTIONS, WHICH HAVE SIDE EFFECTS */

id dict_id_from_str(struct obj *o, unsigned char *str)
{
	char *first_searched = NULL;

	//printf("DICT %x: %.*s = \n", o, *str, str+1);

	for(;;)
	{
		if(obj_type(o) == C_DICT)
		{
			unsigned int ctr, tlen;
			unsigned char *ptr;

			tlen = ntohs(*(unsigned short *)(o->at + 2));
			ctr = ntohs(*(unsigned short *)(o->at + 4));
			ptr = (uchar *)((long)o->at + 6);

			do
			{
				//if(ptr[0] == str[0] && !memcmp(ptr+1, str+1, str[0]))
				if(cisc(ptr, str))
				{
					//printf("%d\n", ctr);
					return ctr;
				}

				ptr += ptr[0] + 1;
				ctr++;
			} while((ulong)ptr < (ulong)o->at + tlen);
		}

		_obj_next_general(o, 1);

		if(o->at == first_searched) return 0;
		if(!first_searched) first_searched = o->at;
	}

	//printf("(not found)\n");

	return 0;
}

uchar *dict_str_from_id(struct obj *o, id id)
{
	char *first_searched = NULL;

	//printf("DICT %x: %d = ", o, id);

	for(;;)
	{
		if(obj_type(o) == C_DICT)
		{
			unsigned int ctr, tlen;
			unsigned char *ptr;

			tlen = ntohs(*(unsigned short *)(o->at + 2));
			ctr = ntohs(*(unsigned short *)(o->at + 4));
			ptr = (uchar *)((long)o->at + 6);

			if(ctr <= id)
			{
				do
				{
					if(ctr == id) 
					{
						//printf("%.*s\n", *ptr, ptr+1);
						return ptr;
					}

					ptr += ptr[0] + 1;
					ctr++;
				} while((ulong)ptr < (ulong)o->at + tlen);
			}
		}

		_obj_next_general(o, 1);

		if(o->at == first_searched) return 0;
		if(!first_searched) first_searched = o->at;
	}

	//printf("(not found)\n");

	return NULL;
}

id dict_highestid(struct obj *o)
{
	id ctr;
	unsigned int tlen;
	unsigned char *ptr;

	tlen = ntohs(*(unsigned short *)(o->at + 2));
	ctr = (id)ntohs(*(unsigned short *)(o->at + 4));
	ptr = (uchar *)((long)o->at + 6);

	do
	{
		ptr += ptr[0] + 1;
		ctr++;
	} while((ulong)ptr < (ulong)o->at + tlen);

	return ctr - 1;
}



/* NEWDICT FUNCTIONS */

struct newdict
{
	struct newdict *prev, *next;			/* linked list */

	id new_id;								/* increments from 256 */
	id old_id;
	id patch_id;							/* if this ID is just vector glue and self.next is the implementation */
	uchar name[256];						/* duh */

	int defining_file;
	int malloc_size;						/* only for the main dict object */
	int fcnt;
	struct newdict ***cache;
	//id id_in_file[99];						/* malloc makes this array *just right* */
};

void newdict_init(struct newdict *d, int file_count)
{
	d->prev = d->next = d;
	d->new_id = 255;
	d->fcnt = file_count;
	d->malloc_size = sizeof *d; //sizeof(*d) + (file_count - 99) * sizeof(d->id_in_file[0]);
}

void newdict_cache(struct newdict *d)
{
	int i;
	struct newdict *s;

	d->cache = (struct newdict ***)calloc(d->fcnt, sizeof d->cache[0]);

	for(i=0; i<d->fcnt; i++)
	{
		d->cache[i] = (struct newdict **)calloc(65536, sizeof d->cache[0][0]);
	}

	for(s = d->next; s != d; s = s->next)
	{
		d->cache[s->defining_file][s->old_id] = s;
	}
}

id newdict_append(struct newdict *d, int file_idx, id orig_id, uchar *name)
{
	struct newdict *s;

	s = (struct newdict *)calloc(d->malloc_size, 1);
	if(!s)
	{
		return 0;
	}

	s->next = d;
	s->prev = d->prev;
	s->prev->next = s;
	d->prev = s;

	s->new_id = s->prev->new_id + 1;
	memcpy(s->name, name, name[0]+1);

	s->defining_file = file_idx;
	//s->id_in_file[file_idx] = orig_id;
	s->old_id = orig_id;

	return s->new_id;
}

struct newdict *newdict_find(struct newdict *d, int file_idx, id mid)
{
	// struct newdict *s;

	// for(s = d->next; s != d; s = s->next)
	// {
	// 	if(s->id_in_file[file_idx] == mid) return s;
	// }

	// return (struct newdict *)0;

	return d->cache[file_idx][mid];
}

// void newdict_debug_dump(struct newdict *d, char **file_names)
// {
// 	struct newdict *s;
// 	int i;

// 	printf("NEWDICT_DEBUG_DUMP\n");

// 	for(s = d->next; s != d; s = s->next)
// 	{
// 		printf("    %d %.*s", s->new_id, *s->name, s->name+1);

// 		if(s->defining_file != -1)
// 		{
// 			if(file_names)
// 			{
// 				printf(" (%s:%d)", file_names[s->defining_file], s->id_in_file[s->defining_file]);
// 			}
// 			else
// 			{
// 				printf(" (file_%d:%d)", s->defining_file, s->id_in_file[s->defining_file]);
// 			}
// 		}

// 		if(s->patch_id)
// 		{
// 			printf(" (patch ID %d, next line is implementation:)", s->patch_id);
// 		}

// 		printf("\n        %d:%d", s->defining_file, s->id_in_file[s->defining_file]);

// 		for(i=0; i<d->fcnt; i++)
// 		{
// 			if(i == s->defining_file) continue;
// 			if(!s->id_in_file[i]) continue;
// 			printf(" %d:%d", i, s->id_in_file[i]);
// 		}

// 		printf("\n");
// 	}
// }

unsigned long newdict_dump(struct newdict *d, char *o)
{
	unsigned long l = 0;
	struct newdict *s = d->next;

	while(s != d)
	{
		long tl = 0;

		o[l] = C_DICT;
		o[l+1] = 0;   /* 0 => names needed for code/data relocation.
		               1 => names needed for symbolic debugging only
		               (in which case they are ignored when doing a
		               non-symbolic link) */

		*(ushort *)(o + l + 4) = htons(s->new_id);

		tl = 6;

		while(s != d && tl < 10000)
		{
			memcpy(o + l + tl, s->name, s->name[0]+1);
			tl += s->name[0]+1;
			s = s->next;
		}

		/* doing the record! */
		*(id *)(o + l + 2) = htons(tl);

		if(tl & 1) o[l + tl++] = 0;

		l += tl;
	}

	return l;
}





// id newdict_lookup_backend(struct newdict *d, uchar *str, long major, long minor)
// {
// 	struct newdict *s;

// 	for(s = d->prev; s != d; s = s->prev)
// 	{
// 		if(major == -1 || minor == -1 || (s->major == major && s->minor == minor))
// 		{
// 			if(cisc(str, s->str))
// 			{
// 				return s->n;
// 			}
// 		}
// 	}

// 	return 0;
// }

// id newdict_id_from_str_with_hint(struct newdict *d, uchar *str, long major, long minor)
// {
// 	id id;

// 	id = newdict_lookup_backend(d, str, major, minor);
// 	if(id) return id;

// 	id = newdict_lookup_backend(d, str, -1, -1);
// 	if(id) return id;

// 	id = newdict_append(d, str, major, minor);
// 	return id;
// }



/* COMPLETE ODDBALL */

// void reref(char **dest, long major, struct newdict *destdict, struct obj *src, struct obj *srcdict, id specialfrom, id specialto)
// {
// 	const char OFFSETS[11][3] = {
// 		/* 0*/ {0},
// 		/* 1*/ {0},
// 		/* 2*/ {0},
// 		/* 3*/ {0},
// 		/* 4*/ {0},
// 		/* 5*/ {2,4,0},
// 		/* 6*/ {2,0},
// 		/* 7*/ {0},
// 		/* 8*/ {0},
// 		/* 9*/ {4,0},
// 		/*10*/ {4,6,0},
// 	};

// 	unsigned long len;
// 	char t;
// 	int i;

// 	len = obj_size(src);
// 	t = obj_type(src);

// 	memcpy(*dest, src->at, len);

// 	for(i=0; OFFSETS[t][i]; i++)
// 	{
// 		id is;

// 		is = ntohs(*(id *)(*dest + OFFSETS[t][i]));

// 		//printf("Converting: type %d offset %d original %d special %d->%d\n", t, OFFSETS[t][i], is, specialfrom, specialto);

// 		if(is == specialfrom)
// 		{
// 			is = specialto;
// 		}
// 		else
// 		{
// 			uchar *str = dict_str_from_id(srcdict, is);
// 			if(!str) printf("Bullshit string\n");
// 			//printf("... intermediate string %x %.*s\n", str, *str, str+1);
// 			is = newdict_id_from_str_with_hint(destdict, str, major, is);
// 		}

// 		//printf("... to %d\n", is);

// 		*(id *)(*dest + OFFSETS[t][i]) = htons(is);
// 	}

// 	*dest += len;

// 	if((long)(*dest) & 1) *(*dest)++ = 0;
// }


void obj_copy(struct obj *dest, struct obj *src)
{
	char *destthing;

	obj_next(dest);
	destthing = dest->at;

	memcpy(destthing, src->at, obj_size(src));

	obj_next(dest);
	obj_pad(dest);
	dest->at = destthing;
}

int obj_islastinmod(struct obj *o)
{
	struct obj j;
	char t;

	memcpy(&j, o, sizeof (struct obj));

	obj_next(&j);
	t = obj_type(&j);

	return t == C_MODULE || t == C_LAST;
}
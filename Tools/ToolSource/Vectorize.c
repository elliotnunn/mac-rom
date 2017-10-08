// This tool will be implemented using only standard C, the better 

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include "MPWObjFuncs.c"

#ifndef __GNUC__
#include <Finder.h>
#include <Files.h>
#endif

#define ERRSTR "# Vectorize Error: "
#define WARNSTR "# Vectorize Warning: "

// Default options

const char PASSIVE_OFFSETS[11][3] = {
	/* 0*/ {0},
	/* 1*/ {0},
	/* 2*/ {0},
	/* 3*/ {0},
	/* 4*/ {0},
	/* 5*/ {2,0},
	/* 6*/ {2,0},
	/* 7*/ {0},
	/* 8*/ {0},
	/* 9*/ {4,0},
	/*10*/ {4,6,0},
};

const char OFFSETS[11][3] = {
	/* 0*/ {0},
	/* 1*/ {0},
	/* 2*/ {0},
	/* 3*/ {0},
	/* 4*/ {4,0},
	/* 5*/ {2,4,0},
	/* 6*/ {2,0},
	/* 7*/ {0},
	/* 8*/ {0},
	/* 9*/ {4,0},
	/*10*/ {4,6,0},
};


int warnings = 1;
char *patchObjPath = NULL;
char *symFilePath = NULL;
int do_patch = 1;
char *outputObjPath = NULL;
char **inputPaths = NULL;
int inputCount = 0;

void to_pas(uchar *p, char *c)
{
	int sl = strlen(c);	
	p[0] = sl;
	memcpy(p+1, c, sl);
}

char *fname(char *x)
{
	char *y = x;

	while(*y) y++;

	while(y != x && y[-1] != ':') y--;

	return y;
}

char *slurp(char *path)
{
	FILE *f;
	long pos;
	char *bytes;

	f = fopen(path, "rb");
	if(f == NULL) return NULL;

	fseek(f, 0, SEEK_END);
	pos = ftell(f);
	fseek(f, 0, SEEK_SET);

	bytes = (char *)malloc(pos);
	if(bytes == NULL) return NULL;

	fread(bytes, pos, 1, f);

	fclose(f);

	return bytes;
}

int blat(char *path, char *buf, ulong len)
{
	FILE *f;

	f = fopen(path, "wb");
	if(f == NULL) return 1;

	fwrite(buf, len, 1, f);

	fclose(f);

	return 0;
}

void printUsage(char *cmdName)
{
	printf("USAGE: %s [-w] [-v PATCHES.o | -nopatch] [-log ROM.sym] -o ROM.lib INPUT1.o ...\n", cmdName);
}

int parseOpts(int argc, char **argv)
{
	int i;
	int err = 0;

	for(i=1; i<argc; i++)
	{
		if(!strcmp(argv[i], "-w"))
		{
			warnings = 0;
		}
		else if(!strcmp(argv[i], "-nopatch"))
		{
			do_patch = 0;
		}
		else if(!strcmp(argv[i], "-v"))
		{
			if(i == argc-1)
			{
				err = 1;
				break;
			}

			patchObjPath = argv[i+1];
			i++;
		}
		else if(!strcmp(argv[i], "-log"))
		{
			if(i == argc-1)
			{
				err = 1;
				break;
			}

			symFilePath = argv[i+1];
			i++;
		}
		else if(!strcmp(argv[i], "-o"))
		{
			if(i == argc-1)
			{
				err = 1;
				break;
			}

			outputObjPath = argv[i+1];
			i++;
		}
		else if(argv[i][0] == '-')
		{
			err = 2;
			break;
		}
		else
		{
			inputPaths = argv + i;
			inputCount = argc - i;
			break;
		}

	}

	// Report lexical errors (from the loop)
	if(err == 2)
	{
		fprintf(stderr, ERRSTR "%s is an unknown argument.", argv[i]);
	}
	else if(err == 1)
	{
		fprintf(stderr, ERRSTR "%s cannot be the last argument.", argv[i]);
	}
	
	// Check for semantic errors (basic sanity checks)
	if(!err)
	{
		if(do_patch && patchObjPath == NULL)
		{
			fprintf(stderr, ERRSTR "An MPW object containing patches must be specified with -v, unless -nopatch is used.\n");
			err = 3;
		}

		if(outputObjPath == NULL)
		{
			fprintf(stderr, ERRSTR "An output file must be specified with -o.\n");
			err = 3;
		}

		if(inputCount == 0)
		{
			fprintf(stderr, ERRSTR "At least one input file must be specified.\n");
			err = 3;
		}
	}

	if(err)
	{
		printUsage(argv[0]);
	}

	return err;
}


struct tblent
{
	uchar *name; /* without __v__ */
	char *data;
	long len;
	id __v__id;
	id clean_id;
	long offset_of_parent_in_module; /* bit of a hack, for sorting the patchstack */
};


int pstrcmp(const void *aa, const void *bb)
{
	const unsigned char *a = (const unsigned char *)aa;
	const unsigned char *b = (const unsigned char *)bb;


	int cl = *a;
	int r;
	if(*b < cl) cl = *b;

	//printf("Comparing %.*s to %.*s\n", *a, a+1, *b, b+1);

	r = memcmp(a+1, b+1, cl);

	if(r) return r;

	if(*b > *a) return -1;

	if(*b < *a) return 1;

	return 0;
}

int tblcmp(const void *a, const void *b)
{
	return pstrcmp(((struct tblent *)a)->name, ((struct tblent *)b)->name);
}

int ptch_order_cmp(const void *aa, const void *bb)
{
	long a = (**(struct tblent **)aa).offset_of_parent_in_module;
	long b = (**(struct tblent **)bb).offset_of_parent_in_module;

	if(a > b) return -1;
	if(a < b) return 1;
	return 0;
}

// int tblcmp2(const void *a, const void *b)
// {
// 	int res;
// 	printf("Comparing %.*s to %.*s", *((struct tblent *)a)->name, ((struct tblent *)a)->name+1, *((struct tblent *)b)->name, ((struct tblent *)b)->name+1);
// 	res = pstrcmp(((struct tblent *)a)->name, ((struct tblent *)b)->name);
// 	if(!res) printf(" ...match!");
// 	printf("\n");
// 	return res;
// }


// void print_tbl(struct tblent *tbl, long cnt)
// {
// 	long i;

// 	for(i=0; i<cnt; i++)
// 	{
// 		printf("%05d = %.*s\n", tbl[i].id, *(tbl[i].name), (tbl[i].name)+1);
// 	}
// }


void debug_print_about_patch(FILE *l, char *data, long len)
{
	int reg;
	unsigned short vtbl, voff;

	if(!data)
	{
		reg = -1;
	}
	else if(len != 10)
	{
		reg = -2;
	}
	else if(data[0] == 0x2f && data[1] == 0x30 && (uchar)data[2] == 0x81 && (uchar)data[3] == 0xe2 && data[8] == 0x4e && data[9] == 0x75)
	{
		reg = 7;
		vtbl = shortfrom(data + 4);
		voff = shortfrom(data + 6);
	}
	else if(data[0] == 0x22 && data[4] == 0x22 && data[8] == 0x4e) /* dirty shortcut */
	{
		reg = data[9] & 7;
		vtbl = shortfrom(data + 2);
		voff = shortfrom(data + 6);
	}
	else
	{
		reg = -2;
	}

	if(reg == -2)
	{
		fprintf(l, "UNKNOWN %db PATCH", len);
	}
	else if(reg == -1)
	{
		fprintf(l, "no patch");
	}
	else
	{
		fprintf(l, "patch $%04x,$%04x,A%d", vtbl, voff, reg);
	}
}


int main(int argc, char **argv)
{
	struct obj dest;
	struct tblent *tbl;
	long tblcnt = 0;
	int delta;
	int file_i;
	FILE *l = NULL; /* log file */
	int isfirst = 1;



	/* GET OUR COMMAND LINE */
	if(parseOpts(argc, argv)) return 1;

	if(NULL != symFilePath)
	{
		l = fopen(symFilePath, "w");
		if(!l)
		{
			fprintf(stderr, ERRSTR "Failed to open sym file %s\n", symFilePath);
			return 1;
		}
	}

	if(l)
	{
		fprintf(l, "      #     # #######  #####  ####### ####### ######  ### ####### ####### \n");
		fprintf(l, "      #     # #       #     #    #    #     # #     #  #       #  #       \n");
		fprintf(l, "      #     # #       #          #    #     # #     #  #      #   #       \n");
		fprintf(l, "      #     # #####   #          #    #     # ######   #     #    #####   \n");
		fprintf(l, "       #   #  #       #          #    #     # #   #    #    #     #       \n");
		fprintf(l, "        # #   #       #     #    #    #     # #    #   #   #      #       \n");
		fprintf(l, "         #    #######  #####     #    ####### #     # ### ####### ####### \n");
		fprintf(l, "\n");
		fprintf(l, "# This log file is formatted as an MPW worksheet, to help you troubleshoot\n");
		fprintf(l, "# your build.\n");
		fprintf(l, "\n");
		fprintf(l, "# (Fake)Vectorize attempts to replace a lost Apple build tool. It is mostly\n");
		fprintf(l, "# based on patent US5546586, \"Method and apparatus for vectorizing the contents\n");
		fprintf(l, "# of a read only memory device without modifying underlying source code\".\n");

		fprintf(l, "\n");

		if(do_patch)
		{
			fprintf(l, "# Dump the input file containing \"vector patches\":\n");
			fprintf(l, "  Set PatchDump \"{TempFolder}VectorPatchDump\"; DumpObj \"%s\" > \"{PatchDump}\"\n\n", patchObjPath);
			fprintf(l, "  # and navigate its contents:\n");
			fprintf(l, "    Find /NAVIGATE PATCHES/ \"{Active}\"\n");

			fprintf(l, "\n");
		}

		fprintf(l, "# Dump the \"vectorized\" output file: (takes a while)\n");
		fprintf(l, "  Set RomDump \"{TempFolder}VectorRomDump\"; DumpObj \"%s\" > \"{RomDump}\"\n", outputObjPath);
		fprintf(l, "\n");
		fprintf(l, "  # and look at it:\n");
		fprintf(l, "    File \"{RomDump}\"\n");
		fprintf(l, "\n");
		fprintf(l, "  # or navigate it input-file-wise:\n");
		fprintf(l, "    Find /NAVIGATE OUTPUT/ \"{Active}\"\n");
		for(file_i=0; file_i<inputCount; file_i++)
		{
			fprintf(l, "      Find /¶\"%s¶\"/ \"{Active}\"\n", inputPaths[file_i]);
		}

		fprintf(l, "\n");
	}

	dest.buf = dest.at = calloc(0x400000, 1);
	if(!dest.buf)
	{
		fprintf(stderr, ERRSTR "Failed to calloc 4MB dest buffer\n");
		return 1;
	}

	/* Create a First record (remember that MPW objects are fully ascending) */
	dest.at[0] = 1;
	dest.at[1] = 1;
	dest.at[2] = 0;
	dest.at[3] = 2;

	if(do_patch)			/* PROCESS THE PATCH FILE (and keep it around because we use it for strings) */
	{
		char *patch_bin;
		struct obj patch_obj, patch_dict;

		patch_bin = slurp(patchObjPath);
		if(!patch_bin)
		{
			fprintf(stderr, ERRSTR "Failed to slurp patch file\n");
			return 2;
		}

		tbl = (struct tblent *)calloc(5000, sizeof (struct tblent));
		if(!tbl)
		{
			fprintf(stderr, ERRSTR "Failed to malloc tbl\n");
			return 3;
		}

		if(l) fprintf(l, "#############################  NAVIGATE PATCHES  #############################\n");
		if(l) fprintf(l, "# (These command lines are a bit clumsy. Oh well...)\n\n");

		obj_init(&patch_obj, patch_bin);
		obj_init(&patch_dict, patch_bin);

		while(obj_nextmod(&patch_obj))
		{
			struct obj scratch;

			uchar *name;
			char *data = NULL;
			long len = 0;
			id __v__id;


			memcpy(&scratch, &patch_obj, sizeof (struct obj));		/* find the module's Size record */

			while(obj_nextinmod(&scratch))
			{
				if(obj_type(&scratch) == C_SIZE)
				{
					len = obj_contsize(&scratch);
					break;
				}
			}


			if(len)
			{
				memcpy(&scratch, &patch_obj, sizeof (struct obj));	/* find the module's Contents record (hopefully only one) */

				while(obj_nextinmod(&scratch))
				{
					if(obj_type(&scratch) == C_CONTENTS)
					{
						data = scratch.at + 4;						/* actual data starts 4 bytes into Contents record */
						if(obj_flags(&scratch) & 8) data += 4;		/* unless the offset or repeat fields are flagged as present */
						if(obj_flags(&scratch) & 16) data += 2;

						if(scratch.at + obj_recsize(&scratch) != data + len)
						{
							fprintf(stderr, ERRSTR "Patch file contains module with size/contents mismatch\n");
							return 1;
						}

						break;
					}
				}

				if(!data)
				{
					fprintf(stderr, ERRSTR "Patch file contains module with nonzero Size but no Contents\n");
					return 1;
				}
			}


			name = dict_str_from_id(&patch_dict, obj_id(&patch_obj));
			if(!name)
			{
				fprintf(stderr, ERRSTR "Patch module with unlisted ID\n");
				return 1;
			}


			__v__id = tblcnt + 1;

			dict_append_v(&dest, name, __v__id);					/* create a "__v__" dict id for the code that this patch will hide */
																	/* 1 dict append to 1 tbl append (dict ID = tbl index + 1) */

			tbl[tblcnt].name = name;
			tbl[tblcnt].data = data;
			tbl[tblcnt].len = len;
			tbl[tblcnt].clean_id = 0;
			tbl[tblcnt].__v__id = __v__id;							/* equals ID assigned just above */


			if(l) fprintf(l, "File \"{PatchDump}\"; Line 0; File \"{PatchDump}\"; Find /Module=¶\"%.*s¶\"/ # ", *name, name+1);
			if(l) debug_print_about_patch(l, data, len);			/* log some MPW code that can show the user this routine's disasm */
			if(l) fprintf(l, "\n");

			tblcnt ++;
		}

		obj_pad(&dest);

		/* The most important part: create a name-searchable table of vector glue code */
		qsort((void *)tbl, tblcnt, sizeof (struct tblent), tblcmp);

		if(l) fprintf(l, "\n");
	}

	delta = tblcnt + 1;


	if(l) fprintf(l, "##############################  NAVIGATE OUTPUT  #############################\n\n");

	for(file_i=0; file_i<inputCount; file_i++)
	{
		char *cur_bin;
		struct obj cur_obj, cur_dict;

		char *mod_copy_start = NULL;				/* dest's copy of this module record */
		char *mod_copy_last = NULL;					/* dest's copy of the last record in this module (not including new patches) */
		char *mod_sizeobj = NULL;					/* dest's copy of this module's size record, for offsetting any patches */

		struct tblent *patchstack[512];
		int patchcnt = 0;

		id nextdelta = delta + 1;



		cur_bin = slurp(inputPaths[file_i]);
		if(!cur_bin)
		{
			fprintf(stderr, ERRSTR "Failed to slurp input file %s\n", inputPaths[file_i]);
			return 4;
		}

		if(l) fprintf(l, "# \"%s\"\n", inputPaths[file_i]);
		if(l) fprintf(l, "   Find /Åjump to next fileÅ/ \"{Active}\"\n\n");

		obj_init(&cur_obj, cur_bin);
		obj_init(&cur_dict, cur_bin);

		//fprintf(stderr, "Delta is %d for %s\n", delta, inputPaths[file_i]);


		/* done slurping */


		for(obj_next(&cur_obj); obj_type(&cur_obj) != C_LAST; obj_next(&cur_obj))			/* for each RECORD in the file (excluding First + Last) */
		{
			char t = obj_type(&cur_obj);
			int i;

			obj_copy(&dest, &cur_obj);							/* COPY THE RECORD STRAIGHT IN (BRAVE!) */

			mod_copy_last = dest.at;

			/* do (some of) the renumbering here, i guess */
			for(i=0; OFFSETS[t][i]; i++)
			{
				id is;
				is = shortfrom(dest.at + OFFSETS[t][i]);
				setshort(dest.at + OFFSETS[t][i], is + delta);
			}


			if(t == C_MODULE)
			{
				mod_copy_start = dest.at;
				mod_sizeobj = NULL;

				dest.at[1] |= 1<<7; // force active
			}

			if(t == C_DICT)
			{
				id hid = dict_highestid(&dest);
				if(hid > nextdelta) nextdelta = hid;
			}

			if(t == C_SIZE)
			{
				mod_sizeobj = dest.at;
			}

			if(t == C_MODULE || t == C_ENTRYPT)
			{
				struct tblent fodder_for_bsearch, *ent;
				uchar *my_name;
				char *patch_mod = NULL;
				int is_vectorized = 0;

				my_name = dict_str_from_id(&cur_dict, obj_id(&cur_obj));

				if(!my_name)
				{
					fprintf(stderr, ERRSTR "Module with unlisted ID\n");
					return 1;
				}

				fodder_for_bsearch.name = my_name;
				ent = (struct tblent *)bsearch(&fodder_for_bsearch, tbl, tblcnt, sizeof (struct tblent), tblcmp);

				if(ent)											/* there is a patch module, but it may be zero-size! */
				{
					if(ent->data && ent->len)
					{
						ent->clean_id = obj_id(&dest);
						patchstack[patchcnt++] = ent;
						is_vectorized = 1;

						if(t == C_MODULE)
						{
							ent->offset_of_parent_in_module = 0;
						}
						else
						{
							ent->offset_of_parent_in_module = longfrom(dest.at+4);
						}
					}
				}
				else
				{
					if(warnings)
					{
						fprintf(stderr, WARNSTR "Missing vector patch: %.*s\n", *my_name, my_name+1);
					}
				}

				if(l)
				{
					if(t == C_MODULE)
					{
						fprintf(l, "File \"{RomDump}\"; Line 0; File \"{RomDump}\"; Find /Module=¶\"");
					}
					else
					{
						fprintf(l, "  File \"{RomDump}\"; Line 0; File \"{RomDump}\"; Find /Entry=¶\"");
					}

					if(is_vectorized) fprintf(l, "__v__");

					fprintf(l, "%.*s¶\"/ # ID %d", *my_name, my_name+1, is_vectorized ? ent->__v__id : obj_id(&dest));

					if(t == C_ENTRYPT)
					{
						fprintf(l, ", offset $%x", longfrom(dest.at+4));
					}

					fprintf(l, "\n");
				}
			}

			if(mod_copy_start && obj_islastinmod(&cur_obj))		/* empty the patchstack */
			{
				int pi;

				// qsort((void *)patchstack, patchcnt, sizeof (struct tblent *), ptch_order_cmp);

				for(pi=0; pi<patchcnt; pi++)
				{
					struct obj scratch;
					long original_size;
					uchar *my_name;

					my_name = patchstack[pi]->name;

					original_size = longfrom(mod_sizeobj + 2);
					if(original_size & 1) original_size ++;		/* even-align the patches -- found this bug while reversing QuickDraw */

					if(l) fprintf(l, "    File \"{RomDump}\"; Line 0; File \"{RomDump}\"; Find /Entry=¶\"%.*s¶\"/ # patch ID %d, ", *my_name, my_name+1, patchstack[pi]->clean_id);
					if(l) debug_print_about_patch(l, patchstack[pi]->data, patchstack[pi]->len);
					if(l) fprintf(l, ", offset $%x\n", original_size);

					obj_next(&dest);															/* EXTRA RECORD: CONTENTS */
					dest.at[0] = C_CONTENTS;														/* type */
					dest.at[1] = 8;																	/* offset field present */
					setshort(dest.at + 2, 8 + patchstack[pi]->len);									/* size = 8b header, plus data */
					setlong(dest.at + 4, original_size);											/* offset = end of module data so far */
					memcpy(dest.at + 8, patchstack[pi]->data, patchstack[pi]->len);					/* actual, you know, *contents* */

					obj_next(&dest);															/* EXTRA RECORD: ENTRY POINT (of patch) */
					dest.at[0] = C_ENTRYPT;															/* type */
					dest.at[1] = 8;																	/* external entry point */
					setshort(dest.at + 2, patchstack[pi]->clean_id);								/* ID */
					setlong(dest.at + 4, original_size);											/* offset = end of module data so far */

					/* Increment the size of this module */
					setlong(mod_sizeobj + 2, original_size + patchstack[pi]->len);


					/* Now do the dirty work of changing self-references to use __v__... */

					for(scratch.at=mod_copy_start; scratch.at<=mod_copy_last; obj_next(&scratch))
					{
						char tt = obj_type(&scratch);

						for(i=0; PASSIVE_OFFSETS[tt][i]; i++)
						{
							id is = shortfrom(scratch.at + PASSIVE_OFFSETS[tt][i]);
							if(is == patchstack[pi]->clean_id)
							{
								setshort(scratch.at + PASSIVE_OFFSETS[tt][i], patchstack[pi]->__v__id);
							}
						}
					}
				} /* patchstack loop */

				if(l) fprintf(l, "\n");			/* newline before each module... nice touch */

				patchcnt = 0;
			} /* do patchstack or not? */
		} /* for each record */

		free(cur_bin);
		//fprintf(stderr, "Culminating in %d\n", nextdelta);
		delta = nextdelta + 1;

		// delta += 5000;
		// delta -= (delta % 5000);
	}

	obj_next(&dest);
	dest.at[0] = C_LAST;
	dest.at[1] = 0;

	if(blat(outputObjPath, dest.buf, (long)(dest.at) - (long)(dest.buf) + 2))
	{
		fprintf(stderr, ERRSTR "Failed to write output file\n");
		return 5;
	}
	
	if(l) fclose(l);
	
	#ifndef __GNUC__
	{
		FInfo fi;
		Str255 pas;
		int e;
		
		to_pas(pas, outputObjPath);
		
		e = GetFInfo(pas, 0, &fi);
		if (e == 0)
		{
			fi.fdType = 0x4F424A20;		/* TEXT */
			fi.fdCreator = 0x4D505320;	/* MPS  */
			e = SetFInfo(pas, 0, &fi);
		}
		
		if(symFilePath)
		{
			to_pas(pas, symFilePath);
			
			e = GetFInfo(pas, 0, &fi);
			if (e == 0)
			{
				fi.fdType = 0x54455854;		/* TEXT */
				fi.fdCreator = 0x4D505320;	/* MPS  */
				e = SetFInfo(pas, 0, &fi);
			}
		}
	}
	#endif

	return 0;
}

/* I interpret the "RomLink" bytecode. My "programs" are resources. */

#include <stdio.h>
#include <Memory.h>
#include <Resources.h>
#include <Finder.h>
#include <Files.h>

// Symbolic constants for ROMLink opcodes.
#define __RL_OP_CSTRING              0x80
#define __RL_OP_INCLUDE              0x81
#define __RL_OP_BEGIN                0x82
#define __RL_OP_END                  0x83
#define __RL_OP_BLOCKSIZE            0x84
#define __RL_OP_ROMLENGTH            0x86
#define __RL_OP_ROMCRC               0x87
#define __RL_OP_TREESIZE             0x88
#define __RL_OP_ALIGN                0x89
#define __RL_OP_ANCHOR               0x8a
#define __RL_OP_KEY                  0xfe
#define __RL_OP_COMMENT              0xff

// Symbolic constants for ROMLink resource pattern selectors.
#define __RL_SEL_FILENAME             1
#define __RL_SEL_NAME                 2
#define __RL_SEL_TYPE                 3
#define __RL_SEL_ID                   4
#define __RL_SEL_LOCAL                5


/* GLOBALS used by get_program and free_program */

char blergh[] = "nodeformxfrmcstrlongstypexecpinisinivdevpramvmnalistspdrsdirboarsrscddirgdirvdirvendvmod";
ResType *global_type_list;
long global_type_count;


void to_pas(unsigned char *p, char *c)
{
	int sl = strlen(c);
	p[0] = sl;
	memcpy(p+1, c, sl);
}


void get_program(unsigned char **prog_p, long *len_p, unsigned char *name)
{
	long i;
	Handle hdl = NULL;

	for(i=0; i<global_type_count; i++)
	{
		hdl = GetNamedResource(global_type_list[i], name);
		if(hdl) break;
	}

	if(!hdl)
	{
		*prog_p = NULL;
		*len_p = 0;
		fprintf(stderr, "Could not find program \"%.*s\"\n", *name, name+1);
	}

	MoveHHi(hdl);
	HLock(hdl);

	*prog_p = *(unsigned char **)hdl;
	*len_p = GetHandleSize(hdl);
}


void free_program(unsigned char *prog)
{
	Handle hdl = RecoverHandle((Ptr)prog);
	HUnlock(hdl);
	DisposeHandle(hdl);
}


int do_program(unsigned char *const middle, unsigned char *program, long prog_len, long *leftlenp, long *rightlenp)
{
	unsigned char *prog_base = program;

	unsigned char *left = middle;
	unsigned char *right = middle;

	unsigned char *real_left, *fake_middle, *real_right;

	unsigned char offset_field_bytes;

	unsigned long *put_len_here = NULL;
	unsigned long *put_crc_here = NULL;

	//printf("do_program middle=0x%x program=0x%x prog_len=0x%x\n", middle, program, prog_len);

	while(program < prog_base + prog_len)
	{
		unsigned char opcode = *program++;

		if(127 >= opcode)
		{
			memcpy(right, program, opcode);
			right += opcode;
			program += opcode;
		}

		else if(__RL_OP_CSTRING == opcode)
		{
			long len_with_nul = strlen(program) + 1;

			memcpy(right, program, len_with_nul);
			right += len_with_nul;
			program += len_with_nul;

			if(len_with_nul & 1)
			{
				*right++ = 0;
			}
		}

		else if(__RL_OP_INCLUDE == opcode)
		{
			unsigned char selector;
			unsigned char *res_name_pstr = NULL;
			unsigned char *other_prog;
			long other_prog_len;

			long used_leftlen, used_rightlen;

			int result;

			while((selector = *program++) != 0)
			{
				if(selector == __RL_SEL_NAME)
				{
					res_name_pstr = program;
					program += *program + 1;
				}
			}

			if(!res_name_pstr) { fprintf(stderr, "INCLUDE opcode with unimplemented resource pattern selector\n"); return 1; }

			get_program(&other_prog, &other_prog_len, res_name_pstr);

			if(!other_prog) return 1;

			result = do_program(right, other_prog, other_prog_len, &used_leftlen, &used_rightlen);
			free_program(other_prog);
			if(result) return result;

			if(left != right && used_leftlen) { fprintf(stderr, "Overwrote to the left!\n"); return 1; }

			left = right - used_leftlen;
			right = right + used_rightlen;
		}

		else if(__RL_OP_BEGIN == opcode)
		{
			offset_field_bytes = *program++ / 8;	/* how many bytes this is going to use */

			real_left = left;						/* for when we return to our senses */
			real_right = right;

			left = right = fake_middle = left - 0x1000;		/* off to lala land, with 4k of room */
		}

		else if(__RL_OP_END == opcode)
		{
			long newstufflen = right - left;
			long offset;

			if(right > real_left) { fprintf(stderr, "Ran out of breathing room!\n"); return 1; }

			real_left -= newstufflen;					/* my left including new stuff */
			fake_middle += real_left - left;			/* the middle of the new stuff */
			memmove(real_left, left, newstufflen);

			left = real_left;							/* get out of lala land */
			right = real_right;

			offset = fake_middle - right;
			if((long)right & 1) offset += 1;			/* pretend this field is long-aligned */

			memcpy(right, (char *)(&offset) + 4 - offset_field_bytes, offset_field_bytes);
			//printf("%08x\n", offset);

			right += offset_field_bytes;

			offset_field_bytes = 0;
		}

		else if(__RL_OP_BLOCKSIZE == opcode)
		{
			fprintf(stderr, "BLOCKSIZE not implemented\n"); return 1;
		}

		else if(__RL_OP_ROMLENGTH == opcode)
		{
			put_len_here = (unsigned long *)right;
			right += 4;
		}

		else if(__RL_OP_ROMCRC == opcode)
		{
			put_crc_here = (unsigned long *)right;
			right += 4;
		}

		else if(__RL_OP_TREESIZE == opcode)
		{
			fprintf(stderr, "TREESIZE not implemented\n"); return 1;
		}

		else if(__RL_OP_ALIGN == opcode)
		{
			unsigned char align = *program++;

			while((unsigned long)right % align)
			{
				*right++ = 0;
			}
		}

		else if(__RL_OP_ANCHOR == opcode)
		{
			fprintf(stderr, "ANCHOR not implemented\n"); return 1;
		}

		else if(__RL_OP_KEY == opcode)
		{
			unsigned char key = *program++;				/* nop */
		}

		else if(__RL_OP_COMMENT == opcode)
		{
			fprintf(stderr, "COMMENT not implemented\n"); return 1;
		}

		else
		{
			fprintf(stderr, "Unknown opcode %d\n", opcode); return 1;
		}
	}

	if(put_len_here) *put_len_here = right - left;

	if(put_crc_here)
	{
		unsigned char *ptr;
		unsigned long sum;

		*put_crc_here = 0;

		sum = 0;
		ptr = left;

		for(ptr=left; ptr<right; ptr++)
		{
			sum = (sum << 1) | (sum >> 31);
			sum += *ptr;
		}

		*put_crc_here = sum;
	}

	*leftlenp = middle - left;
	*rightlenp = right - middle;

	return 0;
}


int main(int argc, char **argv)
{
	int print_usage = 0;

	short *refnum_list;
	int refnum_count = 0;
	short refnum;
	Str255 pas;

	char *outfile = NULL;

	unsigned char *buf, *middle;

	unsigned char *prog;
	long prog_len;

	int result;

	long used_left, used_right;

	long i;

	short err;

	FInfo fi;
	FILE *f;
	long writesize, writtensize;

	global_type_list = (ResType *)blergh;
	global_type_count = 22;

	refnum_list = (short *)calloc(argc, sizeof *refnum_list);
	if(!refnum_list)
	{ fprintf(stderr, "%s: extreme memory pressure. Quitting.\n", argv[0]); return 1; }

	for(i=1; i<argc; i++)
	{
		if(!strcmp("-o", argv[i]))
		{
			if(i == argc - 1)
			{
				print_usage = 1;
				break;
			}

			outfile = argv[++i];
		}
		else
		{
			to_pas(pas, argv[i]);

			refnum = OpenResFile(pas);
			if(refnum <= 0)
			{ fprintf(stderr, "%s: Failed to open %s\n", argv[0], argv[i]); return 1; }

			refnum_list[refnum_count++] = refnum;
		}
	}

	if(!outfile) print_usage = 1;
	if(!refnum_count) print_usage = 1;

	if(print_usage) { fprintf(stderr, "USAGE: %s -o OUT FILE [...]\n", argv[0]); return 1; }

	to_pas(pas, "Root");
	get_program(&prog, &prog_len, pas);

	if(!prog) { fprintf(stderr, "%s: could not get Root program\n", argv[0]); return 1; }

	buf = (unsigned char *)calloc(1, 0x40000);
	middle = buf + 0x38000;

	if(!buf) { fprintf(stderr, "%s: serious memory pressure. Quitting.\n", argv[0]); return 1; }

	result = do_program(middle, prog, prog_len, &used_left, &used_right);
	free_program(prog);
	if(result) return result;


	while(refnum_count) CloseResFile(refnum_list[--refnum_count]);


	/* WRITEOUT */

	writesize = used_left + used_right;


	f = fopen(outfile, "wb");

	if(!f) { fprintf(stderr, "%s: could not open for output %s\n", argv[0], outfile); return 1; }


	writtensize = fwrite(middle - used_left, 1, writesize, f);

	if(writtensize != writesize) { fprintf(stderr, "%s: could not write\n", argv[0]); return 1; }


	free(buf);
	fclose(f);


	to_pas(pas, outfile);
	err = GetFInfo(pas, 0, &fi);
	if(!err)
	{
		fi.fdType = 0x6465636C;    /*decl -- so nothing else tries to mess with it!*/
		fi.fdCreator = 0x6465636C; /*decl*/
		err = SetFInfo(pas, 0, &fi);
	}


	return 0;
}

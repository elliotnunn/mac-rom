/*
	File:		Hiram.c

	Contains:	Source to MPW tool that converts linker output into a ROM image.

	Written by:	J. T. Coonen

	Copyright:	© 1985-1990, 1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM6>	10/18/92	CCH		Bumped block size for interleaved writes to 2MB to make writes
									fast.
	   <SM5>	 6/16/92	CS		(RB) Include TextUtils.h to comply with new interface files.
	   <SM4>	 5/29/92	RB		Modified output of ROM statistics to also show sizes in K bytes.
		 <3>	 3/26/92	JSM		OSEvents.h is obsolete, use Events.h only. Update copyright to
									1992. Rolled this version of the file into Reality.
		 <2>	 2/11/92	RB		Need to check in version 4 of Hiram from the Zydeco project to
									fully support 2 Meg ROMs. Included String, Strings and
									StdLib.h's Changed variable name Alignment to gAlignment to
									avoid a conflict. Added prototypes.
		ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
			  Pre Super Mario ROM comments begin here.
		ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
			<4>	12/02/91	jmp		Changed references to GetResource to Get1Resource to fix a
									problem with various System Extensions that patch things like
									the standard WDEFs, CDEFs, MBDFs, etcÉ.
		 <3>	11/11/91	BG		Added a local -long- variable and copied *rsrcID* to it, then
									passed the long to -sprintf()- since passing negative -short-
									values to it causes it to print the unsigned value under MPW3.2.
		 <2>	10/25/91	jmp		Checking in SamÕs changes from Horror into Zydeco-TERROR.
		 <1>	10/23/91	SAM		Reformatted all of the screen output so that it agrees with the
									rest of the build status strings.  Recompiled under MPW 3.2.
									Bumped version to d2.
		ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
			  Pre-Zydeco ROM comments begin here.
		ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ

		 <4>	 1/30/92	JSM		Cleanup header, update copyright to 1992, rename Alignment
									global to byteAlignment, include StdLib.h, String.h, and
									Strings.h and add more function prototypes to avoid warnings.
									This tool is now built and run from inside :Objects:ROM: as part
									of a normal ROM build.
		 <3>	 1/16/90	CCH		Removed extraneous header info.
		 <2>	 1/12/90	CCH		Version 3.21:  Updated copyright to 1990.
	   <2.4>	 7/25/89	CCH		Changes: 
	   									- Changed encryption algorithm slightly to make it less
										  obvious, and changed key to match Romulator v1.0.
	   <2.3>	 7/20/89	CCH		Changes: 
	   									- Added "-pd" option to make the forced date a pascal
										  date. 
										- Date should now be entered without "[]"'s surrounding
										  it.
	   <2.1>	 7/19/89	CCH		Changes: 
	   									- Added "-nd" option to supress inclusion of date in
										  ROM.
	   <2.2>	 7/19/89	CCH		Changes: 
	   									- Removed "-nd" option in favor of new "-fd" option to
										  force a date into the ROM.
	   <2.0>	  7/6/89	CCH		Changes: 
	   									- Added "-a" option to set alignment of resources. -
										  Fixed bug in AlignBelow macro.
	   <1.8>	 6/30/89	CCH		Changes: 
	   									- Modified to put ROM rsrc's at the end of ROM. 
										- Added a new reference entry field that gives an offset 
										  to the rsrc data for that entry.
	   <1.9>	 6/30/89	CCH		Changes: 
	   									- Fixed bug in "DeclData loaded at" output. 
										- Spiffed up output file.
	   <1.7>	 6/22/89	CCH		Changes: 
	   									- Redesigned how ROM resources are stored to accomodate
										  multiple-resources of the same type, ID, and name in the ROM.
										  Hiram reads a resource-list file to determine what resources are
										  loaded. This file also contains information about which
										  resources should be made available to the O/S at any one time,
										  and the filenames they are contained in. 
										  - Removed unmount and eject code
	   <1.6>	 5/12/89	CCH		Added encryption for RAM-based images, and sped up checksumming
									loop.
	   <1.5>	 4/11/89	CCH		Zeros out individual cksums before cksumming, and excludes first
									4 bytes from all checksumming. Added check for null initials
									handle (so it doesn't crash).
	   <1.4>	 3/17/89	CCH		Now stuffs ROMSize at RomBase+0x40. Added new "-o" option to
									generate slice file output. "-n" is now required unless ROM is
									one slice. Added Copyright notice along with initials at end of
									ROM.
	   <1.3>	  2/8/89	CCH		Stop generating ROM slice files unless specifically asked for
									with the "-n" option.
	   <1.2>	 1/25/89	CCH		Extensive modification to always compute slice checksums, and to
									halve the runtime memory requirements. Also added '-32' option
									to support 32-bit clean ROMs.
	   <1.1>	12/15/88	CCH		Changed "\r"'s to "\n"'s...
	   <1.0>	11/14/88	CCH		Adding to EASE. Fixed up error msgs to be more informative.
				  1/8/88	rwh		added support for multiple ROM overpatch files. Also made GWN's
									change to read in declaration data a command line option (-d).
				 2/16/87	bbm		changed output of rom totals to display in hex.
				  2/4/87	bbm		made resources and map long word go on long word boundries.
				11/11/86	JTC		Force 0 pad byte for odd-sized resources.
	  <A250>	10/10/86	JTC		Clean up ROM rsrc map to have zero in fields of no <10Oct86>
									relevance, such as 16-byte duplicate of file header (various
									offsets and the like), the 4-byte handle to next map, and the
									pad byte for odd-sized maps.
				 8/28/86	JTC		Write new file ROMCat, the concatenation of the N files produced
									by -s and -b options. <28Aug86>
				  8/6/86	JTC		A little help for our friends in hardware: a option -b (for
									Brian(s)) is added to permit high and low options, each to be
									split into SLICES number of slices. How nice! The -b option will
									take no integer parameter. <06Aug86> Have high bytes take up
									ZeroImage, OneImage, etc. and have low bytes take NImage,
									(N+1)Image, etc.
				  6/2/86	JTC		Major rework for MPW, continuing 19Mar86 changes. Add
									<argc,argv> support (see comment below), watch for flushing of
									feedback in output window, and remove the old ROM: disk stuff,
									building the output files in the default directory. Some bugs in
									new use of FSxxx file system calls since some arguments must be
									passed by address. Oh, Pascal!
				 3/19/86	JTC		Moved from Consulair world, and correctly integrated Milwaukee
									changes. Among major changes: (1) use high-level file system
									calls; (2) parameterize ROM length and number of slices of ROM;
									(3) render time/date stuff in C.
				 1/27/86	JTC		A few quick file changes for Milwaukee.
				 1/16/86	bbm		added support for 8 byte master pointer.
				 10/6/85	JTC		Heavens, fixed for real this time!
				 10/4/85	JTC		Fix loop end for checksum.
				 8/26/85	JTC		Fix eject to use volume name. Change RSRC layout to remove bogus
									MP block from ROM, placing offsets to the RSRC data in the map
									(file offset slot) itself.
				 7/22/85	JTC		Fix bug in sizing ROM -- 8-byte header not added in! Also, allow
									at least one byte of date at end of ROM.
				 7/15/85	JTC		Leave ROM:ROMImageL on disk!
				  7/1/85	JTC		Added adjustable ROMSTART constant for non-Mac builds.
				 5/20/85	JTC		Make map refNum = 2.
				 5/15/85	JTC		Stuff ROM date into last bytes of ROM, with TRAILING length.
				 5/14/85	JTC		Finally got the COLON right in UnmountVol! The 'last' set of
									changes collects data into a summary file HiROMErr.TXT.
				 5/13/85	JTC		Eject and unmount after write.
				 5/11/85	JTC		BUG in checksum: accumulated words into long sum were
									sign-extended, a No-No.
				 4/11/85	JTC		Add conditional compilation to write either ROMImageH &
									ROMImageL or ROMImageEven & ROMImageODD
				 4/11/85	JTC		Modify to use Consulair OSIO.h definitions.
				 3/18/85	JTC		Modify HeapMagic constant for 4 master pointers in ROM zone,
									rather than DefaultMasters, as it was.
				 2/18/85	JTC		Revise block IO to use Mac routines directly, incorporating
									experimental structure definitions from jtCIODefs.h
				 2/12/85	JTC		Revise resources to put fake memory manager header in front of
									each resource. Mark it Relocatable+Nonrelocatable, with logical
									= phys size, and mp offset as though master pointers will be
									allocated first in system heap after first master pointer block.
				  2/9/85	JTC		Changed name of output file to ROMImageH. Look for file
									ROMImageL, and if found, concatenate the two to ROMMondo; else
									write one word of 0's to ROMMondo. Sleazy bum -- forcing volume
									name to be ROM:
				  2/1/85	JTC		Changed format of output image to begin with word map and mp
									block size. Set res attribute bits to 0x58: No sys ref / Sys
									heap / Not Purgeable / Locked / Protected / Not pre-loaded / Not
									changed / reserved Also, mark master pointers as locked.
				 1/22/85	JTC		Changed name of input file.

*/

/**************************************************************************
** FakeRomLayout -- adapted from hiram.c to emulate the lost RomLayout.
** "A program to build ROM images, complete with RSRCs and checksum."
** hiram.c by J. T. Coonen  18 Dec 84  --  last change 18 Oct 92
**
** MPW command line usage:											
**		RomLayout INPUT.rsrc -o OUTPUT -log LOGFILE [-mf] [-24]
** where:
**		-mf is a nop (probably enabled the use of Temporary Memory)
**		-24 makes the generated Memory Mgr headers 32-bit DIRTY
**
**
** The format of OUTPUT is:
**	0x000000				(long) checksum of entire ROM
**	0x000004				ROM code
**	0x00001A				(long) ResOff = offset to ROM resource structure table	<1.7>
**	0x00001E - 0x00002F		ROM code
**	0x000030 - 0x00003F		checksums for slices (zero for unused slices)
**	0x000040				ROM size								<1.4>
**	0x000044 - ResOff		ROM code
**
**	ResOff					ROM Resource Structure Table:
**	  long	offsetToFirst;		offset from base Of Rom to first rsrc Reference Entry in linked list
**	  char	maxValidIndex;		maximum value for PRAM combo index
**	  char	comboFieldSize;		size in bytes of combo field
**	  short	comboVersion;		version of combo field
**	  short	headerSize;			length of memory headers
**
**	RefEntry				ROM Resource Reference Entry:
**	  long	offsetToNext;		offset from base Of Rom to next ref entry in linked list
**	  long	offsetToData;		offset from base Of Rom to rsrc data for this entry
**	  long	rsrcType;			resource type
**	  short	rsrcID;				resource ID
**	  char	rsrcAttr;			resource attributes
**	  char	nameLen;			length of resource name
**	  char	rsrcName[];			resource name followed by longword aligned resource data
**
** The resource structure has the following amusing properties:
**
**	You can have resources with the same type and ID as long as they are not
**		members of the same resource combination.
**
**  The resource attributes byte has the value 0x58, corresponding to:
**		No sys ref / Sys heap / Not Purgeable / Locked /
**		Protected  / Not pre-loaded / Not changed / reserved
**
**	Each resource is placed as a true MM block, complete with header.
**		The tags say Reloc/Nonreloc (unused to date), the size fudge factor
**		is 0, the physical size field is honest, and the relative handle
**		depends on the following system heap configuration:
**
**	System Heap layout after ROM resources "loaded".  Note that the absolute
**		address of the start of System Heap is irrelevant!  In 32 bit mode, memory block-headers
**		are 12 bytes instead of 8, hence the following wierdness:
**	0x0000			Zone header, pointed to by (SysZone); size = HeapData = 0x34
**  0x0034			master ptr block; size = BlkData + 8*CMoreMasters = 0x18     0x1C < 1/25/89 >
**              	    where CMoreMasters = 2, for now... Master pointers are 8 bytes to
**						be compatible with a/ux.  Initresources uses these relative handles
**						to figure out where to put the master pointers in the System heap at
**						boot time.
**  0x004C  (24)	header of bogus master pointer block; size = BlkData = 0x8
**  0x0050  (32)	header of bogus master pointer block; size = BlkData = 0x0C < 1/25/89 >
**  0x0054  (24) 	first bogus master pointer...
**  0x005C	(32)	first bogus mp...add 8 byte of blkdata (12 byte block header)	< 1/25/89 >
**
*************************************************************************/
#define		k64KBytes		0x10000
#define		CIDeclDataPtr	0x7ec1a

#define		BLOCKSIZE	0x200000	/* Size of file block transfers. */
#define		ROMSLICES	4

//#define		Align4(A) 			((ulong)(A+3)&0xFFFFFFFC)
#define		Align(A,Size) 		((Ptr)((ulong)(A+(Size-1))&(~(Size-1))))
#define		AlignBelow(A,Size) 	(((ulong)(A+(Size-1))&(~(Size-1)))-(((ulong)(A))&(Size-1)?Size:0))
#define		BitSet(byte,bit)	(byte |= (1<<bit))

#define		gAlignment			16

#define		Pull(src, typ)		(*(typ *)(((src) += sizeof (typ)) - sizeof (typ)))

#define		HeapMagic24	0x0054		/* 24-bit mode - Offset from heap start to first bogus mp */ 
#define		HeapMagic32	0x005c		/* 32-bit mode - Offset from heap start to first bogus mp */ 
#define		Chekov		0x0000		/* Offset to checksum in ROM */
#define		Mapov		0x001A		/* Offset to rsrc part of ROM */
#define		Byteov		0x0030		/* Offset to 4 long checksums */				/* <10Oct86> */
#define		RomSizeOv	0x0040		/* Offset to size of ROM */

#define		RSRCLISTTYPE	'hirm'	/* resource type for resource-list resource <1.7> */
#define		RSRCLISTID		0		/* resource ID for resource-list resource <1.7> */

#define		VERSION		"5.0"

#include	<Types.h>
#include	<Errors.h>
#include	<Events.h>
#include	<Files.h>
#include	<Memory.h>
#include	<OSUtils.h>
#include	<Packages.h>
//#include	<Quickdraw.h>
#include	<Resources.h>
#include	<Stdio.h>
//#include	<CursorCtl.h>
#include	<String.h>
#include	<Strings.h>
#include	<StdLib.h>
#include 	<TextUtils.h>

/*************************************************************************
** Type definitions
*************************************************************************/

typedef unsigned long ulong;
typedef unsigned short ushort;
typedef unsigned char uchar;

#pragma options align=mac68k
struct ResHead {						/* <1.7> */
	long	offsetToFirst;				/* offset from base Of Rom to first rsrc Ref Entry */
	char	maxValidIndex;				/* maximum value for PRAM combo index */
	char	comboFieldSize;				/* size in bytes of combo field */
	short	comboVersion;				/* version of combo field */
	short	headerSize;					/* length of memory headers */
	char	zeros[6];					/* NOT filled with kckckc */
};

struct rcod {
	long ver;
	char fileName[0x100];
	long rsrcType;
	short rsrcID;
	long addr;
};

struct rrscHead {
	long ver;
	long cond;
	char comboField[8];
	char fileName[0x100];
	long typeCount;
};

struct rsiz {
	long ver;
	long size;
};

struct rdcl {
	long ver;
	char fileName[0x100];
	long addr;
};
#pragma options align=reset

/*************************************************************************
** Forward Referenced Routines
*************************************************************************/

/*extern void stuffResData();*/
/*extern void parseArgs();*/
/*extern char * PasName();*/
/*extern char * CName();*/

/*************************************************************************
** Prototypes
*************************************************************************/

void parseArgs(int argc, char *argv[]);
void openFiles(void);
void readROMCode(void);
void buildRsrcImage(void);
void closeFiles(void);
void computeCheckSums(void);
void fastRead(char *fName, char *fBuffer, long *pSize);
void fastWrite(char *fName, char *fBuffer, long fSize);
void MySignal(char *msg, int retCode);
char * OSTypeStr(OSType t);
unsigned char * PasName(char *cName);
char * CName(unsigned char *str);
void tabTo(char *str, int pos);

/*************************************************************************
** Global data.
*************************************************************************/
Ptr			ROMImage;					/* pointer to ROM array */
int			ROMSize;
Ptr			freeBtm, freeTop;

int			headerLen;					/* length of heap headers (32 vs. 24 bit mode) */

char		*inputFileName;
char		*outputFileName;
char		*logFileName;
short		inputFileRefnum;
FILE		*logFile;

char		strTmp[256];				/* temp buffer for CName(str) and PasName(str) */
char		ostypeStr[5];				/* temp buffer for OSTypeStr(ostype) */


/*************************************************************************
**	Entry point for Hiram.  Coordinates build of image.
*************************************************************************/
main(argc,argv)
int argc;
char *argv[];
{
	parseArgs(argc, argv);
	openFiles();
	fprintf(logFile, "× Beginning Hiram v%sÉ ×\n\n", VERSION);
	readROMCode();
	buildRsrcImage();										/* read the rsrc's into image */
	fprintf(logFile, "    Free space: %d%%\n\n", 100*(freeTop-freeBtm)/ROMSize);
	computeCheckSums();										/* <10Oct86> */
	fastWrite(outputFileName, ROMImage, ROMSize);
	fprintf(logFile, "× Hiram complete. ×\n");
	closeFiles();
	return 0;
}


/*************************************************************************
** Now *everything* gets loaded from the one resource file.
*************************************************************************/
void parseArgs(argc, argv)									/* 02Jun86 */
int argc;
char *argv[];
{
	char *curarg;
	
	inputFileName	= NULL;
	outputFileName	= NULL;
	logFileName		= NULL;
	headerLen		= 12;
	
	argc--;
	argv++;
	
	while (argc) {
		curarg = *argv++;
		argc--;
		
		if (!strcmp(curarg, "-o") && argc) {
			outputFileName = *argv++;
			argc--;
		} else if (!strcmp(curarg, "-log") && argc) {
			logFileName = *argv++;
			argc--;
		} else if (!strcmp(curarg, "-mf")) {
			// ignore
		} else if (!strcmp(curarg, "-24")) {
			headerLen = 8;
		} else {
			inputFileName = curarg;
		}
	}
	
	if (!inputFileName) MySignal("No input file specified", 1);
	if (!outputFileName) MySignal("No output file specified", 1);
}


/*************************************************************************
*************************************************************************/
void openFiles()
{
	if (!logFileName) {
		logFile = stdout;
		fprintf(logFile, "No -log file specified. Using stdout.\n");
	} else {
		logFile = fopen(logFileName, "w");
		if (!logFile) MySignal("Failed to open -log file", 1);
	}
	
	inputFileRefnum = OpenResFile( PasName(inputFileName));
	if ( inputFileRefnum <= 0 ) MySignal("Failed to open input file", ResError());
}


/*************************************************************************
** Allocate ROMImages: always get a buffer the size of the final ROM;
** then assume there are 0, 2, or 4 ROM slices, and allocate buffers
** accordingly.  Initialize ROM buffer with -- what else -- initials!
** Finally, load the pure code input and stuff away its size (i.e. the
** offset to the RSRC part of the ROM) at location MapOv.
*************************************************************************/
void readROMCode()
{
	Handle rsrcHdl;
	struct rsiz *rsizPtr;
	short *fillPtr;
	struct rcod *rcodPtr;
	short srcRefnum;
	Handle srcResHdl;
	struct rdcl *rdclPtr;
	short ret;
	long declSize;
	
	fprintf(logFile, "    Creating ROM image\n");
	
	/** size the image **/
	
	rsrcHdl = Get1Resource('rsiz', 128);
	if (!rsrcHdl) MySignal("rsiz 128 not found", ResError());
	
	rsizPtr = (struct rsiz *)(*rsrcHdl);
	fprintf(logFile, "        Found rsiz 128 resource:\n");
	fprintf(logFile, "                 ver = %d\n", rsizPtr->ver);
	fprintf(logFile, "                size = 0x%x\n", rsizPtr->size);
	
	ROMSize = ((struct rsiz *)(*rsrcHdl)) -> size;
	
	DisposeHandle(rsrcHdl);
	
	/** allocate space for image and align it **/		/* <2.0> */
	
	ROMImage = NewPtr(ROMSize + gAlignment);
	if (!ROMImage)		/* <2.0> */
		MySignal("Couldn't allocate memory for ROMImage!", 0);
	ROMImage = (Ptr) Align(ROMImage, gAlignment);			/* <2.0> */
	
	freeBtm = ROMImage;
	freeTop = ROMImage + ROMSize;
	
	/** fill space with Kurt Clark's initials **/		/* <1.4> */
	
	for (fillPtr=(short *)freeBtm; fillPtr<(short *)freeTop; fillPtr++)
		*fillPtr = 'kc';
	
	/** read in resource referenced by rcod 128 **/
	
	rsrcHdl = Get1Resource('rcod', 128);
	if (!rsrcHdl) MySignal("rcod 128 not found", ResError());
	
	rcodPtr = (struct rcod *)(*rsrcHdl);
	fprintf(logFile, "        Found rcod 128 resource:\n");
	fprintf(logFile, "                 ver = %d\n", rcodPtr->ver);
	fprintf(logFile, "            fileName = \"%s\"\n", rcodPtr->fileName);
	fprintf(logFile, "            rsrcType = '%s'\n", OSTypeStr(rcodPtr->rsrcType));
	fprintf(logFile, "              rsrcID = %d\n", rcodPtr->rsrcID);
	fprintf(logFile, "                addr = 0x%x\n", rcodPtr->addr);
	
	srcRefnum = OpenResFile( PasName(rcodPtr->fileName));
	if ( srcRefnum <= 0 ) MySignal("Couldn't open rcod-specified file", ResError());
	
	srcResHdl = Get1Resource(rcodPtr->rsrcType, rcodPtr->rsrcID);
	if (!srcResHdl) MySignal("Couldn't get rcod-specified resource", ResError());
	
	BlockMove(*srcResHdl, ROMImage + rcodPtr->addr, GetHandleSize(srcResHdl));
	freeBtm += rcodPtr->addr + GetHandleSize(srcResHdl);
	
	DisposeHandle(srcResHdl);
	CloseResFile(srcRefnum);
	DisposeHandle(rsrcHdl);
	
	/* Stuff size of ROM into another secret longword */
	*(long *)(ROMImage + RomSizeOv) = ROMSize;
	
	fprintf(logFile, "\n");
	
	/* Stuff DeclData in from data fork, because not sure how ROMLink worked */
	rsrcHdl = Get1Resource('rdcl', 128);
	if (!rsrcHdl) MySignal("rdcl 128 not found", ResError());
	
	rdclPtr = (struct rdcl *)(*rsrcHdl);
	fprintf(logFile, "        Found rdcl 128 resource:\n");
	fprintf(logFile, "                 ver = %d\n", rdclPtr->ver);
	fprintf(logFile, "            fileName = \"%s\"\n", rdclPtr->fileName);
	fprintf(logFile, "                addr = %d\n", rdclPtr->addr);
	
	ret = FSOpen(PasName(rdclPtr->fileName), 0, &srcRefnum);
	if (ret) MySignal("Couldn't open DeclData", ret);
	
	ret = GetEOF(srcRefnum, &declSize);
	if (ret) MySignal("Failed GetEOF on DeclData", ret);
	
	ret = FSClose(srcRefnum);
	if (ret) MySignal("Failed FSClose on DeclData", ret);
	
	freeTop -= declSize;
	fastRead(rdclPtr->fileName, freeTop, &declSize);
	
	DisposeHandle(rsrcHdl);

}


/*************************************************************************
** Steps for building ROM resource images:
**		- read combo version and field size
**		- FOR each entry in the resource-list resource:
**			- set up a reference entry for each resource
**			- set up a fake block-header for each one
**			- read data in after block-header
** 6/13/89	<1.7>	Rewrote to accomodate combinatorial resources in ROM
** 6/30/89	<1.8>	Modified to put ROM rsrc's at the end of ROM, and to
**					use a new reference entry field that gives an offset
**					to the rsrc data for that entry.
** 8/23/90  <2>		Added ability for multiple banks of ROM rsrc, 
**					specifically for Terror.
*************************************************************************/
void buildRsrcImage()
{
	int i, j, k;
	long bogusOff, prevRef;
	Ptr dataPtr, mmHeaderPtr, refPtr;
	struct ResHead *resHeadPtr;
	ulong resHeadOffset;
	int rrscCount;
	
	fprintf(logFile, "    Building resource image\n");
	fprintf(logFile, "        Resources have %d byte Memory Mgr headers\n", headerLen);
	
	freeBtm = Align(freeBtm, gAlignment);
	resHeadPtr = (struct ResHead *)freeBtm;
	resHeadOffset = (Ptr)resHeadPtr - (Ptr)ROMImage;
	*(ulong*)(ROMImage + Mapov) = resHeadOffset;
	fprintf(logFile, "        Resource header @ 0x%x\n", resHeadOffset);
	
	resHeadPtr->maxValidIndex = 4;				/* all it ever was */
	resHeadPtr->comboFieldSize = 8;				/* don't think this was ever anything different */
	resHeadPtr->comboVersion = 1;				/* can't seem to find this in layout docs */
	resHeadPtr->headerSize = headerLen;			/* size of fake MM header, 12 bytes for 32-bit */
	memset(resHeadPtr->zeros, 0, sizeof resHeadPtr->zeros);
	
	freeBtm += sizeof (struct ResHead);
	
	bogusOff = (headerLen == 12) ? HeapMagic32 : HeapMagic24;		/* use first master pointer */
	prevRef = 0;
	
	rrscCount = CountResources('rrsc');
	fprintf(logFile, "        Found %d rrsc resources\n", rrscCount);
	
	for (i=1; i<=rrscCount; i++) {
		Handle rrscHdl;
		struct rrscHead *rrscHeadPtr;
		char *rrscScanPtr;
		short srcRefnum;
		
		rrscHdl = GetIndResource('rrsc', i);
		HLock(rrscHdl);
		rrscHeadPtr = (struct rrscHead *)(*rrscHdl);
		rrscScanPtr = (char *)(*rrscHdl + sizeof (struct rrscHead));
		
		fprintf(logFile, "        rrsc referencing %d types from %s\n", rrscHeadPtr->typeCount, rrscHeadPtr->fileName);
		
		if (!rrscHeadPtr->cond) {
			fprintf(logFile, "            link-time conditional field false, skipping\n");
			continue;
		}
		
		srcRefnum = OpenResFile( PasName(rrscHeadPtr->fileName));
		if ( srcRefnum <= 0 ) {
			fprintf(logFile, "            couldn't open, skipping\n");
			continue;
		}
		
		for (j=0; j<rrscHeadPtr->typeCount; j++) {
			OSType srcResType;
			long srcResCountOfType;
			
			srcResType = Pull(rrscScanPtr, long);
			srcResCountOfType = Pull(rrscScanPtr, long);
			fprintf(logFile, "            '%s' -- %d resources\n", OSTypeStr(srcResType), srcResCountOfType);
			
			for (k=0; k<srcResCountOfType; k++) {
				short srcResId;
				Handle srcResHdl;
				long srcResSize;
				Str255 srcResName;
				
				srcResId = Pull(rrscScanPtr, short);
				fprintf(logFile, "                ID %d\n", srcResId);
				
				srcResHdl = Get1Resource(srcResType, srcResId);
				if (!srcResHdl) {
					fprintf(logFile, "                    couldn't open, skipping\n");
					continue;
				}
				
				srcResSize = GetHandleSize(srcResHdl);
				GetResInfo(srcResHdl, &srcResId, &srcResType, srcResName);
				
				dataPtr = Align(freeBtm + headerLen + /* for 'Kurt' word */ 4, gAlignment);
				mmHeaderPtr = dataPtr - headerLen;
				refPtr = Align(dataPtr + srcResSize, gAlignment);
				
				fprintf(logFile, "                    data@0x%08x blkhead@0x%08x ref@0x%08x (%db)\n",
					dataPtr - ROMImage, mmHeaderPtr - ROMImage, refPtr - ROMImage, srcResSize);
				
				BlockMove(*srcResHdl, dataPtr, srcResSize);
				
				// put an MM header (fake one) immediately below this resource
				if (headerLen == 12) {
					*(ulong *)(mmHeaderPtr - 4) = 'Kurt';
					*(ulong *)(mmHeaderPtr)     = 0xc0a00000;
					*(ulong *)(mmHeaderPtr + 4) = srcResSize + headerLen;	/* hiram aligned this??? */
					*(ulong *)(mmHeaderPtr + 8) = bogusOff;					/* ptr to fake master ptr */
				} else {
					*(ulong *)(mmHeaderPtr)     = srcResSize + headerLen;	/* hiram aligned this??? */
					*(char  *)(mmHeaderPtr)     = 0xc0;
					*(ulong *)(mmHeaderPtr + 4) = bogusOff;
				}
				
				// place the resource reference
				BlockMove(rrscHeadPtr->comboField, refPtr, 8);
				*(ulong *)(refPtr + 8) = prevRef;
				*(ulong *)(refPtr + 12) = dataPtr - ROMImage;
				*(ulong *)(refPtr + 16) = srcResType;
				*(short *)(refPtr + 20) = srcResId;
				*(char  *)(refPtr + 22) = 0x58;
				BlockMove(srcResName, refPtr + 23, srcResName[0] + 1); // fuck pstrings
				
				DisposeHandle(srcResHdl);
				
				bogusOff += 8; // next master pointer in the table
				prevRef = refPtr - ROMImage;
				freeBtm = refPtr + 23 + 1 + srcResName[0];
			} /* resource */
		} /* type */
		
		CloseResFile(srcRefnum);
	} /* file */
	
	resHeadPtr->offsetToFirst = prevRef;
	fprintf(logFile, "\n");
} /*buildRsrcImage*/


/*************************************************************************
** Close the error file and set the file type (if the file exists at all).
*************************************************************************/
void closeFiles()
{
	OSErr		e;
	FInfo		fi;
	
	if (logFile != stdout) {
		fclose(logFile);
		
		e = GetFInfo(PasName(logFileName), 0, &fi);
		if (e == 0)
		{
			fi.fdType = 0x54455854;		/* TEXT */
			fi.fdCreator = 0x4D505320;	/* MPS  */
			e = SetFInfo(PasName(logFileName), 0, &fi);
		}
	}
	
	CloseResFile(inputFileRefnum);
}



/*************************************************************************
**************************************************************************
** Lower-level utilities subordinate to the main flow.
**************************************************************************
*************************************************************************/


/*************************************************************************
** Presuming locations 0x30-0x3F are 0, compute byte-wide checksums for each
** of the ROM slices.  After all are computed, stuff them into the relevant
** longs in the ROM image.  Must not overwrite the ROM image until ALL are
** computed, to simplify the summing loop.
** Accumulate 16-bit words into 32-bit sum, stuff it in first long.
** Have ROMSize-4 bytes to be split into words for the sum.
**
** 1/24/89	<1.2>	CCH	Rewritten to always calc slice cksums
** 4/11/89	<1.5>	CCH	Zeros out individual cksums before doing anything, and 
**					excludes first 4 bytes from all checksumming.
** 5/11/89	<1.6>	CCH	Sped up checksum loop.
*************************************************************************/
void computeCheckSums()
{
	uchar *cPtr, *cMax;
	int i, top;
	ushort *wp;
	ulong cs, csum[8];

	fprintf(logFile, "    Calculating checksumsÉ\n\n");
	fflush(stdout);
	
	/** zero slice cksums **/
	
	cs = 0;
	for (i=0; i < ROMSLICES; i++) {
		csum[i] = 0;
		*(ulong*)(ROMImage+48+(i<<2)) = 0;
	}

	/** calc slice cksums during loop through ROMImage **/
	
	i = 0;
	cPtr = (uchar *)ROMImage + 4;					/* skip first long word */
	cMax = (uchar *)ROMImage + ROMSize;
	while (cPtr < cMax) {
		csum[i] += *cPtr++;					/* add to approp. slice */
		if (++i == ROMSLICES)				/* reset if necessary */
			i = 0;
	} /*while*/

	/** store slice checksums in the ROM Image **/
	
	for (i=0; i < ROMSLICES; i++)
		*(ulong*)(ROMImage + Byteov + (i*4)) = csum[i];

	/** calc main during loop through ROMImage **/

	wp = (ushort*)(ROMImage + 4);
	top = (ROMSize-4)/2;
	for (i=0;i<top;i++) {
		cs += *wp++;
	}

	/** store the complete checksum in the ROM Image **/
	
	*(ulong*)(ROMImage + Chekov) = cs;

} /*computeCheckSums*/


/*************************************************************************
** Utility to read a file named fName in BLOCKSIZE chunks into fBuffer,
** returning file size in bytes in *pSize.
*************************************************************************/
void fastRead(fName, fBuffer, pSize)
	char		*fName, *fBuffer;
	long			*pSize;
{
	char				*fPtr;
	long				codeRead, fSize;
	short				refNum, retCode;
	
	fprintf(logFile, "    Opening file Ò%sÓ for reading.\n\n", fName);
	fflush(stdout);

	retCode = FSOpen(PasName(fName), 0, &refNum);
	if (retCode) {
		fprintf(logFile, "File = %s ; Retcode = %d\n", fName, retCode);
		MySignal("Failed open.", retCode);
	}
	
	/* Read it in blkSize chunks. */
	fPtr  = fBuffer;
	fSize = 0;
	do {
		codeRead = BLOCKSIZE;
		retCode = FSRead(refNum, &codeRead, fPtr);
		fPtr  += codeRead;
		fSize += codeRead;
		//SpinCursor(8);
	} while (codeRead == BLOCKSIZE);
	if (retCode != eofErr)				/* permit only EOF to go unnoticed */
		MySignal("Read loop terminated by other than EOF.", retCode);
	
	retCode = FSClose(refNum);
	*pSize = fSize;					/* return the size */
}


/*************************************************************************
** Utility to write a file quickly using low-level IO.
*************************************************************************/
void fastWrite(fName, fBuffer, fSize)
	char	*fName, *fBuffer;
	long		fSize;
{
	long	codeWrit, codeWantWrit;
	short	refNum, retCode;
	
	fprintf(logFile, "    Opening file Ò%sÓ to write 0x%x characters.\n\n", fName, fSize);
	fflush(stdout);
	
	/*
	** Strategy for writing a file:  Attempt to create it: if not OK, but not
	** because file already exists, then die; else, open it and set EOF to 0.
	*/
	
	retCode = Create(PasName(fName), 0, 'rom ', 0x524F4D20);
	if ((retCode != dupFNErr) && (retCode))	{ 	/* error, not a dupe? */
		fprintf(logFile, "    ¥ Create of Ò%sÓ failedÉ\n", fName);
		fflush(stdout);
		MySignal("Create failed, and not a duplicate filename error.", retCode);
	}
	
	retCode = FSOpen(PasName(fName), 0, &refNum);
	if (retCode) {
		fprintf(logFile, "    ¥ Create of Ò%sÓ failedÉ\n", fName);
		fflush(stdout);
		MySignal("Open for R/W failed.", retCode);
	}
	
	retCode = SetEOF(refNum, 0);
	if (retCode) {
		fprintf(logFile, "    ¥ SetEOF of Ò%sÓ failedÉ\n", fName);
		fflush(stdout);
		MySignal("SetEOF failed after create.", retCode);
	}
	
	/* Write it in blkSize chunks, until last chunks... */
	do {
		codeWantWrit = (fSize > BLOCKSIZE) ? BLOCKSIZE : fSize;
		codeWrit = codeWantWrit;
		retCode = FSWrite(refNum, &codeWrit, fBuffer);
		if (codeWrit != codeWantWrit) {
			fprintf(logFile, "    ¥ Error writing Ò%sÓÉ\n", fName);
			fflush(stdout);
			MySignal("Couldn't write everything to fileÉ", retCode);
		}
		fBuffer += codeWrit;
		fSize   -= codeWrit;
		//SpinCursor(1);
	} while (fSize > 0);
	if (retCode) {
		fprintf(logFile, "    ¥ Couldn't write Ò%sÓÉ\n", fName);
		fflush(stdout);
		MySignal("Failure in file write.", retCode);
	}
	
	retCode = FSClose(refNum);
}


/*************************************************************************
** Write a message and exit, closing all files.
*************************************************************************/
void MySignal(msg, retCode)
char *msg;
int retCode;
{
	printf("**** Hiram Error: %s", msg);
	if (retCode)
		printf(" ; Return Code = %d\n", retCode);
	else
		putchar('\n');
	exit(1);
}


/*************************************************************************
** Convert OSType to printable string
*************************************************************************/
char * OSTypeStr(OSType t)
{
	*(OSType *)ostypeStr = t;
	ostypeStr[4] = 0;
	return ostypeStr;
}


/*************************************************************************
** Convert C filenames to Pascal names.
*************************************************************************/
unsigned char *PasName(char *cName)
{
	strcpy((char *)strTmp, (char *)cName);				/* name better be < 255 characters */
	return (unsigned char *)c2pstr((char *)strTmp);		/* 1.2 */
}


/*************************************************************************
** Convert Pascal filenames to C names.
*************************************************************************/
char *CName(unsigned char *str)
{
	strncpy((char *)strTmp, (char *)str, str[0]+1);		/* name better be < 255 characters */
	return (char *)p2cstr((unsigned char *)strTmp);
}


/*************************************************************************
** String formatting routine
*************************************************************************/
void tabTo( str, pos)
char *str;
int pos;
{
	int len, i;
	
	len = strlen(str);
	for (i=pos; i>len; i--)
		strcat(str," ");
} /*tabTo*/


/*******************
*	End Of Hiram.c
********************/



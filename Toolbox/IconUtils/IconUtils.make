#
#	File:		IconUtils.make
#
#	Contains:	Makefile for the Icon Utilities.
#
#	Written by:	Kurt Clark, Chas Spillar, and Tim Nichols
#
#	Copyright:	© 1992 by Apple Computer, Inc., all rights reserved.
#
#	Change History (most recent first):
#


IconUtilsObjs 	= 					"{ObjDir}IconUtils.a.o"			¶
									"{ObjDir}IconUtils.c.o"

"{LibDir}IconUtils.lib"			Ä	{IconUtilsObjs}
	Lib {StdLibOpts} -o "{Targ}" {IconUtilsObjs}


"{ObjDir}IconUtils.a.o"			Ä	"{IconUtilsDir}IconUtils.a"
	Asm {StdAOpts} -o "{Targ}" "{IconUtilsDir}IconUtils.a"



"{ObjDir}IconUtils.c.o"			Ä	"{IconUtilsDir}IconUtils.c"
	C {StdCOpts} -o "{Targ}" "{IconUtilsDir}IconUtils.c"
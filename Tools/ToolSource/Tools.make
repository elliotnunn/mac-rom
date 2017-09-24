LibFiles-68K    =	¶
					"{Libraries}Stubs.o"				¶
					"{CLibraries}StdCLib.o"				¶
					"{Libraries}MacRuntime.o"			¶
					"{Libraries}IntEnv.o"				¶
					"{Libraries}Interface.o"			¶

"{ToolSrcDir}Vectorize.c.o"			Ä	"{ToolSrcDir}Vectorize.c" "{ToolSrcDir}MPWObjFuncs.c"
	SC -o {Targ} "{ToolSrcDir}Vectorize.c"

"{ToolDir}Vectorize"				Ä	"{ToolSrcDir}Vectorize.c.o"
	ILink -d -t 'MPST' -c 'MPS ' -o {Targ} {LibFiles-68k} "{ToolSrcDir}Vectorize.c.o"


"{ToolSrcDir}RomLink.c.o"			Ä	"{ToolSrcDir}RomLink.c"
	SC -o {Targ} "{ToolSrcDir}RomLink.c"

"{RsrcDir}RomLink"					Ä	"{ToolSrcDir}RomLink.c.o"
	ILink -d -t 'MPST' -c 'MPS ' -o {Targ} {LibFiles-68k} "{ToolSrcDir}RomLink.c.o"

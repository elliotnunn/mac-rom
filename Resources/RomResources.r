/*
	File:		RomResources.r

	Contains:	The ROM resource descriptions used to create the rom image.

	Written by:	Kurt Clark.

	Copyright:	© 1992-1994 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	  <SM53>	  2/6/94	kc		Fix expression from last checkin.
	  <SM52>	  2/6/94	kc		Move beep resoruces into MiscDir.
	  <SM51>	  2/6/94	kc		ADD TNT error and boot beeps.
	  <SM49>	12/13/93	PN		Roll in KAOs and Horror changes to support Malcom and AJ
									machines.
	  <SM48>	11/29/93	JDR		added Meter CDEF for the Sound Mgr
	  <SM47>	 11/9/93	KW		added ecfg resources for STP machines
	  <SM46>	 11/8/93	SAM		Separated the "gibbly" resource from the boot(3) and rovm
									resources.  Condtionally include the "gbly" resource.
	  <SM45>	 11/6/93	SAM		Added iWrongOutputSampleRate.
	  <SM44>	 11/2/93	JDR		deleted mixer tables, and added headphone audio component
	  <SM43>	 9/17/93	RC		Take out the FOND resources, since the Font Mgr caching code has
									a bug which prevents it from being able to use FONDs out of ROM
	  <SM42>	 9/13/93	RC		Fixing FONT/FOND resources
	  <SM41>	  9/9/93	RC		Took out extra Enet resource which was left over from Dave
									Calverts version of the PDM ENET driver
	  <SM40>	  9/2/93	SKH		change hasSCSIDiskMode to hasSCSIDiskModeFeature
	  <SM39>	  9/2/93	BG		Added various PDMs to the List O' Machines that have 'pslt'
									resources.
	  <SM38>	  9/1/93	JDR		Added 'mixt' to the sound manager.
	  <SM37>	 8/19/93	RC		Added 'pslt' resources for Cold Fusion and Carl Sagan
	  <SM36>	 8/17/93	JDR		removed some unused Sound Mgr resources
		<35>	 8/17/93	IH		BG checked in gestalt equates, but did not do a full build. This
									file was still using pre-release gestalt names and wouldn't
									build.
	  <SM34>	 8/11/93	RC		take out LC Ethernet driver from PDM ROM
	  <SM33>	  8/4/93	JDR		Integrate sound manager 3.0 project.
	  <SM32>	 7/28/93	SAM		Added several 'nlib' resources from Native System Additions.
	  <SM31>	 7/21/93	RC		Back Out <sm 30>
	  <SM29>	 7/14/93	RC		Use hasAMIC feature flags forSerialDMA resources.
	  <SM28>	 6/28/93	PN		Add hasMACE link time condition for MACEecfg.rsrc.
	  <SM27>	 6/17/93	joe		RE-Added DRVR -16500 (PDM sound in) to Sound rrsc.
	  <SM26>	 6/14/93	kc		Roll in Ludwig.
	  <LW18>	 4/30/93	mal		Moved Ethernet.RSRC to {MiscDir}.  Added LCII's ecfg.
	  <LW17>	 4/20/93	fau		#1079789: Bug # 1079789:  Included the new 'pslt' resources and
									used equates for all the 'pslt' res id's.
	  <LW15>	 4/11/93	chp		Cleaned up Serial and SerialDMA 'rrsc's and renumbered a few
									others to avoid future conflicts.
	  <LW14>	  4/8/93	fau		Changed the combo for the NetBoot drivers from NetBoot to
									AllCombos so that they get loaded when a machine has a
									DefaultRSRC of 4.
	  <LW13>	 3/25/93	ejb		change resource number of zound input DRVR from 52 to -16565
	  <LW11>	  3/8/93	JDB		Removed the DLOG and DITL resources for RTSndIn since these are
									now in the Gibbly.
	   <LW9>	 1/27/93	mal		Removed inclusions of 'DRVR' 127 from Ethernet.RSRC.  Added r
	   <LW8>	  1/6/93	ejb		remove Sadism and unneeded DSP Resources
	   <LW7>	  1/4/93	ejb		added rules to include std snd player module resource
	   <LW6>	12/29/92	chp		Now, serial driver resources are all loaded from Serial.rsrc.
									SERD 0 is universal, and SERDs 60 & 61 are included as well for
									hasIopScc builds. The net result has not changed, but
									Serial.make has been simplified to generate fewer intermediate
									files.
	   <LW5>	12/23/92	fau		Changed the I2C and VDIG thng and code id's to use the
									MSAD-blessed ones.
	   <LW3>	12/17/92	fau		Added 'wedg' resources to be pulled from the ColorPicker.rsrc so
									the color picker works.
	  <SM25>	 6/11/93	RC		Ended the need for the special version of the
									AppleTalk.ROM.PDM.RSRC
	  <SM24>	 5/31/93	joe		Added DRVR -16500 (PDM sound in) to Sound rrsc.
	  <SM23>	 5/30/93	SAM		Moved ROM_EM to Tidbits.
	  <SM22>	  5/6/93	RC		deleted some ncod's and added nlib resources
	  <SM21>	  5/4/93	RC		Added two ltlk resources to C AppleTalk in ROM rsrc
	  <SM20>	  5/3/93	RC		Added an ncod resource to the GoNative rsrc
	  <SM19>	  5/3/93	RC		make minor fix to last checkin
	  <SM18>	  5/3/93	RC		uncomment out AMIC shal
	  <SM17>	 4/11/93	chp		Cleaned up Serial and SerialDMA 'rrsc's and renumbered a few
									others to avoid future conflicts.
	  <SM16>	 3/25/93	RB		Added Robert Polic's password-on-boot icon from Ludwig.
	  <SM15>	 3/24/93	dwc		Restore resources 4,5 and re-enable CAppleTalk to use patched
									AT58.
	  <SM14>	 3/24/93	dwc		Removed 'ltlk' resources 4,5 in the hasAppleTalkInROM definition
									which AppleTalk.ROM.RSRC does not have so ROM will build without
									using CAppleTalk.
	  <SM13>	 3/19/93	CSS		Remove Sadism junk.
	  <SM12>	  3/9/93	RC		Sorry about this, but I was facked out by a GoNative problem
	  <SM11>	  3/9/93	RC		Took inSaneNFPU out of Risc ROM
	  <SM10>	  3/8/93	PN		From the conversation with Jon . We should use InSane for NonFPU
									pack 4 and 5 from now on. Change Sane.rsrc to InSaneNFPU.rsrc
	   <SM9>	  3/8/93	RC		Took out ncod resource #4
	   <SM8>	  3/8/93	RC		made AppleTalk C version work on both Smurf and PDM
	   <SM7>	  3/8/93	dwc		Changed PDM ENET resource ID to be unique from DeclDataMace.
	   <SM6>	  3/5/93	RC		Want C version only on PDM, not Smurf also
	   <SM5>	  3/5/93	RC		adding the C version of the Appletalk.ROM.RSRC to PDM
	   <SM4>	  3/4/93	RC		Added the SerialDMA resources needed for PDM
	   <SM3>	 2/27/93	chp		Update from Ludwig. <LW6>
	   <SM2>	 2/22/93	kc		Move Ethernet.RSRC from TidbitsDir to MiscDir.
	   <20+>	02/16/93	kc		Removed DRVR 127. Rolled in changes from RISC build.
	     <5>	  2/4/93	dwc		Add PDMMaceEnet resource definition.
	     <4>	 1/10/93	RC		Added Resources for Emulator Accelerations
	   <LW6>	12/29/92	chp		Now, serial driver resources are all loaded from Serial.rsrc.
									SERD 0 is universal, and SERDs 60 & 61 are included as well for
									hasIopScc builds. The net result has not changed, but
									Serial.make has been simplified to generate fewer intermediate
									files.
	     <3>	12/18/92	RC		Fixed rrsc resource ID conflict between Dictionary and GoNative
	     <2>	12/17/92	RB		Added the Dictionary Mgr.
	     <1>	 12/7/92	rpc		added resource for GoNative (RISC)
	  <SM20>	02/10/93	HY		Removed resource 'rrsc' 11 which was only used for LCR/LC930.
	  <SM19>	 1/29/93	RB		Removed ppt# (0) and PAT# (0) from the ROM resource list, since
									the Control Panel 'General' wants to modify this resource when
									the user double clicks on the desktop icon.
	  <SM18>	12/23/92	kc		Remove DSPHardware from the build.
	  <SM17>	12/18/92	HY		Added 'rrsc' 11, string list resource of machine names for LC930 only.
	  <SM16>	12/18/92	RB		Enabled the backlight driver.
	  <SM15>	12/17/92	RB		Added more conditionals for making 1 Meg ROMs easier.
	  <SM14>	12/15/92	CSS		Add dictionary manager to the ROM.
	  <SM13>	12/10/92	ejb		JDB add the '3210' slave resource into the list of RTDrvr
									resources.
	  <SM12>	12/10/92	JDB		ejb: Added 3210 resources for RTDrvr, sjs: Added resources for
									Sadism, jdb: Added resources for Sound Input driver.
	  <SM11>	 12/9/92	DH		Added new I2C component resources and modified VDig resources.
	  <SM10>	 12/1/92	RB		Created a 'rovm' resource to override some system resources
									which we want used from ROM since the ROM versions are up to
									date. Removed dialogs from PPC stuff.
	   <SM9>	 12/1/92	ejb		seperate RTMgr and RTDrvr resources/files.
	   <SM8>	11/24/92	RB		Use the feature hasROM_EM so it can be easily taken out.
	   <SM7>	11/20/92	RB		Added resources from the system that are usable from ROM in
									order to save memory.
	   <SM5>	11/18/92	CSS		Set bit two in AppleTalk2_NetBoot_FPU per Kurt's wisdom.
	   <SM4>	11/17/92	kc		Put the CommToolbox back into the LC930 build.
	   <SM4>	11/16/92	ejb		Add resource IDs for MACE 3:1 and 6:1 sound
									compression/decompression to Sadism resource declarations.
	   <SM3>	11/14/92	kc		Exclude CommToolbox, VM, and DataAccessMgr from the LC930 build.
	   <SM2>	11/11/92	RB		Use hasNewSoundMgr and added changes for the LC930.
	Example:

				resource 'rrsc' (120, "InSane") {			<-- Group name and id
					kUniversal,								<-- Link time conditional
					AppleTalk2_NetBoot_FPU,					<-- Combination bitfield
					{RsrcDir},								<-- Resource pathname
					"InSane.rsrc",							<-- Resource filename

					{
						'PACK',								<-- Resource type
						{ 4, 5 };							<-- Resource id(s)
					}
				};

				resource 'rrsc' (250, "SerialIOP") {		<-- Group name and id
					hasIopScc,								<-- Link time conditional
					AllCombos,								<-- Combination bitfield
					{RsrcDir},								<-- Resource pathname
					"Serial.rsrc",							<-- Resource filename

					{
						'SERD',								<-- Resource type
						{ 60 };								<-- Resource id(s)

						'SERD',								<-- Resource type
						{ 61 };								<-- Resource id(s)
					}
				};

			The group name and id are arbitrary but the name should be descriptive.
			If link time conditional is false, the resources will be ommited.
			The combination bitfield is a packed-array of 64 bits that is used
			to specify at runtime which resources to put into the ROM resource map.
			In the product info for each CPU, there is a byte that is used to
			index the bitfield (from left to right). If the corresponding bit is set
			for a resource, it is included in the ROM resource map.

*/

#include "RomTypes.r"
#include "GestaltPriv.r"
#include "GestaltEqu.h"
#include "SysTypes.r"
#include "Types.r"

#define AppleTalk1					0x40			/*	Appletalk 1.0				01000000 */
#define AppleTalk2					0x20			/*	Appletalk 2.0				00100000 */
#define	AppleTalk2_NetBoot_FPU		0x30			/*	Has FPU and remote booting	00110000 */
#define	AppleTalk2_NetBoot_NoFPU	0x08			/*	Has remote booting, no FPU	00001000 */
#define NetBoot						0x10			/*	Has remote booting			00010000 */
#define AllCombos					0x78			/*	Universal resource			01111000 */

#define kUniversal	true
#define kUnused		false

resource 'rrsc' (10, "Gibbly Guts") {
	kUniversal,
	AllCombos,
	{RsrcDir},
	"Gibbly.rsrc",

	{
		'rovm',
		{ 0 };
	}
};

resource 'rrsc' (12, "Gibbly Rsrc") {
	hasROMGibbly,
	AllCombos,
	{RsrcDir},
	"Gibbly.rsrc",

	{
		'gbly',
		{ -16385 };

	}
};

resource 'rrsc' (20, "ROMFonts") {
	kUniversal,
	AllCombos,
	{RsrcDir},
	"ROMFonts.rsrc",

	{
		'CURS',
		{ 1, 2, 3, 4 };

		'FONT',
		{12, 393, 396, 521 };

/*		'FOND',
		{ 0, 3, 4 };	The Font Mgr can't handle this */

		'snd ',
		{ 1 };
	}
};

resource 'rrsc' (30, "kbd") {
	kUniversal,
	AllCombos,
	{RsrcDir},
	"kbd.rsrc",

	{
		'KCHR',
		{ 0 };

		'vadb',
		{
			0 /*ISO Cosmo*/,
			1 /*JIS Cosmo*/,
			2 /*ANSI Cosmo*/,
			3 /*ISO Andy*/,
			4 /*JIS Andy*/,
			5 /*ANSI Andy*/
		};

		'KMAP',
		{ 0, 2, 27, 198, 199, 200, 204, 205, 206 };

		'KCAP',
		{ 1,2,4,5,14,16,17,198,199,200,204,205,206 };
	}
};

resource 'rrsc' (35, "Portable kbd") {
	hasPortableKeyLayouts,
	AllCombos,
	{RsrcDir},
	"kbd.rsrc",

	{
		'KCAP',
		{ 6, 7 };
	}
};

resource 'rrsc' (40, "ControlMgr") {
	hasSysSevenResources,
	AllCombos,
	{RsrcDir},
	"ControlMgr.rsrc",

	{
		'CDEF',
		{ 0, 1 };
	}
};

resource 'rrsc' (50, "MenuMgr") {
	hasSysSevenResources,
	AllCombos,
	{RsrcDir},
	"MenuMgr.rsrc",

	{
		'MBDF',
		{ 0 };

		'MDEF',
		{ 0 };
	}
};

resource 'rrsc' (60, "MiscROMRsrcs") {
	kUniversal,
	AllCombos,
	{RsrcDir},
	"MiscROMRsrcs.rsrc",

	{
		'accl',
		{ 0, 1, 2, 4, 5, 6, 7, 8, 9 };

		'ics#',
		{ -16386 };

		'ics4',
		{ -16386 };

		'ics8',
		{ -16386 };

		'cicn',
		{ -20023, -20022, -20021, -20020 };

		'clut',
		{ 5, 9 };

		'ppat',
		{ 16, 18 };

		'pixs',
		{ -14335, -14334, -10199, -10200, -10201, -10202, -10203, -10204, -10205, -10206, -10207, -10208 };
	}
};

resource 'rrsc' (61, "MiscROMRsrcs") {
	hasSCSIDiskModeFeature,
	AllCombos,
	{RsrcDir},
	"MiscROMRsrcs.rsrc",

	{
		'PICT',								/* SCSI Disk Mode pictures */
		{ 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106 };
	}
};

resource 'rrsc' (70, "EDisk") {
	hasEDisk,
	AllCombos,
	{RsrcDir},
	"EDisk.RSRC",

	{
		'DRVR',
		{ 48 };
	}
};

resource 'rrsc' (80, "CQD") {
	kUniversal,
	AllCombos,
	{RsrcDir},
	"CQD.rsrc",

	{
		'clut',
		{ 1, 2, 4, 8, 127 };

		'gama',
		{ 0 };

		'mitq',
		{ 0 };
	}
};

resource 'rrsc' (90, "WindowMgr") {
	hasSysSevenResources,
	AllCombos,
	{RsrcDir},
	"WindowMgr.rsrc",

	{
		'WDEF',
		{ 0, 1 };

		'wctb',
		{ 0 };

		'cctb',
		{ 0 };
	}
};

resource 'rrsc' (100, "ListMgr") {
	hasSysSevenResources,
	AllCombos,
	{RsrcDir},
	"ListMgr.rsrc",

	{
		'PACK',
		{ 0 };

		'LDEF',
		{ 0, 19 };
	}
};

resource 'rrsc' (110, "StandardFile") {
	hasSysSevenResources,
	AllCombos,
	{RsrcDir},
	"StandardFile.rsrc",

	{
		'PACK',
		{ 3 };
	}
};

resource 'rrsc' (120, "InSane") {
	has040MMU,
	AppleTalk2_NetBoot_FPU,
	{RsrcDir},
	"InSane.rsrc",

	{
		'PACK',
		{ 4, 5 };
	}
};

resource 'rrsc' (130, "Sane1") {
	kUniversal,
	AppleTalk2_NetBoot_NoFPU,
	{RsrcDir},
	"InSaneNFPU.rsrc",

	{
		'PACK',
		{ 4, 5 };
	}
};

resource 'rrsc' (140, "Sane2") {
	kUniversal,
	AllCombos,
	{RsrcDir},
	"Sane.rsrc",

	{
		'PACK',
		{ 7 };
	}
};

resource 'rrsc' (150, "AppleEventMgr") {
	hasSysSevenResources,
	AllCombos,
	{RsrcDir},
	"AppleEventMgr.rsrc",

	{
		'PACK',
		{ 8 };
	}
};

resource 'rrsc' (160, "PPC") {
	hasSysSevenResources,
	AllCombos,
	{RsrcDir},
	"PPC.rsrc",

	{
		'PACK',
		{ 9 };

		'ppcc',
		{ -5856 };

	}
};

resource 'rrsc' (170, "EditionMgr") {
	hasSysSevenResources,
	AllCombos,
	{RsrcDir},
	"EditionMgr.rsrc",

	{
		'PACK',
		{ 11 };
	}
};

resource 'rrsc' (180, "ColorPicker") {
	hasSysSevenResources,
	AllCombos,
	{RsrcDir},
	"ColorPicker.rsrc",

	{
		'wedg',
		{ -5760, -5759 };

		'PACK',
		{ 12 };
	}
};

resource 'rrsc' (190, "CommToolBox") {
	hasSysSevenResources,
	AllCombos,
	{RsrcDir},
	"CommToolbox.rsrc",

	{
		'cmtb',
		{ -32508, -32509, -32510, -32511, -32512  };

		'proc',
		{ -32510, -32511, -32512 };

		'snd ',
		{ -32512 };

		'LDEF',
		{ -32510, -32512 };
	}
};


resource 'rrsc' (200, "DataAccessMgr") {
	hasDataAccessPACK,
	AllCombos,
	{RsrcDir},
	"DataAccessMgr.rsrc",

	{
		'PACK',
		{ 13 };

		'proc',
		{ -5728, -5727 };
	}
};


resource 'rrsc' (210, "HelpMgr") {
	hasSysSevenResources,
	AllCombos,
	{RsrcDir},
	"HelpMgr.rsrc",

	{
		'PACK',
		{ 14 };

		'WDEF',
		{ 126 };
	}
};

resource 'rrsc' (220, "PictUtilities") {
	hasSysSevenResources,
	AllCombos,
	{RsrcDir},
	"PictUtilities.rsrc",

	{
		'PACK',
		{ 15 };
	}
};

resource 'rrsc' (240, "SCCIOP") {
	hasIopScc,
	AllCombos,
	{RsrcDir},
	"SCCIOP.rsrc",

	{
		'iopc',
		{ 0 };
	}
};

resource 'rrsc' (270, "SerialDMA") {
	kUniversal,
	AllCombos,
	{MiscDir},
	"SerialDMA.rsrc",

	{
		'nsrd',
		{ 1 };
	}
};

resource 'rrsc' (281, "SerialHALPSC") {
	hasPSC,
	AllCombos,
	{RsrcDir},
	"SerialDMA.rsrc",

	{
		'shal',									/* PSC DMA HAL module */
		{ 1 };
	}
};

resource 'rrsc' (282, "SerialHALAMIC") {
	hasAMIC,
	AllCombos,
	{RsrcDir},
	"SerialDMA.rsrc",

	{
		'shal',									/* AMIC DMA HAL module */
		{ 2 };
	}
};

resource 'rrsc' (290, "SWIMIOP") {
	hasIopSwim,
	AllCombos,
	{RsrcDir},
	"SWIMIOP.RSRC",

	{
		'iopc',
		{ 1 };
	}
};

resource 'rrsc' (300, "AppleTalk") {
	hasAppleTalkInROM,
	AllCombos,
	{MiscDir},
	"AppleTalk.ROM.RSRC",

	{
		'lmgr',
		{ 0 };

		'DRVR',
		{ 9, 10, 40, 125, 126, 127 };

		'drvr',
		{ 9 };

		'atlk',
		{ 1, 3, 10 };

		'ltlk',
		{ 0, 1, 2, 3, 4, 5, 6, 7 };

		'iopc',
		{ 127, 128 };
	}
};


resource 'rrsc' (310, "UnusedAppleTalk") {	// why are these not put in rom???
	kUnused,
	AllCombos,
	{RsrcDir},
	"AppleTalk.ROM.RSRC",

	{

		'AINI',
		{ 30, 30000, 32000 };

		'STR#',
		{-16404,-16408,-16503,-16504};

		'enet',
		{ 8, 38, 43, 46, 51, 54 };

		'tokn',
		{ 11,52 };
	}
};

resource 'rrsc' (320, "ATBoot") {
	hasNetBoot,
	AllCombos,
	{RsrcDir},
	"ATBoot.RSRC",

	{
		'DRVR',								/* .ATBoot Driver */
		{ 60 };
	}
};

resource 'rrsc' (330, "NetBoot") {
	hasNetBoot,
	AllCombos,
	{RsrcDir},
	"NetBoot.RSRC",
	{
		'DRVR',								/* .NetBoot Driver */
		{ 49 };
	}
};

resource 'rrsc' (340, "AppleIIFonts") {
	hasApple2Fonts,
	AllCombos,
	{RsrcDir},
	"ROMApple2Fonts.RSRC",

	{
		'attx',
		{ 1 };
	}
};

resource 'rrsc' (350, "NewAge") {
	hasNewAge,
	AllCombos,
	{RsrcDir},
	"NewAge.RSRC",

	{
		'DRVR',								/* .NewAge	Driver */
		{ 4 };
	}
};

resource 'rrsc' (360, "RealTimeMgr") {
	hasDSP,
	AllCombos,
	{RsrcDir},
	"RTMgr.rsrc",

	{
		'rtmr',								/* DSP Manager */
		{  0 };
	}
};

resource 'rrsc' (361, "RTDrvr") {
	hasDSP,
	AllCombos,
	{RsrcDir},
	"RTDrvr.rsrc",

	{
		'DRVR',								/* DSP Driver */
		{ 51 };

		'3210',								/* 'boot' 		segment */
		{  0 };

		'3210',								/* 'evt ' 		segment */
		{  1 };

		'3210',								/* 'core' 		segment */
		{  2 };

		'3210',								/* 'patches'	segment */
		{  3 };

		'3210',								/* 'slave'		segment */
		{  4 };
	}
};

resource 'rrsc' (370, "StdSndInput") {
	hasDSP,
	AllCombos,
	{RsrcDir},
	"StdSndInput.rsrc",

	{
		'dspf',
		{ 128 };
	}
};

resource 'rrsc' (380, "StdSndMidput") {
	hasDSP,
	AllCombos,
	{RsrcDir},
	"StdSndMidput.rsrc",

	{
		'dspf',
		{ 128 };
	}
};

resource 'rrsc' (390, "StdSndOutput") {
	hasDSP,
	AllCombos,
	{RsrcDir},
	"StdSndOutput.rsrc",

	{
		'dspf',
		{ 128 };
	}
};

resource 'rrsc' (401, "StdSndPlayer") {
	hasDSP,
	AllCombos,
	{RsrcDir},
	"StdSndPlayer.rsrc",

	{
		'dspf',
		{ 128 };
	}
};

resource 'rrsc' (410, "RTSnd") {
	hasDSP,
	AllCombos,
	{RsrcDir},
	"RTSnd.rsrc",

	{
		'rtmr',								/* RealTime Sound Manager*/
		{ 1 };
	}
};

resource 'rrsc' (420, "ZoundBlueInputAdaptor") {
	hasDSP,
	AllCombos,
	{RsrcDir},
	"ZoundBlueInputAdaptor.rsrc",

	{
		'dspf',								/* Standard Sound Input */
		{ 128 };
	}
};

resource 'rrsc' (430, "RTSndIn") {
	hasDSP,
	AllCombos,
	{RsrcDir},
	"RTSndIn.rsrc",

	{
		'DRVR',								/* RealTime Sound Input */
		{ -16565 };
	}
};

resource 'rrsc' (440, "VDigT") {
	hasVideoIn,
	AllCombos,
	{RsrcDir},
	"VDigT.rsrc",

	{
		'thng',
		{ -16727 };
	}
};

resource 'rrsc' (445, "VDigC") {
	hasVideoIn,
	AllCombos,
	{RsrcDir},
	"VDigC.rsrc",

	{
		'code',
		{ -16729 };
	}
};

resource 'rrsc' (450, "I2CT") {
	hasVideoIn,
	AllCombos,
	{RsrcDir},
	"I2CT.rsrc",

	{
		'thng',
		{ -16728 };
	}
};

resource 'rrsc' (455, "I2CC") {
	hasVideoIn,
	AllCombos,
	{RsrcDir},
	"I2CC.rsrc",

	{
		'code',
		{ -16730 };
	}
};

resource 'rrsc' (461, "Ethernet2") {
	hasMace,
	AllCombos,
	{RsrcDir},
	"MACEecfg.rsrc",						/* Its the same rsrc type as the SONIC ecfg but */
											/* it does have a different format. Gestalt machinetype */
											/* allows different formats on different cpus */
	{
		'ecfg',								/* Enet Config resources for MACE Enet Driver */
		{ 43, 60, 78, 79 };					/* Rsrc ID's are gestaltMachineType codes */
	}
};

resource 'rrsc' (470, "VM") {
	hasVMinROM,
	AllCombos,
	{MiscDir},
	"VM.RSRC",

	{
		'ptch',
		{ 42 };
	}
};

resource 'rrsc' (480, "Backlight") {
	hasLCDScreen,
	AllCombos,
	{RsrcDir},
	"Backlight.RSRC",

	{
		'DRVR',
		{ -16511 };
	}
};

resource 'rrsc' (335, "LANDisk") {
	kUniversal,
	AllCombos,
	{MiscDir},
	"LANDisk.rsrc",

	{
		'dfrg',
		{ -20722 };
	}
};

resource 'rrsc' (435, "BCScreen") {
	kUniversal,
	AllCombos,
	{MiscDir},
	"BCScreen.rsrc",

	{
		'ndrv',
		{ -16515 };
	}
};

resource 'rrsc' (501, "EmulatorAccelerations") {
	hasMixedMode,
	AllCombos,
	{MiscDir},
	"EmulatorAccelerations.rsrc",

	{
		'GARY',
		{ 1 }
	}
};

resource 'rrsc' (599, "Multiprocessing") {
	hasMixedMode,
	AllCombos,
	{MiscDir},
	"MultiprocessingServices.rsrc",

	{
		'ncod',
		{ 2 /*MPLibrary*/ };
		'nlib',
		{ 3 /*MPSharedGlobals*/ };
	}
};

resource 'rrsc' (502, "GoNative") {
	hasMixedMode,
	AllCombos,
	{MiscDir},
	"GoNativeResources",

	{
		'cfrf',
		{ 0 };

		'ncod',
		{ 0,1,8 };

		'nlib',
		{
			5 /*InterfaceLib*/,
			6 /*PrivateInterfaceLib*/,
			7 /*BootStdCLib*/,
			8 /*MathLibGlobals*/,
			9 /*MathLib*/,
			10 /*StdCLib*/,
			-16420 /*Math64Lib*/,
			-20264 /*CursorDevicesLib*/
		};
	}
};

/* everything after here is new */

resource 'rrsc' (503, "DriverServices") {
	hasMixedMode,
	AllCombos,
	{MiscDir},
	"DriverServices.rsrc",

	{
		'ntrb',
		{ -16400 /*NameRegistryTraps*/ };

		'nlib',
		{ -16400 /*NameRegistryLib*/, -16407 /*DSLGlobalsLib*/, -16401 /*DriverServicesLib*/, -16402 /*DriverLoaderLib*/, -16404 /*PCILib*/, -16403 /*VideoServicesLib*/, -16405 /*VideoServicesGlobals*/ };
	}
};

resource 'rrsc' (504, "PowerMgr") {
	kUniversal,
	AllCombos,
	{MiscDir},
	"PowerMgr.rsrc",

	{
		'nlib',
		{ -16411 /*PowerMgrLib*/ };

		'scod',
		{ -20961, -20984 };
	}
};

resource 'rrsc' (605, "ATA DRVRs") {
	kUniversal,
	AllCombos,
	{MiscDir},
	"ATAMgr.rsrc",

	{
		'DRVR',
		{ 53 /*.ATADisk*/, -20175 /*.ATALoad*/ };
	}
};

resource 'rrsc' (607, "NativeNub -- for MacsBug?") {
	kUniversal,
	AllCombos,
	{MiscDir},
	"NativeNub.rsrc",

	{
		'ncod',
		{ 50 /*NativeNub*/ };
	}
};

resource 'rrsc' (610, "NativeItt -- SCSI") {
	kUniversal,
	AllCombos,
	{MiscDir},
	"NativeItt.rsrc",

	{
		'nitt',
		{ 43 /*Native 4.3*/ };
		'gcko',
		{ 43 /*Main*/ };
	}
};

resource 'rrsc' (620, "PCCard") {
	kUniversal,
	AllCombos,
	{MiscDir},
	"PCCard.rsrc",

	{
		'ndrv',
		{ -20166 /*DefaultPCCardEnabler*/, -20181 /*pccard-ata*/ };
	}
};

resource 'rrsc' (630, "MediaBay") {
	kUniversal,
	AllCombos,
	{MiscDir},
	"MediaBay.rsrc",

	{
		'ndrv',
		{ -20164 /*media-bay*/ };
		'code',
		{ -20164 /*Main*/ };
	}
};

resource 'rrsc' (640, "ATAMgr") {
	kUniversal,
	AllCombos,
	{MiscDir},
	"ATAMgr.rsrc",

	{
		'nlib',
		{ -20186 /*ATAManager*/ };
	}
};

resource 'rrsc' (650, "USB") {
	kUniversal,
	AllCombos,
	{MiscDir},
	"USB.rsrc",

	{
		'nlib',
		{ -20776 /*USBServicesLib*/, -20777 /*USBFamilyExpertLib*/, -20778 /*USBManagerLib*/ };
		'ndrv',
		{ -20776 /*pciclass,0c0310*/ };
		'usbd',
		{ -20776 /*USBHubDriver0*/, -20777 /*USBHubDriver1*/, -20778 /*USBHIDKeyboardModule*/, -20779 /*USBHIDMouseModule*/, -20780 /*USBCompositeDriver*/ };
		'usbf',
		{ -20776 };
		'usbs',
		{ -20781 /*USBShimKeyboard*/, -20782 /*USBShimMouse*/ };
		'ndrv',
		{ -20777 /*USBUnitTableStorageDriver*/ };
		'usbs',
		{ -20776 /*USBMassStorageLoader*/ };
		'usbd',
		{ -20781 /*USBMassStorageClassDriver*/, -20782 /*USBMassStorageVSDriver*/ };
	}
};

resource 'rrsc' (660, "FireWire") {
	kUniversal,
	AllCombos,
	{MiscDir},
	"FireWire.rsrc",

	{
		'ndrv',
		{ -21143 /*fw609e,10483*/ };
		'fexp',
		{ -21140 /*ComponentDriverExpert*/, -21141 /*GenericDriverFamilyExpert*/ };
		'frag',
		{ -21140 /*FWPCIScanner*/, -21141 /*FWExpertRegistration*/, -21142 /*sbp609e,104d8*/ };
		'gpch',
		{ 1207 /*Main*/ };
		'ndrv',
		{ -20994 /*sbp609e,104d8*/ };
	}
};

The 68k ROM for NewWorld Macs
=============================
This repo is part of the *CDG5* project. It contains reversed sources and unlinked object files sufficient to build a 3 MB 68k ROM for a NewWorld Mac (that's a "ROM-in-RAM" Mac). The build result is a byte-perfect copy of the ROM inside the final "Mac OS ROM" release.

Fixing line endings
-------------------

MPW requires old-style Mac line endings (CR), while Git works better with Unix line endings (LF). Git filters can be used to convert between the two. Files committed to the repo are "cleaned" (LF-ed), and then "smudged" (CR-ed) when they hit the working tree. After cloning, append these snippets to your Git config.

Append this to `.git/config`:

	[filter "maclines"]
		clean = LC_CTYPE=C tr \\\\r \\\\n
		smudge = LC_CTYPE=C tr \\\\n \\\\r

Append this to `.git/info/attributes`:

	* filter=maclines
	*.lib -filter
	*.o -filter
	.gitignore -filter

Finally, do a once-off "re-smudge":

	rm -rf ../mac-rom/*
	git checkout .

Building
--------
This code is built with the [Macintosh Programmer's Workshop](https://en.wikipedia.org/wiki/Macintosh_Programmer%27s_Workshop) (MPW), which runs on the Classic Mac OS. To satisfy the memory requirements of the build process, the MPW Shell should get a memory partition of at least 16 MB. Once you have MPW set up, the build process is not particularly fussy.

Not many computers run the Classic Mac OS any more. Here are a few workarounds:

* Just find a Mac running Mac OS 7.5-9.2. (Not much fun if it's also your test machine.)
* Use the Classic environment on a PowerPC Mac running Mac OS X 10.4 or earlier. (A small PowerBook or iBook is perfect.)
* Use [EMPW](https://github.com/elliotnunn/empw) ("Emulated MPW"), a package of command-line tools, emulators and OS images that lets you run MPW commands straight from your macOS Terminal. This is my preferred solution.

Once MPW is set up, the build command is:

	EasyBuild

Using EMPW, that's:

	empw EasyBuild

The 3 MB image will be at `BuildResults/RISC/Image/RomMondo`.

What's next?
------------
The 3 MB 68k ROM needs to be linked into a 4 MB PowerPC ROM before it can be compressed inside a bootable Mac OS ROM file. So on to <https://github.com/elliotnunn/powermac-rom>.

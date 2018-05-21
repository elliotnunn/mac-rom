#!/bin/sh

# Avoid the uber-slow step of running the emulator when nothing has changed

if [ ! -f BuildResults/RISC/Image/RomMondo ]
then
	echo "RomMondo not yet built"
	echo "> Starting emulator to build RomMondo"
	empw EasyBuild
	echo "< Emulator done"
	exit
fi

echo "Checking for files updated since RomMondo"
find . ! -regex '.*/\..*' ! -iname '*.dmg' -newer BuildResults/RISC/Image/RomMondo | grep . || exit 0

echo "> Starting emulator to build RomMondo"
empw EasyBuild
echo "< Emulator done"

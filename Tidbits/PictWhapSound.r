/*
				File:		PictWhapSound.r
			
				Contains:	A sound resource which is played when FKEY 3 is executed
			
				Written by:	Bo3b Johnson
			
				Copyright:	� 1990 by Apple Computer, Inc., all rights reserved.
			
				Change History (most recent first):
			
		 <1>	 9/16/90	csd		first checked in
				 9/16/90	csd		xxx put comment here xxx
			
*/

/* 8/17/90: B3B:
	This is the sound that a camera makes when taking a picture.  Rather
	than lug around a resedit file for it, I just derezzed it to get it here,
	since it is pretty small.  It is about 4K big, and is sampled down at
	11K Hz, to make it smaller.  The sound is thus owned by the FKEY, but
	it's OK if it gets lost or used for other purposes.  Specifically, we
	give it no name so that it won't show up in the list of beeps in the cdev.
*/
	
data 'snd ' (-16504, "", purgeable) {
	$"00 01 00 01 00 05 00 00 00 A0 00 01 80 51 00 00"
	$"00 00 00 14 00 00 00 00 00 00 0F C6 26 00 00 00"
	$"00 00 0F C4 00 00 0F C5 00 3C 80 7F 7F 7F 7F 7B"
	$"7B 7D 7F 7C 7A 85 7C 78 70 9D 60 97 5D 91 59 96"
	$"8A 51 B5 7A 5A 7A 9F 56 A6 43 91 22 60 FF F9 59"
	$"73 49 8A 77 FE 00 95 00 83 FB 7D 9F 9A 6A E7 69"
	$"84 8A 2E CB 4F AB 36 81 81 C0 8E 7D 78 85 A6 4C"
	$"A2 67 8A 73 A3 8D 72 86 70 A6 7B 70 9B 74 6F B7"
	$"49 E0 00 CD 4C EC 0A BA 83 69 A3 6B 89 43 FF 37"
	$"7B 96 39 85 7B AC 15 67 9E FF C2 31 60 A2 9D 70"
	$"55 85 84 62 91 BC 00 D4 8E 5A 8E 70 6F 78 72 6A"
	$"5C 7F 6B 9A 80 74 72 9E 65 80 72 7F 74 A6 44 76"
	$"73 8A 73 73 74 80 6F 84 7D 63 73 70 88 70 7A 96"
	$"51 93 58 77 74 7D 70 6F 6D 83 80 77 6F 6F 86 67"
	$"8C 6E 7C 7B 7D 7B 6E 76 73 88 6E 78 66 85 7A 84"
	$"6F 73 73 6E 78 6A 81 5A 85 6F 8C 72 59 9E 6A 7A"
	$"74 8A 60 6F 84 5E 86 6D 92 4F B8 62 95 6F 80 80"
	$"89 74 7C 6E 7F 7D 85 80 6B 76 72 92 67 90 78 85"
	$"7B 81 7C 89 8E 6E 8C 70 90 83 7D 97 6E 85 83 7C"
	$"86 6F 8D 76 9F 6A 62 FF 00 E1 26 E9 36 C2 83 7B"
	$"6D 59 7C 97 7A 6D BC 77 83 90 6E 9D 49 B1 53 7A"
	$"69 90 6E 8A 97 81 9B 96 8D 9E 83 7F 69 A2 53 A2"
	$"73 6E 70 7A 8E 6B AC 5D 9E 69 A2 66 81 84 8A 84"
	$"7F 95 60 8E 83 A4 6A AA 69 85 77 88 77 77 84 74"
	$"8D 8D 89 86 80 92 85 95 89 83 7B 76 9D 73 7D 81"
	$"7B 8D 7A 8E 8C 7D 8A 84 96 84 81 85 90 80 8A 93"
	$"80 A2 73 96 83 81 89 95 86 90 7D 8E 85 88 83 96"
	$"8D 86 88 89 8A 85 99 7F 96 76 90 85 92 73 9D 7B"
	$"9B 84 95 8A 96 90 8A 7A 93 7B 83 90 8D 89 91 89"
	$"85 90 7C 8E 8D 84 8C 91 91 81 89 86 8D 8A 95 96"
	$"77 85 84 85 96 90 AA 65 9F 62 B7 7A A0 89 84 73"
	$"86 91 9E 89 88 85 61 81 86 9B 97 6B 7D 76 70 93"
	$"7D C5 53 56 C1 1C FF 28 B8 86 33 C9 24 FF 00 FF"
	$"00 FB 07 E0 72 83 7F 89 25 E5 2F D4 54 91 58 93"
	$"67 BC 5A A0 55 B5 26 DA 1C DF 60 5C 89 61 83 88"
	$"7F 78 84 32 AC 51 9F 5A 9A 59 6E 61 99 78 85 6A"
	$"81 2F BC 58 84 9D 5E 66 73 66 A7 5C A7 58 7A 4D"
	$"93 69 8C 74 6B 63 7A 65 85 5D 93 9B 00 CE 33 BD"
	$"72 8D 77 19 85 BE 37 8A 93 46 73 6B 88 A8 5E 74"
	$"C2 0E AB 53 8D A0 4B 99 3A 62 C7 47 AD 95 2F 83"
	$"7A 61 AD 6A 81 70 1C EC 15 BA AD 65 74 89 48 B8"
	$"B0 55 C0 29 85 9B 53 A6 86 AB 28 9F 74 95 7A CB"
	$"50 47 8A 70 B1 9B 76 91 3F 8E 90 93 7C BD 42 8A"
	$"86 6F A2 83 97 7C 55 77 95 9B 83 92 97 50 A7 78"
	$"90 81 AB 92 55 99 69 AA 74 AA AA 65 56 78 8D AB"
	$"65 90 96 49 7B A0 B3 53 9B 91 61 6F 7D A8 77 95"
	$"59 BC 65 6D 81 BC 65 8A 72 92 72 77 88 8D 90 84"
	$"7C 74 6E 93 69 A0 69 62 8C 6B 9A 67 83 76 7D 7F"
	$"7D 80 80 86 7A 73 83 7B 73 80 7D 7C 6F 83 73 7F"
	$"77 7F 7B 7A 6D 85 77 70 7D 7F 74 78 89 7B 77 77"
	$"80 76 7A 7B 7C 7C 6F 7B 88 78 7A 89 7D 6E BC 25"
	$"92 A3 84 12 FA 2D 7D D3 3A 7F 8D 43 D6 49 8C 81"
	$"58 B8 74 8C 6E 69 7F 99 7C 7F 6D 89 9B 70 7F 84"
	$"88 7D 72 89 6F 78 81 81 89 7A 84 80 88 77 84 83"
	$"7D 84 83 8D 83 8E 7A 8D 86 84 81 8D 7F 91 7F 83"
	$"8D 7B 89 85 8D 8A 8A 86 84 8C 86 8C 89 86 80 80"
	$"83 7F 8C 80 83 7D 83 76 89 7B 81 81 86 76 80 88"
	$"7C 81 83 7F 7D 77 7B 7D 80 80 80 7A 7C 7D 78 7D"
	$"76 7F 7B 76 7F 77 86 6E 81 76 80 77 7D 76 7F 74"
	$"7F 7D 89 7B 80 83 7B 74 89 6B 80 76 78 7C 7D 78"
	$"81 80 80 7D 7A 85 7B 89 81 7D 76 80 77 85 77 80"
	$"78 7F 7D 7D 81 7C 89 7D 7F 88 7D 7F 84 77 7D 80"
	$"88 7A 84 7A 7B 7F 7C 7F 7F 77 89 7B 7F 80 85 7F"
	$"80 83 85 83 81 84 85 81 7F 85 81 85 85 81 84 81"
	$"81 86 84 84 80 85 83 83 84 7D 7F 80 80 83 88 81"
	$"81 85 84 85 83 86 84 85 86 86 86 86 84 86 85 85"
	$"85 86 83 84 84 83 84 81 85 83 84 85 85 81 83 84"
	$"85 84 85 84 84 81 84 84 85 85 86 85 80 86 80 81"
	$"81 81 81 80 83 81 7F 83 81 80 7F 80 83 81 7F 7D"
	$"7D 7C 7C 7C 7C 7D 7B 7D 7C 7B 7D 7C 7B 78 7D 78"
	$"7C 7A 7C 7A 7B 7A 7A 78 78 7B 7C 78 78 7A 76 7B"
	$"76 7B 7C 78 7A 77 78 77 7C 7A 7B 7B 7B 7A 7C 7A"
	$"77 7A 77 7A 77 7A 78 78 77 7B 78 78 77 78 74 76"
	$"76 78 78 78 78 7A 78 7A 7A 76 78 77 77 76 78 76"
	$"76 76 76 76 78 78 77 7B 78 7B 7B 7B 7A 7A 7B 7C"
	$"7C 80 7D 7D 7C 7D 7C 7C 7D 7D 7D 7B 7C 7A 7C 7C"
	$"7B 7D 7B 7C 7D 7B 7F 7C 7D 7D 7F 7F 7F 80 7D 80"
	$"7D 81 80 81 80 81 84 81 83 83 83 83 84 83 84 84"
	$"83 84 84 84 86 84 85 85 85 83 84 83 84 81 85 83"
	$"84 81 85 83 81 85 84 81 80 81 83 80 83 83 81 83"
	$"83 83 83 81 83 80 81 80 7F 80 7F 7F 80 7F 7D 7C"
	$"7C 7D 7D 7D 7F 7B 7D 7D 7D 80 80 80 81 80 7F 7D"
	$"7D 7F 7F 7D 7D 7C 7C 7A 7B 7A 7B 7B 7F 7B 7F 84"
	$"78 80 80 7D 7D 83 7B 81 7D 7F 7F 80 83 74 95 72"
	$"81 96 59 73 7D 92 4F AA 96 81 6F 8E 70 7A 7F 73"
	$"89 62 99 76 8C 85 7C 7D 77 72 81 74 66 91 73 7F"
	$"8E 7A 88 93 83 95 93 77 7D 7A 78 8D 6D 7A 8E 84"
	$"83 8E 83 88 78 8C 88 7F 78 89 8D 8A 81 85 81 84"
	$"86 86 80 81 80 83 88 86 86 7D 85 85 7D 7D 8A 84"
	$"8D 8C 8E 8C 8D 85 85 88 7A 86 84 80 85 89 8A 86"
	$"83 86 86 8D 89 8D 88 8C 88 8A 88 8E 80 8A 7F 8A"
	$"83 85 7D 8A 7F 88 88 86 81 88 80 8C 85 86 7D 8A"
	$"83 89 81 89 84 84 8A 86 8D 83 86 8A 84 89 84 8C"
	$"88 85 89 89 88 86 86 89 83 88 81 8A 83 8A 84 8A"
	$"85 88 8E 84 8D 91 70 92 91 67 9A 89 78 95 99 63"
	$"AB 77 90 9D 74 97 73 8D 86 7F 7A 83 83 81 7B 92"
	$"77 A0 7A 6D 84 67 7F 6F A3 5E AF 5C B4 85 B8 5E"
	$"A2 4B C5 18 BA 40 E7 00 FF 44 BE 6D 72 AD 60 61"
	$"96 6B 55 85 A2 8A 8D B1 6D 96 49 97 8C 85 8D 6B"
	$"A0 74 AF 48 C6 31 9E 36 88 66 9D 6D 8C B8 7B 80"
	$"BC 6A 89 4F 9A 77 2E 8C 96 59 39 DA 69 A3 4D 99"
	$"5E 6B CF 13 CE 47 AD 42 9D 42 A4 70 B8 72 58 97"
	$"7D 56 C0 6A 70 84 7B 70 66 96 8D 6E 8A 9F 74 65"
	$"90 8D 61 7D 9A 6F 62 77 95 44 9E 70 9D 42 B3 3F"
	$"9E 6E 93 6A A0 5A 9A 74 8A 8A 6D 80 77 83 61 9A"
	$"9E 55 8A 8D 5D A8 6E 7A 69 A2 6E 9F 3A AD 7A 84"
	$"7A 6B 99 7B 83 76 63 89 A0 5C 9B 6A 81 76 96 7A"
	$"8E 5E 81 7D 84 7B 8C 77 77 80 8D 81 8C 65 7C 84"
	$"81 89 80 6B 84 5E A6 88 85 7D 8C 7F 91 73 81 7C"
	$"7B 7F 93 76 85 6D 97 7F 83 86 7A 73 80 81 86 8A"
	$"7B 85 8C 77 92 84 88 76 88 7D 7C 88 7F 88 7F 84"
	$"74 90 78 92 7D 86 7A 86 7F 86 77 88 7C 83 81 7C"
	$"86 78 80 83 77 7B 80 78 78 70 84 78 7F 84 77 86"
	$"7F 84 85 73 88 76 80 78 8A 74 7A 80 7C 7C 80 7A"
	$"83 7A 7D 78 85 6F 7A 7C 7A 80 78 80 7C 7B 7D 7D"
	$"7B 76 7B 77 7C 76 7A 77 7A 7D 76 7D 78 7A 7A 78"
	$"78 76 76 78 77 78 74 7B 78 7A 76 77 77 76 72 7A"
	$"77 76 78 76 76 7A 7A 7F 7C 83 7A 80 78 7B 7D 7A"
	$"86 7C 7D 7B 83 74 7F 7B 77 7D 7A 7A 7F 7D 7B 7D"
	$"7D 78 7F 80 7B 7B 7D 7F 7A 85 7B 85 83 84 83 81"
	$"83 80 86 81 80 80 85 7D 81 80 84 81 80 80 84 80"
	$"81 83 7C 83 83 85 7F 88 81 81 83 81 81 7C 86 7F"
	$"86 83 85 86 88 85 8C 85 85 8A 85 83 81 83 84 85"
	$"81 83 85 83 81 7F 83 80 84 80 7D 88 80 83 85 84"
	$"7F 88 81 85 85 81 84 86 88 84 86 85 85 85 86 85"
	$"81 83 86 81 86 83 85 83 85 81 86 84 80 86 7F 89"
	$"81 80 7D 88 7C 7F 80 7D 81 80 7D 83 78 84 7B 84"
	$"83 7C 7F 83 7C 7F 7C 7D 81 80 7C 80 7F 7D 7F 7D"
	$"7F 78 7D 7C 7D 7F 7C 7B 7C 7F 7B 7D 7C 7C 7F 7A"
	$"7C 7B 7B 7C 7A 7F 7A 7D 77 7D 7D 78 7C 7C 74 81"
	$"7D 78 78 76 7C 81 7C 7D 81 7C 83 7C 85 77 84 7D"
	$"7D 7C 81 7F 7C 7F 7F 81 7C 84 7B 7F 7A 7D 7D 7C"
	$"81 81 80 85 83 7F 81 88 86 84 84 83 84 84 83 83"
	$"84 81 85 84 86 84 88 84 8D 84 89 88 86 89 85 8C"
	$"84 8D 86 85 88 81 89 83 88 84 86 89 85 8C 84 88"
	$"86 84 81 84 84 84 84 88 8A 83 86 86 85 84 8A 86"
	$"88 83 88 86 81 85 85 84 84 81 88 80 81 86 84 83"
	$"85 84 84 85 84 83 81 7F 83 84 81 81 80 81 85 7D"
	$"83 81 83 84 83 81 7D 80 7F 7F 7F 7F 7B 7B 83 77"
	$"7D 78 77 7A 78 7A 73 7D 7A 76 80 77 7A 80 7F 78"
	$"80 7B 7D 7C 7F 7F 84 7B 83 7D 7D 80 81 7C 80 7A"
	$"7A 7A 77 7C 74 7C 73 78 77 7B 77 7A 77 78 7C 74"
	$"74 77 7A 78 7A 76 77 7D 76 78 7C 78 7B 78 7B 77"
	$"77 7A 78 78 73 77 78 78 7A 6F 76 73 78 77 77 77"
	$"77 73 7A 6D 76 7B 73 76 73 77 70 7C 74 77 6F 76"
	$"74 78 6F 7B 74 76 78 78 76 7B 7B 77 7B 80 78 76"
	$"8A 62 89 6B 90 5D 92 5C 96 77 90 77 90 6D 95 7C"
	$"78 80 80 6F 89 77 7F 73 84 77 7D 7A 81 80 77 86"
	$"80 7F 86 88 85 7C 89 80 7D 8C 77 83 7C 7D 7D 86"
	$"7D 80 8D 7F 90 83 88 89 86 86 81 89 7B 88 7D 7D"
	$"77 86 7C 7D 7C 80 7A 80 84 7C 7B 84 77 88 78 83"
	$"7B 7F 7A 7F 72 81 88 67 88 85 67 85 90 76 7C 78"
	$"84 73 7C 81 7F 74 7A 80 73 70 80 7C 73 7B 7D 86"
	$"6B 8A 62 97 70 80 7A 85 7A 86 77 81 70 7D 73 8A"
	$"70 7B 7D 78 7D 7F 80 77 7F 7F 78 81 7B 7D 78 7B"
	$"7C 7A 78 7B 83 7A 7C 80 77 7C 7F 88 73 86 7A 78"
	$"84 7F 83 7F 80 7C 89 70 8A 77 86 83 91 84 7D 89"
	$"78 84 83 83 84 8D 83 86 74 83 90 7B 89 90 81 92"
	$"61 92 91 85 93 6E 9E 7F 78 8C 84 85 95 74 8C 78"
	$"83 7D 97 83 8E 6D 9A 78 8D 85 8E 81 93 85 9B 7A"
	$"7F 90 8A 92 85 8D 8D 86 80 96 84 9D 7D 9F 6E 96"
	$"90 88 9B 8E 8C 7D 99 76 A7 78 9B 77 91 6F 93 84"
	$"8C 86 8A 85 86 85 84 8C 8A 8C 90 89 88 92 89 90"
	$"89 89 8C 83 90 8C 8E 84 88 81 83 7A 8E 90 8A 84"
	$"90 84 91 86 8E 86 88 85 8A 86 8A 8C 86 8C 85 8C"
	$"84 8A 86 85 86 86 84 86 88 8A 86 88 81 84 81 89"
	$"85 86 81 80 81 81 84 84 81 84 80 7D 86 83 80 85"
	$"83 7C 84 80 83 81 7F 86 81 80 84 83 81 83 7D 7D"
	$"7B 80 81 7C 7F 7D 7A 7D 7F 7B 7F 7A 7D 80 7B 81"
	$"7D 80 81 7F 7D 7D 81 7D 80 80 7D 7F 84 80 81 81"
	$"7D 81 7A 7C 7C 7C 7A 86 7A 83 80 7D 80 80 85 81"
	$"80 81 80 7C 80 84 80 80 83 80 81 83 81 7C 81 7B"
	$"7B 80 7B 7D 7B 7F 7A 7D 78 7D 7B 77 7D 7A 7C 7B"
	$"78 7C 7B 7D 7D 7D 7F 7D 81 7C 83 7F 81 7F 7C 7D"
	$"7C 81 7D 7D 7F 7D 7C 7B 7C 7A 78 7B 77 7B 7A 78"
	$"7A 7A 7A 77 7A 77 78 74 77 78 77 7A 7C 7A 7B 7C"
	$"7A 7A 7B 7C 7B 7A 7B 78 78 7A 78 7A 78 77 77 74"
	$"7A 7B 7D 78 7B 77 77 7B 7C 76 77 7B 7B 78 7C 7B"
	$"7A 77 77 7A 77 77 77 7A 7A 7A 7B 7C 7C 7A 7C 7B"
	$"7A 7A 78 7A 78 7A 7D 7B 7C 7A 7B 7A 7A 77 78 7A"
	$"78 77 78 77 77 78 77 78 76 77 76 77 76 78 74 78"
	$"74 77 76 74 78 78 78 7A 77 77 77 77 78 78 78 7B"
	$"7A 7C 7F 80 80 81 80 83 80 7F 7F 7F 7D 7F 7D 80"
	$"7D 7F 7D 7F 80 80 80 7D 7F 7D 7D 7D 7D 7D 7F 7F"
	$"7F 80 7F 7F 80 7F 7D 80 7F 7F 83 81 84 83 84 84"
	$"84 83 84 84 84 86 85 86 85 86 86 88 88 89 86 86"
	$"85 85 84 84 83 84 83 84 84 83 84 85 85 84 84 83"
	$"84 83 84 83 85 85 84 85 85 84 85 85 83 83 84 84"
	$"83 84 85 85 85 86 86 86 85 86 84 85 85 85 85 86"
	$"86 84 86 85 86 85 86 85 85 85 86 89 88 88 88 86"
	$"88 88 88 86 85 85 86 84 84 84 83 84 83 83 83 81"
	$"81 81 80 81 81 7F 7F 81 80 80 80 80 81 83 81 81"
	$"81 80 80 7F 81 7D 80 7F 7F 7F 7F 7F 7F 7D 80 7F"
	$"7D 7F 7F 7D 7D 80 7F 7F 7F 7F 80 80 80 81 81 83"
	$"83 83 83 84 84 85 85 86 83 84 83 81 81 81 81 80"
	$"83 83 83 83 83 81 81 80 83 80 80 81 80 81 80 7F"
	$"7F 7F 7F 81 80 83 84 83 84 84 83 83 84 83 85 83"
	$"80 81 83 80 81 80 80 7D 7C 7D 7D 80 7C 83 7B 80"
	$"7A 84 7B 83 7A 85 7B 81 7D 83 7B 80 7D 7D 7A 7D"
	$"7F 7A 7D 7C 7D 7A 7F 7C 7F 7A 7D 7A 7C 78 7C 7B"
	$"7B 7A 7D 7B 80 7D 7D 7C 80 7F 7F 7F 81 80 7F 7D"
	$"86 84 85 7F 7F 7D 84 84 7C 7B 81 7F 85 84 81 7C"
	$"84 86 84 83 83 84 83 84 84 7F 80 80 7F 7C 7D 7D"
	$"7C 7D 7D 7D 7C 7C 7F 7F 7D 7C 7D 7D 7D 7C 7D 7C"
	$"7C 7C 7F 7C 7B 7A 7C 7C 7F 7B 7D 7D 80 7D 80 7C"
	$"7F 7F 80 7F 7F 7D 80 7F 80 7F 7F 7F 80 7D 80 7F"
	$"80 7F 7F 7D 7D 7D 80 7F 80 7D 80 81 81 81 81 83"
	$"83 83 83 81 81 81 81 81 81 80 80 80 7F 7F 7D 7D"
	$"7F 7D 7D 7F 7F 7F 81 81 80 81 81 81 81 81 80 81"
	$"81 81 81 83 83 84 83 84 83 84 83 85 85 85 84 84"
	$"84 83 84 83 83 84 84 85 85 85 85 86 85 85 85 85"
	$"85 84 85 85 85 86 86 88 88 89 88 88 88 88 86 89"
	$"89 89 88 89 88 8A 85 89 88 86 88 84 86 85 85 85"
	$"83 84 84 85 84 88 85 85 88 86 85 86 83 84 83 83"
	$"81 84 81 83 80 80 83 80 81 80 83 81 81 84 84 84"
	$"83 84 83 85 81 81 7D 80 80 83 80 84 80 81 80 83"
	$"80 80 80 7F 80 7F 7F 7F 80 81 81 81 81 80 7F 7F"
	$"7F 7F 7F 7D 7D 7C 7C 7C 7D 7C 7D 7C 7D 7D 7F 7C"
	$"7D 7C 7D 7C 7B 7B 7C 7B 7C 7C 7D 7C 7C 7C 7C 7D"
	$"7C 7B 7B 7B 7A 7B 7B 7A 7B 7B 7A 78 78 77 77 77"
	$"76 76 74 74 74 74 74 76 76 74 74 73 73 72 70 70"
	$"72 6F 6F 6F 70 72 72 73 74 74 76 77 76 76 74 74"
	$"73 74 74 73 74 73 74 74 73 73 73 74 73 74 74 76"
	$"76 77 78 78 78 7A 7B 7A 7A 77 7A 78 78 78 78 77"
	$"77 73 74 73 74 72 74 74 74 73 73 74 74 73 73 74"
	$"74 74 76 77 76 77 78 78 78 78 78 78 78 78 78 7A"
	$"7A 78 78 78 7A 78 78 7A 7A 7C 7C 7C 7D 7F 7F 7D"
	$"7F 80 7F 7F 7D 80 7D 7D 7F 7F 80 80 80 84 82 83"
	$"83 84 84 84 82 82 82 80 80 80 80 82 80 80 80 82"
	$"82 82 82 82 83 83 82 84 84 83 84 85 84 84 84 85"
	$"84 84 84 84 84 84 85 86 87 87 87 86 86 84 84 84"
	$"84 84 84 84 84 84 84 84 84 85 86 85 87 87 87 87"
	$"87 87 87 87 87 87 87 87 87 87 87 88 89 8A 8A 8A"
	$"8B 8B 8B 8A 8A 8A 8A 8A 8A 8A 8A 8A 8A 8A 8A 8A"
	$"8A 8A 89 89 88 88 88 88 88 88 88 89 88 88 89 89"
	$"89 89 89 89 89 8A 8A 8B 8B 8A 8A 8A 8A 89 88 87"
	$"87 87 87 87 87 87 87 87 87 87 86 86 86 86 86 86"
	$"86 86 86 85 85 85 85 85 84 84 83 83 83 83 84 84"
	$"84 84 84 84 84 84 83 82 82 82 82 82 82 82 82 82"
	$"82 82 82 82 82 82 82 82 82 82 82 81 81 81 81 81"
	$"81 81 80 80 80 80 80 80 80 80 80 80 80 80 80 80"
	$"7F 7F 7F 7F 7F 7F 7F 7F 7F 7F 7F 7F 7F 7F 7F 7F"
	$"7F 7F 7F 7E 7E 7D 7C 7C 7C 7C 7B 7B 7A 7A 7A 7A"
	$"7B 7B 7B 7B 7B 7B 7B 7B 7B 7B 7B 7B 7B 7B 7B 7B"
	$"7B 7B 7B 7A 79 7A 7A 79 79 79 79 79 78 78 78 78"
	$"78 78 78 78 78 78 79 79 79 79 79 79 79 79 79 7A"
	$"7A 7A 7A 7A 7A 7A 7A 7A 7A 7A 7A 7A 7A 7A 7B 7B"
	$"7B 7B 7B 7B 7B 7B 7A 7A 7A 7A 7A 7A 7A 7A 7A 7A"
	$"7A 7A 7A 7A 7A 7A 7A 7A 7A 7B 7B 7B 7B 7B 7B 7C"
	$"7D 7D 7D 7D 7D 7D 7D 7D 7C 7C 7C 7C 7C 7C 7C 7C"
	$"7C 7C 7C 7C 7C 7D 7D 7E 7E 7E 7E 7E 7E 7E 7E 7E"
	$"7E 7E 7E 7E 7E 7E 7E 7E 7E 7E 7E 7E 7E 7E 7E 7E"
	$"7E 7E 80 80 80 80 80 80 80 80 80 80 80 80 80 80"
	$"80 80 80 80 80 80 80 80 80 80 80 80 80 80 80 80"
	$"80 80 80 80 80 80 80 80 80 80 80 80 80 80 80 80"
};



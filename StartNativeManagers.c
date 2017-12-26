#include <Memory.h>
#include <Types.h>

OSErr GetSharedLibrary(
  unsigned char *libName,
  long archType,
  long options,
  long *connID,
  Ptr *mainAddr,
  Str255 errMessage) = {0x3F3C,0x0001,0xAA5A};


void myfunc(void)
{
	THz z, y;
	Ptr p;
	Ptr mainAddr;
	Str255 scratch;
	OSErr err;

	z = GetZone();
	y = *(THz *)0x2A6;
	SetZone(y);

	p = NewPtrSys(8);
	if(p)
	{
		err = GetSharedLibrary("\pUSBFamilyExpertLib", 'pwpc', 1, (long *)(p + 4), &mainAddr, scratch);
		if(!err)
		{
			SetZone(z);
		}
	}
}

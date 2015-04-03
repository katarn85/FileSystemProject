#include "driverlayer.h"

int main()
{
	EraseAllSectors();

	UINT16 answer = ReadWord(0);

	WriteWord(0, 0x0000);

	WriteWord(nFileSizeBytes - 2, 0x0000);

	answer = ReadWord(0);

	answer = ReadWord(nFileSizeBytes - 2);

	return 0;
}

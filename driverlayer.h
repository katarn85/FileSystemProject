#include <windows.h>

#define nFileSizeBytes 1310720

void EraseAllSectors()
{
	HANDLE memory = CreateFile( "memory.dat",
				(GENERIC_READ | GENERIC_WRITE),
				0,
				OPEN_ALWAYS,
				FILE_ATTRIBUTE_NORMAL);

	LPVOID freshMemorySector = HeapAlloc(GetProcessHeap(),
					HEAP_GENERATE_EXCEPTIONS,
					nFileSizeBytes/20);

	FillMemory(freshMemorySector,
		nFileSizeBytes/20,
		0xFF);

	for(int sect = 0, sect < 20, sect++)
	{
		WriteFile( memory,
			freshMemorySector,
			nFileSizeBytes/20);
	}

	HeapFree(GetProcessHeap(),
		0,
		freshMemorySector);
}

void EraseSector(int nSectorNr)
{
	HANDLE memory = CreateFile( "memory.dat",
				GENERIC_WRITE,
				0,
				OPEN_ALWAYS,
				FILE_ATTRIBUTE_NORMAL);

	LPVOID freshMemorySector = HeapAlloc(GetProcessHeap(),
					HEAP_GENERATE_EXCEPTIONS,
					nFileSizeBytes/20);

	FillMemory(freshMemorySector,
		nFileSizeBytes/20,
		0xFF);}

}

void ReadWord(int nAddress)
{
	HANDLE memory = CreateFile( "memory.dat",
			GENERIC_WRITE,
			0,
			OPEN_ALWAYS,
			FILE_ATTRIBUTE_NORMAL);}

}

void WriteWord(int nAddress, int nWord)
{
	HANDLE memory = CreateFile( "memory.dat",
			GENERIC_WRITE,
			0,
			OPEN_ALWAYS,
			FILE_ATTRIBUTE_NORMAL);}

}

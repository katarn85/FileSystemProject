#include <windows.h>

#define nFileSizeBytes 1310720

void EraseAllSectors()
{
	DWORD dwBytesWritten = 0;

	HANDLE memory = CreateFile( "memory.bin",
				(GENERIC_READ | GENERIC_WRITE),
				0,
				NULL,
				OPEN_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				NULL);

	LPVOID freshMemorySector = HeapAlloc(GetProcessHeap(),
					HEAP_GENERATE_EXCEPTIONS,
					nFileSizeBytes/20);

	FillMemory(freshMemorySector,
		nFileSizeBytes/20,
		0xff);

	for(int sect = 0; sect < 20; sect++){
	
		WriteFile( memory,
			freshMemorySector,
			nFileSizeBytes/20,
			&dwBytesWritten,
			NULL);
	}

	HeapFree(GetProcessHeap(),
		0,
		freshMemorySector);

	CloseHandle(memory);
}

void EraseSector(int nSectorNr)
{
	HANDLE memory = CreateFile(  "memory.bin",
				(GENERIC_READ | GENERIC_WRITE),
				0,
				NULL,
				OPEN_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				NULL);

	LPVOID freshMemorySector = HeapAlloc(GetProcessHeap(),
					HEAP_GENERATE_EXCEPTIONS,
					nFileSizeBytes/20);

	FillMemory(freshMemorySector,
		nFileSizeBytes/20,
		0xFF);

	CloseHandle(memory);
	
}

void ReadWord(int nAddress)
{
	HANDLE memory = CreateFile( "memory.bin",
				(GENERIC_READ | GENERIC_WRITE),
				0,
				NULL,
				OPEN_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				NULL);

	CloseHandle(memory);
	
}

void WriteWord(int nAddress, int nWord)
{
	HANDLE memory = CreateFile( "memory.bin",
				(GENERIC_READ | GENERIC_WRITE),
				0,
				NULL,
				OPEN_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				NULL);

	CloseHandle(memory);
	
}

#include <windows.h>

#define nFileSizeBytes 1310720

enum layerErrors
{
	noError,
	invalidAddress,
	fileNotFound

} layerError = noError;


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
	
	layerError = (GetLastError() == 0) ? fileNotFound : noError;

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
	if(nSectorNr > 19 || nSectorNr < 0)
	{
		layerError = invalidAddress;
		return;
	}

	DWORD dwBytesWritten = 0;

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
	
	SetFilePointer(memory,
			nSectorNr * nFileSizeBytes/20,
			NULL,
			FILE_BEGIN);

	WriteFile( memory,
		freshMemorySector,
		nFileSizeBytes/20,
		&dwBytesWritten,
		NULL);

	HeapFree(GetProcessHeap(),
		0,
		freshMemorySector);

	CloseHandle(memory);
	
}

UINT16 ReadWord(int nAddress)
{
	if(nAddress < 0 || nAddress > nFileSizeBytes || nAddress % 2 != 0)
	{
		layerError = invalidAddress;
		return 0x0000;
	}

	DWORD dwBytesRead = 0;
		
	HANDLE memory = CreateFile( "memory.bin",
				(GENERIC_READ | GENERIC_WRITE),
				0,
				NULL,
				OPEN_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				NULL);

	SetFilePointer(memory,
			nAddress,
			NULL,
			FILE_BEGIN);
	
	UINT16 dReadValue;

	ReadFile(memory,
		&dReadValue,
		2,
		&dwBytesRead,
		NULL);

	CloseHandle(memory);
	
	return dReadValue;
}

void WriteWord(int nAddress, UINT16 nWord)
{
	if(nAddress < 0 || nAddress > nFileSizeBytes || nAddress % 2 != 0)
	{
		layerError = invalidAddress;
		return;
	}

	DWORD dwBytesWritten = 0;

	nWord = nWord & ReadWord(nAddress);

	HANDLE memory = CreateFile( "memory.bin",
				(GENERIC_READ | GENERIC_WRITE),
				0,
				NULL,
				OPEN_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				NULL);

	SetFilePointer(memory,
			nAddress,
			NULL,
			FILE_BEGIN);

	WriteFile(memory,
		&nWord,
		2,
		&dwBytesWritten,
		NULL);



	CloseHandle(memory);
	
}

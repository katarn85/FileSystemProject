#include <stdio.h>

void EraseAllSectors()
{
	FILE* memory;
	
	// Attempt to open file, test for null return.
	// If null, create file then open as r+.
	if(!(memory = fopen("memory.dat", "r+")))
	{
		memory = fopen("memory.dat", "w");
		fclose(memory);
		memory = fopen("memory.dat", "r+");
	}
}

void EraseSector(int nSectorNr)
{
	FILE* memory;

	if(!(memory = fopen("memory.dat", "r+")))
	{
		memory = fopen("memory.dat", "w");
		fclose(memory);
		memory = fopen("memory.dat", "r+");
	}

}

void ReadWord(int nAddress)
{
	FILE* memory;

	if(!(memory = fopen("memory.dat", "r+")))
	{
		memory = fopen("memory.dat", "w");
		fclose(memory);
		memory = fopen("memory.dat", "r+");
	}

}

void WriteWord(int nAddress, int nWord)
{
	FILE* memory;

	if(!(memory = fopen("memory.dat", "r+")))
	{
		memory = fopen("memory.dat", "w");
		fclose(memory);
		memory = fopen("memory.dat", "r+");
	}

}

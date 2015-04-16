#include "FileAPI.h"
#include <string.h> 

// **************************************** User API ****************************************

// In progress
322_FILE CSC322_fopen(const char *filename,
		      const char *mode)
{
	// Check if file is open
	// Return Failure if so.
	
	
	
	FILEHEADER searchHeader;
	UINT32 searchLocation = 0;
	bool found = false;

	while(searchLocation < nSectorSizeBytes*19)
	{
		readBuffer(&searchHeader,
			   searchLocation,
			   sizeof(FILEHEADER));

		if(!strcmp(filename, searchHeader.filename) && searchHeader.portionType == PORTION_ALLOC)
		{
			found = true;
			break;
		}
	       	else if(searchHeader.portionType == PORTION_FREE && nextSector(searchLocation) == 19)
		{
			break;
		}
		else if(searchHeader.portionType == PORTION_FREE)
		{
			searchLocation = nextSector(searchLocation)*nSectorSizeBytes;
			continue;
		}

		searchLocation += sizeof(FILEHEADER) + searchHeader.nFileSizeWords/2;

	}

	if(!found)
	{


	
	
}

int CSC322_fclose(322_FILE *stream)
{
}

int CSC322_fread( LPVOID buffer,
		int size,
		int count,
		322_FILE *stream)
{
}

int CSC322_fwrite(LPVOID buffer,
		int size,
		int count,
		322_FILE *stream)
{
}

int CSC322_fseek(322_FILE *stream,
	  long offset,
	  int origin)
{
	
}

bool CSC322_fdelete(const char *filename)
{
}

// *********************************** Service Functions *************************************


322_FILE* findOpenFile(const char *filename)
{
}

// In progress
322_FILE* createFile(const char *filename,
	       	     const char *mode)
{
	FNODE newFNODE;
	
	strcpy(&newFNODE.filename, filename);
	
	if(!strcmp(mode, "ab")
		newFNODE.type = ab;
	else if(!strcmp(mode, "wb"))
		newFNODE.type = wb;
	else if(!strcmp(mode, "rb"))
		newFNODE.type = rb;
	else
		return invalidFILE;

	LPVOID pFNODE = HeapAlloc(GetProcessHeap(),
				     0,
				     sizeof(FNODE));
}

// Complete, not tested
void readBuffer(LPVOID buffer,
		UINT32 location,
		int lengthBytes)
{
	int word;

	for(word = 0; word < lengthBytes/2*2; word++)
	{
		*(buffer + word*2) = ReadWord(location + word*2);
	}
	
	if(lengthBytes % 2 == 1)
	{
		*(buffer + word*2 + 1) = (ReadWord(location + word*2 + 2) >> 8);
	}
}

int nextSector(int nLocationBytes)
{

}


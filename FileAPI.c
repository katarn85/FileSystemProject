#include <string.h>

#define PORITON_FREE 0xFF
#define PORTION_ALLOC = 0x0F
#define PORTION_USED = 0x00

// **************************************** User API ****************************************

// In progress
CSC322FILE *CSC322_fopen(const char *filename,
		      const char *mode)
{
	// (PSEU)	
	// Check if file is open
	// Return Failure if so.
	
	FILEHEADER searchHeader;
	UINT32 searchLocation = 0;
	bool found = false;

	while(thisSector(searchLocation) < 19)
	{
		readBuffer(&searchHeader,
			   searchLocation,
			   sizeof(FILEHEADER));

		if(strcmp(filename, searchHeader.filename) != 0 && searchHeader.portionType == 0x0F)
		{
			found = true;
			break;
		}
	       	else if(searchHeader.portionType == 0xFF && thisSector(searchLocation) == 19)
		{
			break;
		}
		else if(searchHeader.portionType == 0xFF)
		{
			searchLocation = (1 + thisSector(searchLocation))*nSectorSizeBytes;
			continue;
		}

		searchLocation += sizeof(FILEHEADER) + searchHeader.nFileSizeWords*2;

	}

	if(!found)
		return NULL;

	CSC322FILE *requested = createFile(filename,
					   mode);

	requested->headerLocation = searchLocation;
	requested->filesize = searchHeader.nFileSizeWords*2;
	requested->modified = 0;

	requested->inMemoryFile = HeapAlloc(GetProcessHeap(),
				    0,
				    requested->filesize);


	readBuffer(requested->inMemoryFile,
		   requested->headerLocation + HEADER_SIZE_BYTES,
		   requested->filesize);

	switch(requested->type)
	{
		case wb:
		case wpb:
		case rb: requested->filepointer = requested->inMemoryFile; break;
		case ab: requested->filepointer = (char *)requested->inMemoryFile + requested->filesize; break;
		default: requested->filepointer = NULL; break;
	}

	return requested;
}

// Complete, not tested. Check on being passed old pointers, handle recursion on garbage collect. 
int CSC322_fclose(CSC322FILE *stream)
{
	if(!stream->modified)
	{
		closeNode(stream->filename);
		return 0;
	}

	FILEHEADER usedHeader;

	readBuffer(&usedHeader,
		   stream->headerLocation,
		   sizeof(FILEHEADER));

	usedHeader.portionType = 0x00;

	writeBuffer(&usedHeader,
		    stream->headerLocation,
		    sizeof(FILEHEADER));

	FILEHEADER searchHeader;
	UINT32 searchLocation = 0;
	bool found = false;

	while(thisSector(searchLocation) < 19)
	{
		readBuffer(&searchHeader,
			   searchLocation,
			   sizeof(FILEHEADER));

		if(searchHeader.portionType == 0xFF && thisSector(searchLocation)*nSectorSizeBytes - (searchLocation + sizeof(FILEHEADER)) >= stream->filesize)
		{
			found = true;
			break;
		}
		else if(searchHeader.portionType == 0xFF)
		{
			searchLocation = (1 + thisSector(searchLocation))*nSectorSizeBytes;
			continue;
		}

		searchLocation += sizeof(FILEHEADER) + searchHeader.nFileSizeWords*2;

	}

	if(!found)
	{
		garbageCollect();
		CSC322_fclose(stream);
	}

	strcpy(searchHeader.filename, stream->filename);

	searchHeader.portionType = 0x0F;
	searchHeader.nFileSizeWords = stream->filesize/2 + stream->filesize%2;

	writeBuffer(&searchHeader,
		    searchLocation,
		    sizeof(FILEHEADER));

	writeBuffer(stream->inMemoryFile,
		    searchLocation + sizeof(FILEHEADER),
		    stream->filesize);

	closeNode(stream->filename);

	return 0;
}

int CSC322_fread( LPVOID buffer,
		int size,
		int count,
		CSC322FILE *stream)
{
	return 0;
}

int CSC322_fwrite(LPVOID buffer,
		int size,
		int count,
		CSC322FILE *stream)
{
	return 0;
}

// Complete, not tested.
int CSC322_fseek(CSC322FILE *stream,
	  long offset,
	  int origin)
{
	if(origin == SEEK_SET)
	{
		if(offset >= stream->filesize || offset < 0)
			return 1;

		(char *)stream->filepointer = (char *)stream->inMemoryFile + offset;

		return 0;
	}
	else if(origin == SEEK_END)
	{
		if(offset > 0 || filesize - offset < 0)
			return 1;

		(char *)stream->filepointer = (char *)stream->inMemoryFile + (filesize - offset);

		return 0;
	}
	else if(origin == SEEK_CUR)
	{
		if((char *)stream->filepointer + offset > (char *)stream->inMemoryFile + filesize || (char *)stream->filepointer + offset < (char *)stream->inMemoryFile)
			return 1;

		(char *)stream->filepointer += offset;

		return 0;
	}
	else
		return 2;
}

long CSC322_ftell(CSC322FILE *stream)
{
	return long((char *)stream->filepointer - (char *)stream->inMemoryFile);
}

bool CSC322_remove(const char *filename)
{
	return 0;
}

// *********************************** Service Functions *************************************


CSC322FILE* findOpenFile(const char *filename)
{
	return NULL;
}

// In progress
CSC322FILE* createFile(const char *filename,
	       	     const char *mode)
{
	FNODE newFNODE;
	
	strcpy(newFNODE.file.filename, filename);
	
	if(!strcmp(mode, "ab"))
		newFNODE.file.type = ab;
	else if(!strcmp(mode, "wb"))
		newFNODE.file.type = wb;
	else if(!strcmp(mode, "rb"))
		newFNODE.file.type = rb;
	else if(!strcmp(mode, "w+b"))
		newFNODE.file.type = wpb;
	else
		return NULL;

	FNODE *pFNODE = (FNODE *)HeapAlloc(GetProcessHeap(),
					     0,
					     sizeof(FNODE));

	*pFNODE = newFNODE;

	// (PSEU)
	// Append to open file list
	
	return &(pFNODE->file);
}

// Complete, not tested
void closeNode(const char *filename)
{
	FNODE *pSearch = head, *pPrev = head;

	while(pSearch != NULL && !strcmp(pSearch->file.filename, filename))
	{
		pSearch = pSearch->next;
		pPrev = pSearch;
	}

	if(pSearch == NULL)
		return;

	pPrev->next = pSearch->next;

	HeapFree(GetProcessHeap(),
		 0,
		 pSearch);

	return;
}

// Complete, not tested. 
void readBuffer(LPVOID buffer,
		UINT32 location,
		int lengthBytes)
{
	int word = 0;

	// Misaligned first byte.
	if(location % 2 == 1)
	{
		*(UINT8 *)buffer = ReadWord(location - 1);
		word++;
	}

	// All aligned words.
	for(word; word < lengthBytes/2*2; word++)
	{
		*(UINT16 *)((char *)buffer + word*2) = ReadWord(location + word*2);
	}
	
	// Misaligned last byte.
	if(lengthBytes % 2 == 1 && location % 2 == 1)
	{
		*(UINT8 *)((char *)buffer + word*2 + 1) = (ReadWord(location + word*2 + 2) >> 8);
	}
}

// Complete, not tested.
void writeBuffer(LPVOID buffer,
		 UINT32 location,
		 int lengthBytes)
{
	int word = 0;
	UINT16 data;

	// Misaligned first byte.
	if(location % 2 == 1)
	{
		data = ReadWord(location - 1);
		data = (data & 0xFF00) | (*(UINT8 *)buffer);
		WriteWord(location - 1, data);
		word++;
	}

	// All aligned words.
	for(word; word < lengthBytes/2*2; word++)
	{
		data = *(UINT16 *)((char *)buffer + word*2);
		WriteWord(location + word, data);
	}

	// Misaligned last byte.
	if(lengthBytes % 2 == 1 && location % 2 == 1)
	{
		data = ReadWord(location + word*2 + 2);
		data = (data & 0x00FF) | ( *(UINT16 *)((char *)buffer + word*2 + 1) << 8);
		WriteWord(location + word + 2, data);
	}
}

// Complete, not tested
int thisSector(int nLocationBytes)
{
	int sector = 0;

	while(nLocationBytes / nSectorSizeBytes < sector)
		sector++;

	return sector;
}

void garbageCollect()
{
}

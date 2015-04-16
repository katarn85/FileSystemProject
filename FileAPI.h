#include "driverlayer.h"

enum accessType
{
	rb,
	wb,
	ab
};

typedef struct
{
	char filename[64];
	UINT8 portionType;
	UINT8 nAllocatedBlocks;
	DWORD nFileSizeWords;
} FILEHEADER

#define PORTION_FREE 0xFF
#define PORTION_ALLOC = 0x0F
#define PORTION_USED = 0x00

#define HEADER_SIZE_BYTES 96

typedef struct
{
	char filename[64];
	LPVOID filepointer;
	accessType type;
	int headerLocation;
	int filesize;	
	LPVOID inMemoryFile;
} 322_FILE

typedef struct
{
	322_FILE file;
	322_FILE *next;
} FNODE

FNODE *head = NULL;

// **************************************** User API ****************************************

322_FILE CSC322_fopen(const char *filename,
		      const char *mode);

int CSC322_fclose(322_FILE *stream);

int CSC322_fread(LPVOID buffer,
		 int size,
		 int count,
		 322_FILE *stream);

int CSC322_fwrite(LPVOID buffer,
		  int size,
		  int count,
		  322_FILE *stream);

int CSC322_fseek(322_FILE *stream,
		 long offset,
		 int origin);

bool CSC322_fdelete(const char *filename);

// *********************************** Service Functions *************************************


322_FILE* findOpenFile(const char *filename);

322_FILE* createFile(const char *filename,
	       	     const char *mode);

void readBuffer(LPVOID buffer,
		UINT32 location,
		int lengthBytes);

int nextSector(int nLocationBytes);



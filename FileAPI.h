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
	DWORD filepointer;
	accessType type;
	DWORD FATRecord;
	DWORD filesize;	
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

int CSC322_fread( LPVOID buffer,
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


bool FAT_Exists();

void buildTables();

322_FILE* findOpenFile(const char *filename);

322_FILE* createFile(const char *filename,
	       	     const char *mode);




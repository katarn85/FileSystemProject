#include "FileAPI.h"

// **************************************** User API ****************************************

322_FILE CSC322_fopen(const char *filename,
		      const char *mode){}

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


bool FAT_Exists()
{
}

void buildTables()
{
}

322_FILE* findOpenFile(const char *filename)
{
}

322_FILE* createFile(const char *filename,
	       	     const char *mode)
{
}

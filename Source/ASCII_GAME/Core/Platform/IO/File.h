#ifndef _IO_FILE_H_
#define _IO_FILE_H_

#include <stdlib.h>

extern char rootDirectory[_MAX_PATH];

//file structure
struct iofileType
{
	iofileType() { filesize = 0; pfile = nullptr; }
	
	unsigned long filesize;
	FILE *pfile;

	//member functions
	bool Open(const char *filename, const char* mode = "rb");
	bool ReadBytes(unsigned int size, char* buffer);
	bool WriteBytes(unsigned int size, char* buffer);
	bool Close();

	unsigned long Length() { return filesize; }

	

	//destruction
	~iofileType( ){}
};

#endif //_FILE_H_

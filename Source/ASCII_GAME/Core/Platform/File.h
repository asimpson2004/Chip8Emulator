#ifndef _FILE_H_
#define _FILE_H_

#include <stdlib.h>

extern char rootDirectory[_MAX_PATH];

//file structure
struct fileType
{
	//construction
	fileType( )	{ buffer = nullptr; }
	
	//members
	unsigned long size;
	char * buffer;

	//member functions
	bool load(const char *filename );
	bool save(const char *filename );

	//destruction
	~fileType( )	{ if ( buffer ) { free( buffer ); } }
};

#endif //_FILE_H_

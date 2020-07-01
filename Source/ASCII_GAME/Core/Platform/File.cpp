#include <stdio.h>
#include <string.h>

#include "File.h"

//define file data
char rootDirectory[_MAX_PATH];

//*************************************************************************
//name: file load
//desc:	opens and reads a file into a data buffer for manipulation
//args:	filename
//rets:	false: failed to open
//		true:  opened and loaded
//note:	n/a
//*************************************************************************
bool fileType::load(const char *filename )
{
	char path[_MAX_PATH];
	FILE *pfile;

	memset( path, 0, sizeof( path ) );

	strcpy_s( path, rootDirectory );
	strcat_s( path, filename );

	//open file
	fopen_s(&pfile, path, "rb" );
	if ( !pfile )
	{
		return false;
	}

	//file size
	fseek( pfile, 0, SEEK_END );
	size = ftell( pfile );

	//allocate memory
	if ( buffer ) free ( buffer );
	buffer = ( char * ) malloc ( size );
	memset( buffer, 0, size );
	
	//read file
	fseek( pfile, 0, SEEK_SET );
	fread( buffer, 1, size, pfile );

	//close file
	fclose( pfile );

	return true;
}

//*************************************************************************
//name: file save
//desc:	opens or creates a file, then writes the data buffer to it
//args:	filename
//rets:	false: failed to open
//		true:  opened/created and saved
//note:	untested as of yet!
//*************************************************************************
bool fileType::save(const char *filename )
{
	char path[256];
	FILE *pfile;

	//create filepath
	memset( path, 0, sizeof( path ) );

	strcpy_s( path, rootDirectory );
	strcat_s( path, filename );

	//open or create file
	fopen_s(&pfile, path, "wb" );
	if ( !pfile )
	{
		return false;
	}

	//write buffer to file
	fwrite( buffer, 1, size, pfile );

	//free buffer
	if ( buffer ) free ( buffer );

	//close file
	fclose( pfile );

	return true;
}

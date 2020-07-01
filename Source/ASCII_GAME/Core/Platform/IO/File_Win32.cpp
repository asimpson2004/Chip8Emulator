#include <stdio.h>
#include <string.h>

#include "File.h"

//define file data
//char rootDirectory[_MAX_PATH];

bool iofileType::Open(const char *filename, const char* mode)
{
	char path[_MAX_PATH];

	memset(path, 0, sizeof(path));

	strcpy_s(path, rootDirectory);
	strcat_s(path, filename);

	//open file
	fopen_s(&pfile, path, mode);
	if (!pfile)
	{
		return false;
	}

	//file size
	fseek(pfile, 0, SEEK_END);
	filesize = ftell(pfile);

	fseek(pfile, 0, SEEK_SET);

	return true;
}

bool iofileType::ReadBytes(unsigned int size, char* buffer)
{
	//TODO check file is open first?

	//read file
	fseek(pfile, 0, SEEK_SET);
	fread(buffer, 1, size, pfile);

	return true;
}

bool iofileType::WriteBytes(unsigned int size, char* buffer)
{
	//TODO Check file is open first?

	//TODO set where to write to? or write to end

	//write buffer to file
	fwrite(buffer, 1, size, pfile);

	return true;
}

bool iofileType::Close()
{
	//TODO Check file is open first?

	//close file
	fclose(pfile);

	return true;
}

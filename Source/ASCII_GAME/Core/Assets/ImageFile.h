#ifndef _IMAGE_FILE_H_
#define _IMAGE_FILE_H_

class ImageFile
{
public:

	ImageFile()
	:buffer(nullptr)
	,width(0.0)
	,height(0.0)
	,size(0.0)
	{	
	}

	~ImageFile() { if (buffer) delete(buffer); }
		
	unsigned char* buffer;
	long width;
	long height;
	long size;

	virtual bool load(const char *filename) = 0;
	
	virtual void horizontalFlip() = 0;
	virtual void verticalFlip() = 0;

};

#endif

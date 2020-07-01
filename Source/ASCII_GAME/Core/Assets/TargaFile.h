#include "ImageFile.h"

class TargaFile : public ImageFile
{
public:
	virtual bool load(const char* filename);
	virtual void horizontalFlip() {};
	virtual void verticalFlip() {};
};

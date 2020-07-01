#ifndef _FILE_LIST_MENU_COMPONENT_CREATE_H_
#define _FILE_LIST_MENU_COMPONENT_CREATE_H_

#include "ListMenuComponentCreate.h"

class FileListMenuComponentCreate : public ListMenuComponentCreate
{
public:

	FileListMenuComponentCreate();
	virtual ~FileListMenuComponentCreate();

	const char* m_FileDir;
	const char* m_FileExtension;

	virtual void InitialiseFromBinary(char*& buffer);

	virtual const int GetComponentType() const;

	virtual FileListMenuComponentCreate* Clone() const { return new FileListMenuComponentCreate(*this); }


};

#endif
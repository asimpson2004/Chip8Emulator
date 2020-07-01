#include "FileListMenuComponentCreate.h"
#include "../../../Components/ComponentType.h"
#include "../../GameDataHelpers.h"

FileListMenuComponentCreate::FileListMenuComponentCreate()
:m_FileDir("")
{

}

FileListMenuComponentCreate::~FileListMenuComponentCreate()
{

}

void FileListMenuComponentCreate::InitialiseFromBinary(char*& buffer)
{
	GDb::InitialiseFromBinary(&m_FileDir, buffer);
	GDb::InitialiseFromBinary(&m_FileExtension, buffer);
	ListMenuComponentCreate::InitialiseFromBinary(buffer);
}

const int FileListMenuComponentCreate::GetComponentType() const
{
	return (int)E_Component_Type::E_COMPONENT_TYPE_UI_FILE_LIST_MENU;
}

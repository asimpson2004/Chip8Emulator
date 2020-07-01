#include "ListMenuComponentCreate.h"
#include "../../GameDataHelpers.h"
#include "../../../Components/ComponentType.h"

void MenuItemCreate::InitialiseFromBinary(char*& buffer)
{
	GDb::InitialiseFromBinary(&m_DisplayText, buffer);
	GDb::InitialiseFromBinary(&m_Payload, buffer);
}

ListMenuComponentCreate::ListMenuComponentCreate()
:m_CircularMenu(false)
,m_MaxItemsToDisplay(0)
{
}

ListMenuComponentCreate::~ListMenuComponentCreate()
{
}

void ListMenuComponentCreate::InitialiseFromBinary(char*& buffer)
{
	GDb::InitialiseFromBinary(&m_CircularMenu, buffer);
	GDb::InitialiseFromBinary(&m_MaxItemsToDisplay, buffer);
	GDb::InitialiseFromBinary(&m_TextAlignment, buffer);
	GDb::InitialiseFromBinary(&m_MenuElements, buffer);
	ComponentCreate::InitialiseFromBinary(buffer);
}

const int ListMenuComponentCreate::GetComponentType() const
{ 
	 return (int)E_Component_Type::E_COMPONENT_TYPE_UI_LIST_MENU;
}

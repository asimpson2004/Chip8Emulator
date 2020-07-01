#ifndef _LIST_MENU_COMPONENT_CREATE_H_
#define _LIST_MENU_COMPONENT_CREATE_H_

#include "../ComponentCreate.h"
#include "../../../Components/ComponentType.h"
#include "TextAlignmentType.h"

class MenuItemCreate : public GDb::C_DataItem
{
public:
	const char* m_DisplayText;
	const char* m_Payload;

	virtual void InitialiseFromBinary(char*& buffer);
};

class ListMenuComponentCreate : public ComponentCreate
{
public:

	ListMenuComponentCreate();
	virtual ~ListMenuComponentCreate();

	bool m_CircularMenu;
	int m_MaxItemsToDisplay;
	E_TextAlignmentType m_TextAlignment;
	GDb::C_Array<MenuItemCreate> m_MenuElements;

	virtual void InitialiseFromBinary(char*& buffer);

	virtual const int GetComponentType() const;

	virtual ListMenuComponentCreate* Clone() const { return new ListMenuComponentCreate(*this); }


};

#endif

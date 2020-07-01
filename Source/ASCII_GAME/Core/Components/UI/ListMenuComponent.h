#ifndef _LIST_MENU_COMPONENT_H_
#define _LIST_MENU_COMPONENT_H_

#include "../Component.h"
#include "../../Maths/Vector2.h"
#include <vector>
#include <string>

#include "../../GameDatabase/CreationData/UI/TextAlignmentType.h"

class ComponentCreate;
class GameObject;
class ASCIIRenderer;
class Message;

struct MenuItem
{
	std::string m_DisplayText;
	std::string m_Payload;
};

class ListMenuComponent : public Component
{
public:
	ListMenuComponent(const ComponentCreate* pComponentCreate, GameObject* pOwner);
	virtual ~ListMenuComponent();

	virtual void Initialise();
	virtual void Update(float delta);
	virtual void Render(ASCIIRenderer* pRenderer);
	virtual void OnMessage(Message* pMessage);

protected:

	Vector2 GetAlignedPosition(const Vector2& position, int menuItemIndex) const;
	int GetMenuItemLength(int index) const;

	std::vector<MenuItem> m_MenuItems;
	Vector2 m_Position;
	int m_SelectedItem;
	bool m_CircularMenu;
	int m_MaxItemsToDisplay;

	int m_DisplayStartIndex;
	int m_DisplayEndIndex;

	E_TextAlignmentType m_TextAlignment;
};

#endif

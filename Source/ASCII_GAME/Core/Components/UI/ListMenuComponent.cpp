#include "ListMenuComponent.h"

#include "../../Renderer/ASCIIRenderer.h"
#include "../../GameDatabase/CreationData/ComponentCreate.h"
#include "../../GameDatabase/CreationData/UI/ListMenuComponentCreate.h"

#include "../../Input/InputDevice.h"
#include "../../Input/InputManager.h"

#include "../../Messages/MenuItemSelectedMessage.h"

ListMenuComponent::ListMenuComponent(const ComponentCreate* pComponentCreate, GameObject* pOwner)
:Component(pComponentCreate, pOwner)
,m_SelectedItem(0)
{	
}

ListMenuComponent::~ListMenuComponent()
{
}

void ListMenuComponent::Initialise()
{
	const ListMenuComponentCreate* pListMenuComponentCreate = dynamic_cast<const ListMenuComponentCreate*>(m_pCreationData);
	if (pListMenuComponentCreate)
	{
		m_TextAlignment = pListMenuComponentCreate->m_TextAlignment;
		m_CircularMenu = pListMenuComponentCreate->m_CircularMenu;
		m_MaxItemsToDisplay = pListMenuComponentCreate->m_MaxItemsToDisplay;

		for (unsigned int i = 0; i < pListMenuComponentCreate->m_MenuElements.size(); ++i)
		{
			MenuItem menuItem;
			menuItem.m_DisplayText = pListMenuComponentCreate->m_MenuElements[i].m_DisplayText;
			menuItem.m_Payload = pListMenuComponentCreate->m_MenuElements[i].m_Payload;
			m_MenuItems.push_back(menuItem);
		}

		m_DisplayStartIndex = 0;
		m_DisplayEndIndex = m_MaxItemsToDisplay == 0 ? m_MenuItems.size() : min(m_MaxItemsToDisplay, m_MenuItems.size())-1;
	}
}

void ListMenuComponent::Update(float delta)
{
	UNUSED_VARIABLE(delta);

	InputDevice* pInputDevice = InputManager::Instance()->GetInputDevice();
	if (pInputDevice)
	{
		if (pInputDevice->GetButtonInput(E_DigitalInput_DpadUp).OnPressed())
		{
			if (m_CircularMenu)
			{
				m_SelectedItem = (m_MenuItems.size() + --m_SelectedItem) % m_MenuItems.size();
			}
			else
			{
				m_SelectedItem--;
				if (m_SelectedItem < 0)
				{
					m_SelectedItem = 0;
				}
			}

			if (m_MaxItemsToDisplay > 0)
			{
				if (m_DisplayStartIndex > m_SelectedItem)
				{
					m_DisplayStartIndex = m_SelectedItem;
					m_DisplayEndIndex = min(m_SelectedItem + (m_MaxItemsToDisplay), m_MenuItems.size())-1;
				}
			}

		}

		if (pInputDevice->GetButtonInput(E_DigitalInput_DpadDown).OnPressed())
		{
			if (m_CircularMenu)
			{
				m_SelectedItem = (++m_SelectedItem) % m_MenuItems.size();
			}
			else
			{
				m_SelectedItem++;
				if (m_SelectedItem >= m_MenuItems.size())
				{
					m_SelectedItem = m_MenuItems.size() - 1;
				}
			}

			if (m_MaxItemsToDisplay > 0)
			{
				if (m_DisplayEndIndex < m_SelectedItem)
				{
					m_DisplayEndIndex = m_SelectedItem;
					m_DisplayStartIndex = max(m_SelectedItem - (m_MaxItemsToDisplay-1), 0);
				}
			}
		}

		if (pInputDevice->GetButtonInput(E_DigitalInput_PAUSE).OnPressed())
		{
			MenuItemSelectedMessage menuItemSelectedMessage;
			menuItemSelectedMessage.m_MenuItem = m_MenuItems[m_SelectedItem].m_Payload;

			BroadcastMessageToGameObject(&menuItemSelectedMessage);
		}
	}
}

void ListMenuComponent::Render(ASCIIRenderer* pRenderer)
{

	pRenderer->PushMatrix();

	pRenderer->Translate(m_Position);

	Vector2 currentTranslation = pRenderer->GetMatrix().GetTranslation2D();

	if (m_MaxItemsToDisplay != 0)
	{
		if (m_DisplayStartIndex > 0)
		{
			CHAR_INFO pixel;
			pixel.Attributes = BACKGROUND_BLACK | FOREGROUND_WHITE;
			pixel.Char.UnicodeChar = '^';
			pRenderer->SetPixel((int)currentTranslation.x, (int)currentTranslation.y, &pixel, 100);
		}
		currentTranslation.y++;
	}

	for (unsigned int i = 0; i <= (m_MaxItemsToDisplay == 0 ? m_MenuItems.size()-1 : (m_DisplayEndIndex - m_DisplayStartIndex)); ++i)
	{
		int y = i; 
		unsigned int itemIndex = m_DisplayStartIndex + i;

		Vector2 alignedPosition = GetAlignedPosition(currentTranslation, itemIndex);

		for (unsigned int x = 0; x < m_MenuItems[itemIndex].m_DisplayText.size(); ++x)
		{
			CHAR_INFO pixel;
			pixel.Attributes = m_SelectedItem == itemIndex ? BACKGROUND_WHITE | FOREGROUND_BLACK : BACKGROUND_BLACK | FOREGROUND_WHITE;
			pixel.Char.UnicodeChar = m_MenuItems[itemIndex].m_DisplayText[x];

			pRenderer->SetPixel((int)alignedPosition.x + x, (int)alignedPosition.y + y, &pixel, 100);
		}

	}

	if (m_MaxItemsToDisplay != 0)
	{
		if (m_DisplayEndIndex < m_MenuItems.size() - 1)
		{
			CHAR_INFO pixel;
			pixel.Attributes = BACKGROUND_BLACK | FOREGROUND_WHITE;
			pixel.Char.UnicodeChar = 'v';
			pRenderer->SetPixel((int)currentTranslation.x, (int)currentTranslation.y + m_MaxItemsToDisplay, &pixel, 100);
		}
	}

	pRenderer->PopMatrix();
}

void ListMenuComponent::OnMessage(Message* pMessage)
{
	UNUSED_VARIABLE(pMessage);
}

Vector2 ListMenuComponent::GetAlignedPosition(const Vector2& position, int menuItemIndex) const
{
	Vector2 alignedPosition = position;

	switch (m_TextAlignment)
	{
		case E_TextAlignmentType_Left:
		{
			//do nothing
		}
		break;
		case E_TextAlignmentType_Centre:
		{
			int currentMenuItemLength = GetMenuItemLength(menuItemIndex);
			alignedPosition.x -= currentMenuItemLength >> 0x1;
		}
		break;
		case E_TextAlignmentType_Right:
		{
			int currentMenuItemLength = GetMenuItemLength(menuItemIndex)-1;
			alignedPosition.x -= currentMenuItemLength;
		}
		break;
	}

	return alignedPosition;
}

int ListMenuComponent::GetMenuItemLength(unsigned int index) const
{
	int menuItemLength = 0;

	if (index >= 0 && index < m_MenuItems.size())
	{
		menuItemLength = m_MenuItems[index].m_DisplayText.size();
	}

	return menuItemLength;
}

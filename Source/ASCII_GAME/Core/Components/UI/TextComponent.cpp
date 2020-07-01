#include "TextComponent.h"
#include "../../Renderer/ASCIIRenderer.h"
#include "../../GameDatabase/CreationData/UI/TextComponentCreate.h"

TextComponent::TextComponent(const ComponentCreate* pComponentCreate, GameObject* pOwner)
:Component(pComponentCreate, pOwner)
{
	const TextComponentCreate* pTextComponentCreate = dynamic_cast<const TextComponentCreate*>(pComponentCreate);
	if (pTextComponentCreate)
	{
		m_DisplayText = pTextComponentCreate->m_DisplayText;
		m_TextAlignment = pTextComponentCreate->m_TextAlignment;
		m_Position.x = pTextComponentCreate->m_Position.x;
		m_Position.y = pTextComponentCreate->m_Position.y;
	}
}

TextComponent::~TextComponent()
{
}

void TextComponent::Initialise()
{
}

void TextComponent::Update(float delta)
{

}

void TextComponent::Render(ASCIIRenderer* pRenderer)
{
	pRenderer->PushMatrix();

	pRenderer->Translate(m_Position);

	Vector2 currentTranslation = pRenderer->GetMatrix().GetTranslation2D();
	Vector2 alignedPosition = GetAlignedPosition(currentTranslation);

	for (int x = 0; x < m_DisplayText.size(); ++x)
	{
		CHAR_INFO pixel;
		pixel.Attributes = FOREGROUND_WHITE;
		pixel.Char.UnicodeChar = m_DisplayText[x];

		pRenderer->SetPixel(alignedPosition.x + x, alignedPosition.y, &pixel, 100);
	}

	pRenderer->PopMatrix();

}

void TextComponent::OnMessage(Message* pMessage)
{

}

Vector2 TextComponent::GetAlignedPosition(const Vector2& position) const
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
		int currentMenuItemLength = m_DisplayText.size();
		alignedPosition.x -= currentMenuItemLength >> 0x1;
	}
	break;
	case E_TextAlignmentType_Right:
	{
		int currentMenuItemLength = m_DisplayText.size() - 1;
		alignedPosition.x -= currentMenuItemLength;
	}
	break;
	}

	return alignedPosition;
}

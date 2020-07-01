#include "TextComponentCreate.h"
#include "../../GameDataHelpers.h"
#include "../../../Components/ComponentType.h"

TextComponentCreate::TextComponentCreate()
{

}

TextComponentCreate::~TextComponentCreate()
{

}

void TextComponentCreate::InitialiseFromBinary(char*& buffer)
{
	GDb::InitialiseFromBinary(&m_TextAlignment, buffer);
	GDb::InitialiseFromBinary(&m_DisplayText, buffer);
	GDb::InitialiseFromBinary(&m_Position, buffer);
	ComponentCreate::InitialiseFromBinary(buffer);
}

const int TextComponentCreate::GetComponentType() const
{
	return (int)E_Component_Type::E_COMPONENT_TYPE_UI_TEXT;
}

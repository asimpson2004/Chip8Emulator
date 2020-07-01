#ifndef _TEXT_COMPONENT_CREATE_H_
#define _TEXT_COMPONENT_CREATE_H_

#include "../ComponentCreate.h"
#include "TextAlignmentType.h"
#include "../../Vector2D.h"

class TextComponentCreate : public ComponentCreate
{
public:

	TextComponentCreate();
	virtual ~TextComponentCreate();

	E_TextAlignmentType m_TextAlignment;
	const char* m_DisplayText;
	GDb::C_Vector2d m_Position;

	virtual void InitialiseFromBinary(char*& buffer);

	virtual const int GetComponentType() const;

	virtual TextComponentCreate* Clone() const { return new TextComponentCreate(*this); }


};

#endif

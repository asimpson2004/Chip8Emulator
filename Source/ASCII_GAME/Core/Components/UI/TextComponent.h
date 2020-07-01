#ifndef _TEXT_COMPONENT_H_
#define _TEXT_COMPONENT_H_

#include "../Component.h"
#include "../../GameDatabase/CreationData/UI/TextAlignmentType.h"
#include "../../Maths/Vector2.h"
#include <string>

class ComponentCreate;
class GameObject;
class ASCIIRenderer;
class Message;

class TextComponent : public Component
{
public:
	TextComponent(const ComponentCreate* pComponentCreate, GameObject* pOwner);
	virtual ~TextComponent();

	virtual void Initialise();
	virtual void Update(float delta);
	virtual void Render(ASCIIRenderer* pRenderer);
	virtual void OnMessage(Message* pMessage);

protected:

	Vector2 GetAlignedPosition(const Vector2& position) const;

	std::string m_DisplayText;
	Vector2 m_Position;
	E_TextAlignmentType m_TextAlignment;
};

#endif

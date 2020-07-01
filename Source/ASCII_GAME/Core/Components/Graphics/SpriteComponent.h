#ifndef _SPRITE_COMPONENT_H_
#define _SPRITE_COMPONENT_H_

#include <Windows.h>
#include "../Component.h"
#include "../ComponentType.h"
#include "../../Maths/Vector2.h"
#include "../../Maths/Rect.h"
#include "../../Renderer/AsciiRendererInterface.h"

class GameObject;
class AsciiTexture;
class SpriteComponentCreate;

class SpriteComponent : public Component, public AsciiRendererInterface
{
public:
	SpriteComponent(const SpriteComponentCreate* pCreationData, GameObject* pOwner);
	virtual ~SpriteComponent();

	virtual void Update(float delta);
	virtual void Render(ASCIIRenderer* pRenderer);
	virtual void OnMessage(Message* pMessage);

private:

	void Initialise(const int* pixels, const Vector2& size);
	void Initialise(const CHAR_INFO* pixels, const Vector2& size);
	void Initialise(const char* pixels, int attributes, const Vector2& size);
	void Initialise(const char* filename);

	void SetPosition(int x, int y) { m_Position.x = x; m_Position.y = y; }
	void SetPosition(Vector2& position) { m_Position = position; }

	Vector2 GetPosition() { return m_Position; }
	Vector2 GetSize() { return m_Size; }

	void SetTexture(const char* filename);
	void SetTextureRect(Rect& textureRect);
	void SetOrigin(Vector2& origin);

	int GetWrappedTextureX(int xPos);
	int GetWrappedTextureY(int yPos);

	char GetLayer() { return m_Layer;}
	void SetLayer(char layer) { m_Layer = layer; }

	void Cleanup();

	bool m_bInitialised;

	Vector2 m_Position;
	Vector2 m_Size;

	Vector2 m_Origin;
	Rect m_TextureRect;

	CHAR_INFO** m_PixelData;
	AsciiTexture* m_pTexture;

	char m_Layer;

	unsigned int m_FilenameHashValue;

	float m_Timer;

	const SpriteComponentCreate* m_pCreationData;
};

#endif

#include "SpriteComponent.h"
#include "../../Renderer/ASCIIRenderer.h"

#include "../../Assets/AssetManager.h"
#include "../../Assets/ImageFile.h"
#include "../../Utils/Types.h"
#include "../../Utils/Utils.h"
#include "../../Renderer/AsciiTexture.h"

#include "../../Messages/Message.h"
#include "../../Messages/SetSpriteRectMessage.h"
#include "../../Messages/MessageType.h"

#include "../../GameDatabase/CreationData/SpriteComponentCreate.h"

SpriteComponent::SpriteComponent(const SpriteComponentCreate* pCreationData, GameObject* pOwner)
	:Component(pCreationData, pOwner)
	,m_bInitialised(false)
	,m_PixelData(nullptr)
	,m_FilenameHashValue(0)
	,m_Timer(0.f)
	,m_Layer(0)
{

	if (!pCreationData)
		return;

	m_pCreationData = pCreationData;

	m_Layer = pCreationData->m_Layer;

	const SpriteComponentTextCreate* pSpriteTextCreate = dynamic_cast<const SpriteComponentTextCreate*>(pCreationData);
	if (pSpriteTextCreate)
	{
		Initialise(pSpriteTextCreate->m_Pixels, pSpriteTextCreate->m_SpriteColour, Vector2(pSpriteTextCreate->m_SpriteSize.x, pSpriteTextCreate->m_SpriteSize.y));
		return;
	}

	const SpriteComponentCharInfoCreate* pSpriteCharInfoCreate = dynamic_cast<const SpriteComponentCharInfoCreate*>(pCreationData);
	if (pSpriteCharInfoCreate)
	{
		Initialise(pSpriteCharInfoCreate->m_Pixels, Vector2(pSpriteCharInfoCreate->m_SpriteSize.x, pSpriteCharInfoCreate->m_SpriteSize.y));
		return;
	}
	
	const SpriteComponentIntCreate* pSpriteIntCreate = dynamic_cast<const SpriteComponentIntCreate*>(pCreationData);
	if (pSpriteIntCreate)
	{
		Initialise(pSpriteIntCreate->m_Pixels, Vector2(pSpriteCharInfoCreate->m_SpriteSize.x, pSpriteCharInfoCreate->m_SpriteSize.y));
		return;
	}

	const SpriteComponentFileCreate* pSpriteFileCreate = dynamic_cast<const SpriteComponentFileCreate*>(pCreationData);
	if (pSpriteFileCreate)
	{
		Initialise(pSpriteFileCreate->m_Filename);
		return;
	}
}

SpriteComponent::~SpriteComponent()
{
	for (int i = 0; i < m_Size.y; i++)
	{
		SAFE_DELETE_ARY(m_PixelData[i]);
	}

	SAFE_DELETE_ARY(m_PixelData);
}


void SpriteComponent::Initialise(const int* pixels, const Vector2& size)
{
	if (m_bInitialised)
		return;

	m_Size = size;

	m_PixelData = new CHAR_INFO * [m_Size.y];

	for (int i = 0; i < m_Size.y; i++)
	{
		m_PixelData[i] = new CHAR_INFO[m_Size.x];
	}

	for (int y = 0; y < m_Size.y; y++)
	{
		for (int x = 0; x < m_Size.x; x++)
		{
			m_PixelData[y][x].Char.UnicodeChar = 0;
			m_PixelData[y][x].Char.AsciiChar = 0;
			m_PixelData[y][x].Attributes = pixels[x + (y * (int)m_Size.x)];
		}
	}

	m_bInitialised = true;
}

void SpriteComponent::Initialise(const CHAR_INFO* pixels, const Vector2& size)
{
	if (m_bInitialised)
		return;

	m_Size = size;

	m_PixelData = new CHAR_INFO * [m_Size.y];

	for (int i = 0; i < m_Size.y; i++)
	{
		m_PixelData[i] = new CHAR_INFO[m_Size.x];
	}

	for (int y = 0; y < m_Size.y; y++)
	{
		for (int x = 0; x < m_Size.x; x++)
		{
			m_PixelData[y][x] = pixels[x + (y * (int)m_Size.x)];
		}
	}

	m_bInitialised = true;
}

void SpriteComponent::Initialise(const char* pixels, int attributes, const Vector2& size)
{
	if (m_bInitialised)
		return;

	m_Size = size;

	m_PixelData = new CHAR_INFO * [m_Size.y];

	for (int i = 0; i < m_Size.y; i++)
	{
		m_PixelData[i] = new CHAR_INFO[m_Size.x];
	}

	for (int y = 0; y < m_Size.y; y++)
	{
		for (int x = 0; x < m_Size.x; x++)
		{
			m_PixelData[y][x].Char.UnicodeChar = 0;
			m_PixelData[y][x].Char.AsciiChar = pixels[x + (y * (int)m_Size.x)];
			m_PixelData[y][x].Attributes = attributes;
		}
	}

	m_bInitialised = true;
}

void SpriteComponent::Initialise(const char* filename)
{
	if (m_bInitialised)
		return;

	m_pTexture = AssetManager::Instance()->GetAsciiTexture(filename);
	if (m_pTexture) {
		SetTextureRect(Rect(0.0f, 0.0f, m_pTexture->GetSize().x, m_pTexture->GetSize().y));
	}
	
	m_bInitialised = true;

}

void SpriteComponent::Update(float delta)
{
	m_Timer += delta;
}

void SpriteComponent::Render(ASCIIRenderer* pRenderer)
{
	if (!m_bInitialised)
		return;
	
	pRenderer->PushMatrix();

	pRenderer->Translate(m_Position);

	Vector2 currentTranslation = pRenderer->GetMatrix().GetTranslation2D();

	if (pRenderer)
	{
		for (int y = 0; y < m_TextureRect.h; y++)
		{
			for (int x = 0; x < m_TextureRect.w; x++)
			{
				int posx = currentTranslation.x + x;
				int posy = currentTranslation.y + y;
				const AsciiPixel& pixel = m_pTexture->GetPixelAtPosition(GetWrappedTextureX(m_TextureRect.x + x), GetWrappedTextureY(m_TextureRect.y + y));
				if (pixel.a > 0)
				{
					pRenderer->SetPixel(posx, posy, &pixel.rgb, m_Layer);
				}
			}
		}
	}
	

	pRenderer->PopMatrix();
	
}

int SpriteComponent::GetWrappedTextureX(int xPos)
{
	return xPos % (int)m_pTexture->GetSize().x;
}

int SpriteComponent::GetWrappedTextureY(int yPos)
{
	return yPos % (int)m_pTexture->GetSize().y;
}

void SpriteComponent::SetTexture(const char* filename)
{
	C_Hash32 filenameHash(filename);
	if (m_FilenameHashValue != filenameHash.GetHashValue())
	{
		Cleanup();
		Initialise(filename);
	}
}

void SpriteComponent::SetTextureRect(Rect& textureRect)
{
	m_TextureRect = textureRect;
}

void SpriteComponent::SetOrigin(Vector2& origin)
{
	m_Origin = origin;
}

void SpriteComponent::Cleanup()
{
	m_FilenameHashValue = 0;
	m_Origin = Vector2();
	m_TextureRect = Rect();
	m_Size = Vector2();
	m_bInitialised = false;
}

void SpriteComponent::OnMessage(Message* pMessage)
{
	switch (pMessage->GetMessageType())
	{
		case (int)E_MESSAGE_TYPE::SET_SPRITE_RECT:
		{
			SetSpriteRectMessage* pSetSpriteRectMessage = static_cast<SetSpriteRectMessage*>(pMessage);
			SetTextureRect(pSetSpriteRectMessage->SpriteRect);
		}
		break;
		default:
		{
			Component::OnMessage(pMessage);
		}
	}
}

#include "AssetManager.h"

#include "../Utils/Types.h"
#include "../Utils/Utils.h"

#include "ImageFile.h"
#include "TargaFile.h"

#include "SpritesheetDef.h"
#include "../Renderer/AsciiTexture.h"

#include <tinyxml2.h>

AssetManager* AssetManager::m_pInstance = nullptr;

AssetManager::AssetManager()
{
}

AssetManager::~AssetManager()
{
	for (std::map<unsigned int, ImageFile*>::iterator it = m_Textures.begin(); it != m_Textures.end(); ++it)
	{
		SAFE_DELETE_PTR(it->second);
	}

	for (std::map<unsigned int, AsciiTexture*>::iterator it = m_AsciiTextures.begin(); it != m_AsciiTextures.end(); ++it)
	{
		SAFE_DELETE_PTR(it->second);
	}

	for (std::map<unsigned int, SpritesheetDef*>::iterator it = m_SpritesheetDefs.begin(); it != m_SpritesheetDefs.end(); ++it)
	{
		SAFE_DELETE_PTR(it->second);
	}
}

AssetManager* AssetManager::Instance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new AssetManager();
	}

	return m_pInstance;
}

ImageFile* AssetManager::GetTexture(const char* filename)
{
	// look to see if we have already loaded the file
	C_Hash32 filenameHash(filename);

	std::map<unsigned int, ImageFile*>::iterator iter = m_Textures.find(filenameHash.GetHashValue());

	if (iter != m_Textures.end())
	{
		//file is already loaded, return a reference
		return iter->second;
	}

	//file is not loaded.. let's load it now
	if (LoadTextureFromFile(filename))
	{
		return GetTexture(filename);
	}
	return nullptr;
}

bool AssetManager::LoadTextureFromFile(const char* filename)
{
	ImageFile* texture = new TargaFile;
	C_Hash32 filenameHash(filename);

	if (texture->load(filename))
	{
		m_Textures[filenameHash.GetHashValue()] = texture;
		return true;
	}

	SAFE_DELETE_PTR(texture);

	return false;
}

AsciiTexture* AssetManager::GetAsciiTexture(const char* filename)
{
	C_Hash32 filenameHash(filename);

	std::map<unsigned int, AsciiTexture*>::iterator iter = m_AsciiTextures.find(filenameHash.GetHashValue());

	if (iter != m_AsciiTextures.end())
	{
		//file is already loaded, return a reference
		return iter->second;
	}	

	ImageFile* pTexture = GetTexture(filename);

	if (pTexture)
	{
		AsciiTexture* pAsciiTexture = new AsciiTexture();
		pAsciiTexture->LoadFromTexture(pTexture);
		m_AsciiTextures[filenameHash.GetHashValue()] = pAsciiTexture;
		return pAsciiTexture;
	}

	return nullptr;
}


void AssetManager::AddSpritesheetDef(const char* filename, SpritesheetDef* pSpritesheetDef)
{
	C_Hash32 filenameHash(filename);

	if (m_SpritesheetDefs.find(filenameHash.GetHashValue()) != m_SpritesheetDefs.end())
		return;

	m_SpritesheetDefs[filenameHash.GetHashValue()] = pSpritesheetDef;
}

SpritesheetDef* AssetManager::GetSpritesheetDef(const char* filename)
{
	C_Hash32 filenameHash(filename);

	std::map<unsigned int, SpritesheetDef*>::iterator iter = m_SpritesheetDefs.find(filenameHash.GetHashValue());

	if (iter != m_SpritesheetDefs.end())
		return iter->second;

	if (LoadSpritesheetDefFromFile(filename))
	{
		return GetSpritesheetDef(filename);
	}

	return nullptr;
}

bool AssetManager::LoadSpritesheetDefFromFile(const char* filename)
{
	tinyxml2::XMLDocument doc;

	if (doc.LoadFile(filename) != tinyxml2::XMLError::XML_SUCCESS)
		return false;

	tinyxml2::XMLElement* pTextureAtlas = doc.FirstChildElement("TextureAtlas");

	if (pTextureAtlas)
	{
		SpritesheetDef* pSpritesheetDef = new SpritesheetDef();

		//extract attributes from TextureAtlas
		for (const tinyxml2::XMLAttribute* attribute = pTextureAtlas->FirstAttribute(); attribute; attribute = attribute->Next())
		{
			if (strcmp(attribute->Name(), "imagePath") == 0)
			{
				pSpritesheetDef->m_Filename = attribute->Value();
			}
			else if (strcmp(attribute->Name(), "width") == 0)
			{
				pSpritesheetDef->m_Width = attribute->IntValue();
			}
			else if (strcmp(attribute->Name(), "height") == 0)
			{
				pSpritesheetDef->m_Height = attribute->IntValue();
			}
		}

		//loop through sprites
		for (tinyxml2::XMLNode* ele = pTextureAtlas->FirstChild(); ele; ele = ele->NextSibling())
		{
			SpritesheetSpriteDef spritesheetSpriteDef;

			//extract attributes from sprite
			for (const tinyxml2::XMLAttribute* attribute = ((tinyxml2::XMLElement*)ele)->FirstAttribute(); attribute; attribute = attribute->Next())
			{
				if (strcmp(attribute->Name(), "n") == 0)
				{
					spritesheetSpriteDef.m_Name = attribute->Value();
				}
				else if (strcmp(attribute->Name(), "x") == 0)
				{
					spritesheetSpriteDef.m_PosX = attribute->IntValue();
				}
				else if (strcmp(attribute->Name(), "y") == 0)
				{
					spritesheetSpriteDef.m_PosY = attribute->IntValue();
				}
				else if (strcmp(attribute->Name(), "w") == 0)
				{
					spritesheetSpriteDef.m_Width = attribute->IntValue();
				}
				else if (strcmp(attribute->Name(), "h") == 0)
				{
					spritesheetSpriteDef.m_Height = attribute->IntValue();
				}
				else if (strcmp(attribute->Name(), "pX") == 0)
				{
					spritesheetSpriteDef.m_PivotX = attribute->FloatValue();
				}
				else if (strcmp(attribute->Name(), "pY") == 0)
				{
					spritesheetSpriteDef.m_PivotY = attribute->FloatValue();
				}
				else if (strcmp(attribute->Name(), "oX") == 0)
				{
					spritesheetSpriteDef.m_OffsetX = (float) attribute->IntValue();
				}
				else if (strcmp(attribute->Name(), "oY") == 0)
				{
					spritesheetSpriteDef.m_OffsetY = (float) attribute->IntValue();
				}
				else if (strcmp(attribute->Name(), "oW") == 0)
				{
					spritesheetSpriteDef.m_OriginalWidth = attribute->IntValue();
				}
				else if (strcmp(attribute->Name(), "oH") == 0)
				{
					spritesheetSpriteDef.m_OriginalHeight = attribute->IntValue();
				}
				else if (strcmp(attribute->Name(), "r") == 0)
				{
					spritesheetSpriteDef.m_Rotated = true;
				}
			}

			pSpritesheetDef->m_pSpriteDefs.push_back(spritesheetSpriteDef);
		}

		AddSpritesheetDef(filename, pSpritesheetDef);

		return true;

	}

	return false;
}

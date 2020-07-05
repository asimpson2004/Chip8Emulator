#ifndef _ASSET_MANAGER_H
#define _ASSET_MANAGER_H

#include <map>

class ImageFile;
struct SpritesheetDef;
class AsciiTexture;

class AssetManager
{
public:

	static AssetManager* Instance();
	
	~AssetManager();

	ImageFile* GetTexture(const char* filename);
	bool LoadTextureFromFile(const char* filename);

	AsciiTexture* GetAsciiTexture(const char* filename);

	void AddSpritesheetDef(const char* filename, SpritesheetDef* pSpritesheetDef);
	SpritesheetDef* GetSpritesheetDef(const char* filename);

	bool LoadSpritesheetDefFromFile(const char* filename);

private:

	AssetManager();

	static AssetManager* m_pInstance;

	std::map<unsigned int, ImageFile*> m_Textures;
	std::map<unsigned int, AsciiTexture*> m_AsciiTextures;
	std::map<unsigned int, SpritesheetDef*> m_SpritesheetDefs;

};

#endif

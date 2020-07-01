#ifndef _SPRITESHEET_DEF_H
#define _SPRITESHEET_DEF_H

#include <string>
#include <vector>

struct SpritesheetSpriteDef
{
	std::string m_Name;		//name of the sprite
	int m_PosX;				//sprite x pos in texture
	int m_PosY;				//sprite y pos in texture
	int m_Width;			//sprite width(may be trimmed)
	int m_Height;			//sprite height(may be trimmed)
	float m_PivotX;			//x pos of the pivot point(relative to sprite width)
	float m_PivotY;			//y pos of the pivot point(relative to sprite height)
	bool m_Trimmed;			//not read from file
	float m_OffsetX;		//sprite's x-corner offset (only available if trimmed)
	float m_OffsetY;		//sprite's y-corner offset (only available if trimmed)
	int m_OriginalWidth;	//sprite's original width (only available if trimmed)
	int m_OriginalHeight;	//sprite's original height (only available if trimmed)
	bool m_Rotated;			//'y' only set if sprite is rotated
};

struct SpritesheetDef
{
	std::string m_Filename;
	int m_Width;
	int m_Height;

	std::vector<SpritesheetSpriteDef> m_pSpriteDefs;
};

#endif

#ifndef _ASCII_TEXTURE_H_
#define _ASCII_TEXTURE_H_

#include <windows.h>
#include "../Maths/Vector2.h"

class ImageFile;

struct AsciiPixel
{
	CHAR_INFO rgb;
	unsigned char a;
};

class AsciiTexture
{
public:
	AsciiTexture();
	~AsciiTexture();

	void LoadFromTexture(const ImageFile* pTexture);
	const Vector2& GetSize() { return m_Size; }
	const AsciiPixel& GetPixelAtPosition(int x, int y) { return m_Buffer[y][x]; }

private:

	AsciiPixel** m_Buffer;
	Vector2 m_Size;

};

#endif

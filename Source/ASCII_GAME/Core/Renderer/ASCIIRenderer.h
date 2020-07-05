#ifndef _ASCII_RENDERER_H_
#define _ASCII_RENDERER_H_

#include <Windows.h>
#include <vector>
#include "ConsoleColours.h"
#include "../Maths/Matrix4x4.h"
#include "../Maths/Vector2.h"
#include <mutex>
#include <thread>

class ASCIIRenderer
{
public:
	ASCIIRenderer();
	~ASCIIRenderer();

	void Initialise(short width, short height);
	void InitialisePixelSize(SHORT size);

	void Render();
	void RenderAsync();

	void SetPixel(int x, int y, const CHAR_INFO* pPixelData, const int layer = 0);
	void ClearScreen(WORD clearColour = BACKGROUND_BLACK);	

	void PushMatrix();

	void Translate(Vector2& translation);

	Matrix4x4& GetMatrix() { return m_TransformationStack.back(); }

	void PopMatrix();

	void SwapBuffers();

	std::mutex& GetBackBufferLock() { return bufferLock; }


private:

	int m_BackBufferIndex;
	int m_FrontBufferIndex;

	bool SetWindow(short width, short height);

	SHORT DetectBestFontSize(short width, short height);
	
	HANDLE m_hConsole;
	HANDLE m_hConsoleInput;

	CHAR_INFO* m_ScreenData[2];
	int* m_DepthBuffer[2];

	std::mutex bufferLock;
	std::thread m_RenderThread;

	short m_Width;
	short m_Height;

	short m_DesiredWidth;
	short m_DesiredHeight;

	SMALL_RECT m_DisplayArea;

	bool m_bInitialised;

	std::vector<Matrix4x4> m_TransformationStack;


	COORD renderCoord1;
	COORD renderCoord2;
	SMALL_RECT writeRect;			// Region to write to

	bool m_KillThread;

};

#endif

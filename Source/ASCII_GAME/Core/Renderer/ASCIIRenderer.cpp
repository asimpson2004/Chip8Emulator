#include "ASCIIRenderer.h"
#include <Windows.h>
#include <algorithm>
#include "ConsoleColours.h"
#include "../Utils/Utils.h"
#include "../Maths/Vector2.h"
#include "../Maths/Matrix4x4.h"

const float GAME_RENDER_FREQ = 1.0f / 30.0f;

ASCIIRenderer::ASCIIRenderer()
:m_BackBufferIndex(0)
,m_FrontBufferIndex(1)
,m_Width(0)
,m_Height(0)
,m_DesiredWidth(0)
,m_DesiredHeight(0)
,m_bInitialised(false)
,m_KillThread(false)
{
	m_ScreenData[0] = nullptr;
	m_ScreenData[1] = nullptr;

	m_DepthBuffer[0] = nullptr;
	m_DepthBuffer[1] = nullptr;

	PushMatrix();
}

ASCIIRenderer::~ASCIIRenderer()
{
	m_KillThread = true;
	m_RenderThread.join();

	SAFE_DELETE_ARY(m_ScreenData[m_BackBufferIndex]);
	SAFE_DELETE_ARY(m_ScreenData[m_FrontBufferIndex]);

	SAFE_DELETE_ARY(m_DepthBuffer[m_BackBufferIndex]);
	SAFE_DELETE_ARY(m_DepthBuffer[m_FrontBufferIndex]);
}


void ASCIIRenderer::Initialise(int width, int height)
{
	m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	

	InitialisePixelSize(DetectBestFontSize(width, height));
	SetWindow(width, height);


	renderCoord1 = { m_Width, m_Height };
	renderCoord2 = { 0, 0 }; //0,0
	writeRect = { 0, 0, m_Width - 1, m_Height - 1 };			// Region to write to


	m_ScreenData[m_BackBufferIndex] = new CHAR_INFO[m_Width * m_Height];
	m_ScreenData[m_FrontBufferIndex] = new CHAR_INFO[m_Width * m_Height];

	m_DepthBuffer[m_BackBufferIndex] = new char[m_Width * m_Height];
	m_DepthBuffer[m_FrontBufferIndex] = new char[m_Width * m_Height];

	
	ClearScreen();
	SwapBuffers();

	m_RenderThread = std::thread(&ASCIIRenderer::RenderAsync, this);

	Translate(Vector2(m_DisplayArea.Left, m_DisplayArea.Top));

	m_bInitialised = true;
}

int ASCIIRenderer::DetectBestFontSize(int width, int height)
{
	int workingFontSize = 0;
	bool found = false;

	while (!found)
	{
		InitialisePixelSize(++workingFontSize);
		if (!SetWindow(width, height))
		{
			--workingFontSize;
			workingFontSize = workingFontSize % 2 == 0 ? workingFontSize - 1 : workingFontSize;
			found = true;
		}
	}

	return workingFontSize;
}


void ASCIIRenderer::InitialisePixelSize(int size)
{
	//---Set up font size to look like pixel---
	CONSOLE_FONT_INFOEX font_size;;

	font_size.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	GetCurrentConsoleFontEx(m_hConsole, true, &font_size);

	font_size.dwFontSize.X = size;	//Width of element in buffer
	font_size.dwFontSize.Y = size;//max(1, size * 0.1f);	//Hieght of element in buffer

	SetCurrentConsoleFontEx(m_hConsole, true, &font_size);	//Set the new font size
}

bool ASCIIRenderer::SetWindow(int Width, int Height)
{
	m_DesiredWidth = Width;
	m_DesiredHeight = Height;

	COORD screenSize;

	_CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	GetConsoleScreenBufferInfo(m_hConsole, &bufferInfo);

	COORD MaxWindowSize = GetLargestConsoleWindowSize(m_hConsole);

	SMALL_RECT screenRect;
	
//#ifdef DEBUG
	//screenRect = { 0, 0, min(MaxWindowSize.X, (SHORT)Width), min(MaxWindowSize.Y, (SHORT)Height) };
//#else
	screenRect = { 0, 0, MaxWindowSize.X, MaxWindowSize.Y };
//#endif
	
	bool bufferSizeSet1 = SetConsoleScreenBufferSize(m_hConsole, { screenRect.Right, screenRect.Bottom});
	bool windowInfoSet = SetConsoleWindowInfo(m_hConsole, TRUE, &screenRect);
//#ifdef DEBUG
	//SetConsoleDisplayMode(m_hConsole, CONSOLE_WINDOWED_MODE, &screenSize); //CONSOLE_WINDOWED_MODE //CONSOLE_FULLSCREEN_MODE
//#else
	SetConsoleDisplayMode(m_hConsole, CONSOLE_FULLSCREEN_MODE, &screenSize); //CONSOLE_WINDOWED_MODE //CONSOLE_FULLSCREEN_MODE
//#endif
	
	GetConsoleScreenBufferInfo(m_hConsole, &bufferInfo);


	m_Width = bufferInfo.dwMaximumWindowSize.X;
	m_Height = bufferInfo.dwMaximumWindowSize.Y;

	short  halfDifferenceX = (m_Width - m_DesiredWidth) * 0.5f;
	short  halfDifferenceY = (m_Height - m_DesiredHeight) * 0.5f;

	m_DisplayArea = { max(halfDifferenceX, 0), max(halfDifferenceY, 0), halfDifferenceX + m_DesiredWidth, halfDifferenceY + m_DesiredHeight };

	int a = 0;

	LPCTSTR windowTitle = "ASCII Game";
	SetConsoleTitle(windowTitle);

	return m_DesiredWidth <= m_Width && m_DesiredHeight <= m_Height;
}

void ASCIIRenderer::ClearScreen(WORD attributes)
{
	int numPixels = (m_Width * m_Height);
	for (int i = 0; i < numPixels; i++)
	{
		m_ScreenData[m_BackBufferIndex][i].Char.UnicodeChar = 0;
		m_ScreenData[m_BackBufferIndex][i].Char.AsciiChar = 0; // initialise screen to 0 as we create it
		m_ScreenData[m_BackBufferIndex][i].Attributes = attributes;

		//clear depth buffer
		m_DepthBuffer[m_BackBufferIndex][i] = CHAR_MIN;
	}
}

void ASCIIRenderer::SetPixel(int x, int y, const CHAR_INFO* pPixelData, const char layer)
{
	if (x >= m_DisplayArea.Left && x < m_DisplayArea.Right && y >= m_DisplayArea.Top && y < m_DisplayArea.Bottom)
	{
		int arraryPos = (int)x + ((int)y * m_Width);
		if (layer >= m_DepthBuffer[m_BackBufferIndex][arraryPos])
		{
			m_ScreenData[m_BackBufferIndex][arraryPos].Char.UnicodeChar = pPixelData->Char.UnicodeChar;
			m_ScreenData[m_BackBufferIndex][arraryPos].Char.AsciiChar = pPixelData->Char.AsciiChar;
			m_ScreenData[m_BackBufferIndex][arraryPos].Attributes = pPixelData->Attributes;

			m_DepthBuffer[m_BackBufferIndex][arraryPos] = layer;
		}
	}
}

void ASCIIRenderer::Render()
{
	WriteConsoleOutput(m_hConsole, m_ScreenData[m_FrontBufferIndex], renderCoord1, renderCoord2, &writeRect);

}

void ASCIIRenderer::RenderAsync()
{
	/*debug::log("render async start\n");

	bool killSubThread = false;
	bool renderNow[2] = { false, false };
	std::thread renderRegion[2];

	COORD leftCoord2 = { 0, 0 }; //0,0
	SMALL_RECT leftRect = { 0,0, (0.5 * m_Width), m_Height - 1 };			// Region to write to

	COORD rightCoord2 = { (SHORT)((0.5f * m_Width) + 1), 0 }; //0,0
	SMALL_RECT rightRect = { (SHORT)((0.5f * m_Width) + 1), 0, m_Width - 1, m_Height - 1 };			// Region to write to

	std::mutex flagMutex[2];


	renderRegion[0] = std::thread(&ASCIIRenderer::RenderRegionAsync, this, &renderNow[0], leftCoord2, leftRect, &killSubThread, &flagMutex[0]);
	renderRegion[1] = std::thread(&ASCIIRenderer::RenderRegionAsync, this, &renderNow[1], rightCoord2, rightRect, &killSubThread, &flagMutex[1]);

	*/
	while (!m_KillThread)
	{
		std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();

		WriteConsoleOutput(m_hConsole, m_ScreenData[m_FrontBufferIndex], renderCoord1, renderCoord2, &writeRect);

		bufferLock.lock();
		SwapBuffers();
		bufferLock.unlock();

		std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();
		std::chrono::microseconds delta = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
		float deltaTime = delta.count() * 0.000001f;

		while (deltaTime < GAME_RENDER_FREQ)
		{
			endTime = std::chrono::high_resolution_clock::now();
			delta = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
			deltaTime = delta.count() * 0.000001f;
		}
	}
}

void ASCIIRenderer::PushMatrix()
{
	Matrix4x4 matrix;
	if (m_TransformationStack.size() > 0)
	{
		matrix = m_TransformationStack.back();
	}
	m_TransformationStack.push_back(matrix);
}

void ASCIIRenderer::PopMatrix()
{
	if (m_TransformationStack.size() > 0)
	{
		m_TransformationStack.pop_back();
	}
}

void ASCIIRenderer::Translate(Vector2& translation)
{
	m_TransformationStack.back().Translate(translation);
}

void ASCIIRenderer::SwapBuffers()
{
	int temp = m_BackBufferIndex;
	m_BackBufferIndex = m_FrontBufferIndex;
	m_FrontBufferIndex = temp;
}


#include "KeyboardAndMouseInputDevice.h"

#include <Windows.h>

HANDLE hConsoleInput;

KeyboardAndMouseInputDevice::KeyboardAndMouseInputDevice()
{
	hConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleMode(hConsoleInput, ENABLE_MOUSE_INPUT);
}

KeyboardAndMouseInputDevice::~KeyboardAndMouseInputDevice()
{
}

void KeyboardAndMouseInputDevice::ProcessInputs()
{
	//set the input every frame as we only receive events from the console window
	for (int i = 0; i < E_DigitalInput_MAX; ++i)
	{
		m_DigitalInputs[i].SetPressed(m_DigitalInputs[i].IsDown());
	}

	DWORD numInputEvents = 0;
	GetNumberOfConsoleInputEvents(hConsoleInput, &numInputEvents);

	_INPUT_RECORD inputData[48];

	DWORD numEventsRead = 0;

	for (int i = 0; i < numInputEvents; i += numEventsRead)
	{
		ReadConsoleInput(hConsoleInput, inputData, 48, &numEventsRead);

		for (int j = 0; j < numEventsRead; ++j)
		{
			switch (inputData[j].EventType)
			{
				case KEY_EVENT:
				{
					switch (inputData[j].Event.KeyEvent.wVirtualKeyCode)
					{
						
						case 0x31://1
						{
							m_DigitalInputs[E_DigitalInput_Start].SetPressed(inputData[j].Event.KeyEvent.bKeyDown);
						}
						break;
						case 0x32://2
						{
							m_DigitalInputs[E_DigitalInput_Back].SetPressed(inputData[j].Event.KeyEvent.bKeyDown);
						}
						break;
						case 0x33://3
						{
							m_DigitalInputs[E_DigitalInput_LeftThumb].SetPressed(inputData[j].Event.KeyEvent.bKeyDown);
						}
						break;
						case 0x34://4
						{
							m_DigitalInputs[E_DigitalInput_RightThumb].SetPressed(inputData[j].Event.KeyEvent.bKeyDown);
						}
						break;
						case 0x51://Q
						{
							m_DigitalInputs[E_DigitalInput_LeftShoulder].SetPressed(inputData[j].Event.KeyEvent.bKeyDown);
						}
						break;
						case 0x57://W
						{
							m_DigitalInputs[E_DigitalInput_DpadUp].SetPressed(inputData[j].Event.KeyEvent.bKeyDown);
						}
						break;
						case 0x45://E
						{
							m_DigitalInputs[E_DigitalInput_RightShoulder].SetPressed(inputData[j].Event.KeyEvent.bKeyDown);
						}
						break;
						case 0x52://R
						{
							m_DigitalInputs[E_DigitalInput_A].SetPressed(inputData[j].Event.KeyEvent.bKeyDown);
						}
						break;
						case 0x41://A
						{
							m_DigitalInputs[E_DigitalInput_DpadLeft].SetPressed(inputData[j].Event.KeyEvent.bKeyDown);
						}
						break;
						case 0x53://S
						{
							m_DigitalInputs[E_DigitalInput_DpadDown].SetPressed(inputData[j].Event.KeyEvent.bKeyDown);
						}
						break;
						case 0x44://D
						{
							m_DigitalInputs[E_DigitalInput_DpadRight].SetPressed(inputData[j].Event.KeyEvent.bKeyDown);
						}
						break;
						case 0x46://F
						{
							m_DigitalInputs[E_DigitalInput_B].SetPressed(inputData[j].Event.KeyEvent.bKeyDown);
						}
						break;
						case 0x5A://Z
						{
							m_DigitalInputs[E_DigitalInput_X].SetPressed(inputData[j].Event.KeyEvent.bKeyDown);
						}
						break;
						case 0x58://X
						{
							m_DigitalInputs[E_DigitalInput_Y].SetPressed(inputData[j].Event.KeyEvent.bKeyDown);
						}
						break;
						case 0x43://C
						{
							m_DigitalInputs[E_DigitalInput_TEMP_1].SetPressed(inputData[j].Event.KeyEvent.bKeyDown);
						}
						break;
						case 0x56://V
						{
							m_DigitalInputs[E_DigitalInput_TEMP_2].SetPressed(inputData[j].Event.KeyEvent.bKeyDown);
						}
						break;
						case VK_RETURN:
						{
							m_DigitalInputs[E_DigitalInput_PAUSE].SetPressed(inputData[j].Event.KeyEvent.bKeyDown);
						}
						break;
					}
				}
				break;
				case MOUSE_EVENT:
				{
				}
				break;
			}
		}
		
	}

}

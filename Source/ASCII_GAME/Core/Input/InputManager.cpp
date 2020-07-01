#include "InputManager.h"
#include "InputDevice.h"
#include "../Utils/Utils.h"

InputManager* InputManager::m_pInstance = nullptr;

InputManager::InputManager()
	:m_pInputDevice(nullptr)
{

}

InputManager::~InputManager()
{
	SAFE_DELETE_PTR(m_pInputDevice);
}

InputManager* InputManager::Instance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new InputManager();
	}

	return m_pInstance;
}

void InputManager::Initialise()
{

}

void InputManager::Update()
{
	if (m_pInputDevice)
	{
		m_pInputDevice->ProcessInputs();
	}
}

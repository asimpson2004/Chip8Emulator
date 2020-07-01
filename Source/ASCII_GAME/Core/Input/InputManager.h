#ifndef _INPUT_MANAGER_H
#define _INPUT_MANAGER_H

class InputDevice;

class InputManager
{
public:
	
	~InputManager();

	static InputManager* Instance();

	void Initialise();
	void Update();

	InputDevice* GetInputDevice() { return m_pInputDevice; };
	void SetInputDevice(InputDevice* pInputDevice) { m_pInputDevice = pInputDevice; }

private:
	InputManager();

	static InputManager* m_pInstance;

	InputDevice* m_pInputDevice;
};

#endif

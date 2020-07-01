#ifndef _KEYBOARD_AND_MOUSE_INPUT_DEVICE_H
#define _KEYBOARD_AND_MOUSE_INPUT_DEVICE_H

#include "../../Core/Input/InputDevice.h"

class KeyboardAndMouseInputDevice : public InputDevice
{
public:
	KeyboardAndMouseInputDevice();
	virtual ~KeyboardAndMouseInputDevice();

	virtual void ProcessInputs();

private:

};

#endif

#ifndef _INPUT_DEVICE_H
#define _INPUT_DEVICE_H

struct AnalogueInput
{
	AnalogueInput() : m_Value(0.0f) {}
	void SetValue(float value) { m_Value = value; }
	float GetValue() const { return m_Value;  }

private:
	float m_Value;
};

enum E_ButtonState
{
	E_ButtonState_Up,
	E_ButtonState_Pressed,
	E_ButtonState_Down,
};

struct DigitalInput
{
	DigitalInput() : m_State(E_ButtonState_Up) {}

	void SetPressed(bool pressed) { if (pressed) { m_State = m_State == E_ButtonState_Up ? E_ButtonState_Pressed : E_ButtonState_Down;  } else { m_State = E_ButtonState_Up; } }
	bool OnPressed() const { return m_State == E_ButtonState_Pressed; }
	bool IsDown() const { return m_State != E_ButtonState_Up; }
	bool IsUp() const { return m_State == E_ButtonState_Up; }

private:
	E_ButtonState m_State;
};

enum E_AnalogueInput
{
	E_AnalogueInput_LeftTrigger,
	E_AnalogueInput_RightTrigger,

	E_AnalogueInput_ThumbLX,
	E_AnalogueInput_ThumbLY,

	E_AnalogueInput_ThumbRX,
	E_AnalogueInput_ThumbRY,

	E_AnalogueInput_MAX
};

enum E_DigitalInput
{
	E_DigitalInput_DpadUp,
	E_DigitalInput_DpadDown,
	E_DigitalInput_DpadLeft,
	E_DigitalInput_DpadRight,

	E_DigitalInput_Start,
	E_DigitalInput_Back,

	E_DigitalInput_LeftThumb,
	E_DigitalInput_RightThumb,

	E_DigitalInput_LeftShoulder,
	E_DigitalInput_RightShoulder,

	E_DigitalInput_A,
	E_DigitalInput_B,
	E_DigitalInput_X,
	E_DigitalInput_Y,

	E_DigitalInput_TEMP_1,
	E_DigitalInput_TEMP_2,

	E_DigitalInput_PAUSE,


	E_DigitalInput_MAX
};

class InputDevice
{
public:
	InputDevice() {}
	virtual ~InputDevice() {}

	virtual void ProcessInputs() = 0;


	const DigitalInput& GetButtonInput(E_DigitalInput button) const { return m_DigitalInputs[button]; }
	const AnalogueInput& GetAnalogueInput(E_AnalogueInput trigger) const { return m_AnalogueInputs[trigger]; }

protected:
	AnalogueInput m_AnalogueInputs[E_AnalogueInput_MAX];
	DigitalInput m_DigitalInputs[E_DigitalInput_MAX];
};

#endif

#ifndef _CHIP_8_EMULATOR_COMPONENT_H_
#define _CHIP_8_EMULATOR_COMPONENT_H_

#include "../../Core/Components/Component.h"

static const int CHIP_8_MEMORY_SIZE = 4096;
static const int NUM_CHIP_8_REGISTERS = 16;
static const int CHIP_8_STACK_SIZE = 16;
static const int CHIP_8_SCREEN_WIDTH = 64;
static const int CHIP_8_SCREEN_HEIGHT = 32;
static const char NUM_CHIP_8_KEYS = 16;

class Chip8EmulatorComponent : public Component
{
public:

	Chip8EmulatorComponent(const ComponentCreate* pCreationData, GameObject* pOwner);
	virtual ~Chip8EmulatorComponent();

	virtual void Update(float delta);
	virtual void Render(ASCIIRenderer* pRenderer);
	virtual void OnMessage(Message* pMessage);

private:

	void LoadFontset();
	void LoadRom(const char* filename);

	inline void DecodeAndExecute(const unsigned short int& opcode);

	inline void SwapBuffers();
	inline void GetInput();
	inline void IncrementPC();

	unsigned char m_SystemMemory[CHIP_8_MEMORY_SIZE];
	unsigned char m_Registers[NUM_CHIP_8_REGISTERS]; //V0-VF
	unsigned short m_Stack[CHIP_8_STACK_SIZE];
	unsigned char m_StackPos;
	unsigned char m_DelayTimer;
	unsigned char m_SoundTimer;
	unsigned short int m_AddressRegister; //I
	unsigned short int m_ProgramCounter; //PC
	int m_BackBufferIndex;
	int m_FrontBufferIndex;
	unsigned char m_Keyboard[NUM_CHIP_8_KEYS];
	unsigned char m_Display[CHIP_8_SCREEN_WIDTH * CHIP_8_SCREEN_HEIGHT];
	bool m_DrawFlag;

	float m_Timer;
};

/*

MEMORY
CHIP-8 was most commonly implemented on 4K systems, such as the Cosmac VIP and the Telmac 1800. These machines had 4096 (0x1000)
memory locations, all of which are 8 bits (a byte) which is where the term CHIP-8 originated. However, the CHIP-8 interpreter itself
occupies the first 512 bytes of the memory space on these machines. For this reason, most programs written for the original system 
begin at memory location 512 (0x200) and do not access any of the memory below the location 512 (0x200). The uppermost 256 bytes 
(0xF00-0xFFF) are reserved for display refresh, and the 96 bytes below that (0xEA0-0xEFF) were reserved for the call stack, internal
use, and other variables.

In modern CHIP-8 implementations, where the interpreter is running natively outside the 4K memory space, there is no need to avoid 
the lower 512 bytes of memory (0x000-0x200), and it is common to store font data there.


REGISTERS
CHIP-8 has 16 8-bit data registers named V0 to VF. The VF register doubles as a flag for some instructions; thus, it should be avoided.
In an addition operation, VF is the carry flag, while in subtraction, it is the "no borrow" flag. In the draw instruction VF is set upon
pixel collision.

The address register, which is named I, is 16 bits wide and is used with several opcodes that involve memory operations.




THE STACK
The stack is only used to store return addresses when subroutines are called. The original RCA 1802 version allocated 48 bytes for up to
12 levels of nesting[10]; modern implementations usually have more[11][12].




TIMERS
CHIP-8 has two timers. They both count down at 60 hertz, until they reach 0.

Delay timer: This timer is intended to be used for timing the events of games. Its value can be set and read.
Sound timer: This timer is used for sound effects. When its value is nonzero, a beeping sound is made.


INPUT
Input is done with a hex keyboard that has 16 keys ranging 0 to F. The '8', '4', '6', and '2' keys are typically used for directional 
input. Three opcodes are used to detect input. One skips an instruction if a specific key is pressed, while another does the same if a
specific key is not pressed. The third waits for a key press, and then stores it in one of the data registers.


GRAPHICS AND SOUND
Original CHIP-8 Display resolution is 64×32 pixels, and color is monochrome. Graphics are drawn to the screen solely by drawing sprites,
which are 8 pixels wide and may be from 1 to 15 pixels in height. Sprite pixels are XOR'd with corresponding screen pixels. In other
words, sprite pixels that are set flip the color of the corresponding screen pixel, while unset sprite pixels do nothing. The carry flag
(VF) is set to 1 if any screen pixels are flipped from set to unset when a sprite is drawn and set to 0 otherwise. This is used for 
collision detection.

As previously described, a beeping sound is played when the value of the sound timer is nonzero.

*/

#endif

#include "Chip8EmulatorComponent.h"
#include "../GameData/GameDatabase/CreationData/Chip8EmulatorComponentCreate.h"

#include "../../Core/Renderer/ASCIIRenderer.h"
#include "../../Core/Messages/Message.h"
#include "../../Core/Platform/File.h"

#include "../../Core/Input/InputManager.h"
#include "../../Core/Input/InputDevice.h"

static const int CHIP_8_FONT_SIZE = 80;
static const int CHIP_8_FONT_LOCATION = 0x0;
static const int CHIP_8_ROM_LOCATION = 0x200;

static const int OPCODES_PER_PASS = 15;

static const unsigned char chip8_fontset[CHIP_8_FONT_SIZE] =
{
  0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
  0x20, 0x60, 0x20, 0x20, 0x70, // 1
  0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
  0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
  0x90, 0x90, 0xF0, 0x10, 0x10, // 4
  0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
  0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
  0xF0, 0x10, 0x20, 0x40, 0x40, // 7
  0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
  0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
  0xF0, 0x90, 0xF0, 0x90, 0x90, // A
  0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
  0xF0, 0x80, 0x80, 0x80, 0xF0, // C
  0xE0, 0x90, 0x90, 0x90, 0xE0, // D
  0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
  0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

Chip8EmulatorComponent::Chip8EmulatorComponent(const ComponentCreate* pCreationData, GameObject* pOwner)
:Component(pCreationData, pOwner)
,m_SystemMemory{}
,m_Registers{}
,m_Stack{}
,m_StackPos(-1)
,m_DelayTimer(0)
,m_SoundTimer(0)
,m_AddressRegister(0)
,m_ProgramCounter(CHIP_8_ROM_LOCATION)
,m_BackBufferIndex(0)
,m_FrontBufferIndex(1)
,m_Keyboard{}
,m_Display{}
,m_DrawFlag(false)
,m_Timer(0.0f)
{
	const Chip8EmulatorComponentCreate* pCreate = dynamic_cast<const Chip8EmulatorComponentCreate*>(pCreationData);
	if (pCreate)
	{
		LoadFontset();
		LoadRom(pCreate->filename);
	}
}

Chip8EmulatorComponent::~Chip8EmulatorComponent()
{
}

void Chip8EmulatorComponent::LoadFontset()
{
	for (int i = 0; i < CHIP_8_FONT_SIZE; i++)
	{
		m_SystemMemory[CHIP_8_FONT_LOCATION + i] = chip8_fontset[i];
	}
}

void Chip8EmulatorComponent::LoadRom(const char* filename)
{
	fileType romFile;
	if (romFile.load(filename))
	{
		for (int i = 0; i < romFile.size; i++)
		{
			m_SystemMemory[CHIP_8_ROM_LOCATION + i] = romFile.buffer[i];
		}
	}
}

void Chip8EmulatorComponent::Update(float delta)
{
	m_Timer += delta;

	for (int i = 0; i < OPCODES_PER_PASS; i++)
	{
		//Input 
		GetInput();

		//fetch
		unsigned short int opcode = m_SystemMemory[m_ProgramCounter] << 8 | m_SystemMemory[m_ProgramCounter + 1];

		//debug::log("opcode: %04X\n", opcode);
		DecodeAndExecute(opcode);
	}

	if (m_DelayTimer > 0)
	{
		--m_DelayTimer;
	}

	if (m_SoundTimer > 0)
	{
		if (m_SoundTimer == 1)
		{
			//play beep
			debug::log("Beep!\n");
		}
		--m_SoundTimer;
	}

	m_Timer -= 1.0f;	
}

void Chip8EmulatorComponent::Render(ASCIIRenderer* pRenderer)
{
	for (int y = 0; y < CHIP_8_SCREEN_HEIGHT; ++y)
	{
		for (int x = 0; x < CHIP_8_SCREEN_WIDTH; ++x)
		{
			CHAR_INFO pixel;
			pixel.Char.AsciiChar = ' ';
			if (m_Display[x + (y * CHIP_8_SCREEN_WIDTH)] == 1)
			{
				pixel.Attributes = BACKGROUND_WHITE;
			}
			else
			{
				pixel.Attributes = BACKGROUND_BLACK;
			}
			pRenderer->SetPixel(x * 2, y, &pixel);
			pRenderer->SetPixel((x * 2) + 1, y, &pixel);

		}
	}
}

void Chip8EmulatorComponent::OnMessage(Message* pMessage)
{
}

inline void Chip8EmulatorComponent::DecodeAndExecute(const unsigned short int& opcode)
{
	switch (opcode & 0xF000)
	{
		case 0x0000:
		{
			switch (opcode)
			{
				case 0x00E0://00E0 - CLS
				{
					//Clear the display.
					for (int i = 0; i < CHIP_8_SCREEN_WIDTH * CHIP_8_SCREEN_HEIGHT; ++i)
					{
						m_Display[i] = 0;
					}
					IncrementPC();
				}
				break;
				case 0x00EE://00EE - RET
				{
					//Return from a subroutine.
					//The interpreter sets the program counter to the address at the top of the stack, then subtracts 1 from the stack pointer.
					m_ProgramCounter = m_Stack[--m_StackPos];
					IncrementPC();
				}
				break;
				default:
				{
					//0NNN - SYS addr
					//Jump to a machine code routine at nnn.
					//This instruction is only used on the old computers on which Chip - 8 was originally implemented.
					//It is ignored by modern interpreters
					debug::log("ERROR unhandled opcode: %04X\n", opcode);
				}
				break;
			}
		}
		break;
		case 0x1000://1NNN - JP addr
		{			
			//Jump to location nnn.
			//The interpreter sets the program counter to nnn.
			m_ProgramCounter = (opcode & 0x0FFF);
		}
		break;
		case 0x2000://2NNN - CALL addr
		{			
			//Call subroutine at nnn.
			//The interpreter increments the stack pointer, then puts the current PC on the top of the stack.The PC is then set to nnn.
			m_Stack[m_StackPos++] = m_ProgramCounter;
			m_ProgramCounter = (opcode & 0x0FFF);
		}
		break;
		case 0x3000://3XNN - SE Vx, byte
		{			
			//Skip next instruction if Vx = NN.
			//The interpreter compares register Vx to NN, and if they are equal, increments the program counter by 2.
			if (m_Registers[(opcode & 0x0F00) >> 8] == (opcode & 0x00FF))
			{
				IncrementPC();
			}
			IncrementPC();
		}
		break;
		case 0x4000://4XNN - SNE Vx, byte
		{			
			//Skip next instruction if Vx != NN.
			//The interpreter compares register Vx to NN, and if they are not equal, increments the program counter by 2.
			if (m_Registers[(opcode & 0x0F00) >> 8] != (opcode & 0x00FF))
			{
				IncrementPC();
			}
			IncrementPC();
		}
		break;
		case 0x5000://5XY0 -  - SE Vx, Vy
		{			
			//Skip next instruction if Vx = Vy.
			//The interpreter compares register Vx to register Vy, and if they are equal, increments the program counter by 2.
			if (m_Registers[(opcode & 0x0F00) >> 8] == m_Registers[(opcode & 0x00F0) >> 4])
			{
				IncrementPC();
			}
			IncrementPC();
		}
		break;
		case 0x6000://6XNN - LD Vx, byte
		{			
			//Set Vx = NN.
			//The interpreter puts the value NN into register Vx.
			m_Registers[(opcode & 0x0F00) >> 8] = (opcode & 0x00FF);
			IncrementPC();
		}
		break;
		case 0x7000://7XNN - ADD Vx, byte
		{			
			//Set Vx = Vx + NN.
			//Adds the value NN to the value of register Vx, then stores the result in Vx.
			m_Registers[(opcode & 0x0F00) >> 8] += (opcode & 0x00FF);
			IncrementPC();
		}
		break;
		case 0x8000:
		{
			switch (opcode & 0x000F)
			{
				case 0x0000://8XY0 - LD Vx, Vy
				{
					//Set Vx = Vy.
					//Stores the value of register Vy in register Vx.
					m_Registers[(opcode & 0x0F00) >> 8] = m_Registers[(opcode & 0x00F0) >> 4];
					IncrementPC();
				}
				break;
				case 0x0001://8XY1 - OR Vx, Vy
				{					
					//Set Vx = Vx OR Vy.
					//Performs a bitwise OR on the values of Vx and Vy, then stores the result in Vx.A bitwise OR compares the corrseponding
					//bits from two values, and if either bit is 1, then the same bit in the result is also 1. Otherwise, it is 0.
					m_Registers[(opcode & 0x0F00) >> 8] |= m_Registers[(opcode & 0x00F0) >> 4];
					IncrementPC();
				}
				break;
				case 0x0002://8XY2 - AND Vx, Vy
				{
					//Set Vx = Vx AND Vy.
					//Performs a bitwise AND on the values of Vx and Vy, then stores the result in Vx.A bitwise AND compares the 
					//corrseponding bits from two values, and if both bits are 1, then the same bit in the result is also 1. Otherwise, it is 0.
					m_Registers[(opcode & 0x0F00) >> 8] &= m_Registers[(opcode & 0x00F0) >> 4];
					IncrementPC();
				}
				break;
				case 0x0003://8XY3 - XOR Vx, Vy
				{
					//Set Vx = Vx XOR Vy.
					//Performs a bitwise exclusive OR on the values of Vx and Vy, then stores the result in Vx.An exclusive OR 
					//compares the corrseponding bits from two values, and if the bits are not both the same, then the corresponding
					//bit in the result is set to 1. Otherwise, it is 0.
					m_Registers[(opcode & 0x0F00) >> 8] ^= m_Registers[(opcode & 0x00F0) >> 4];
					IncrementPC();
				}
				break;
				case 0x0004://8XY4 - ADD Vx, Vy
				{
					//Set Vx = Vx + Vy, set VF = carry.
					//The values of Vx and Vy are added together.If the result is greater than 8 bits(i.e., > 255, ) VF is set
					//to 1, otherwise 0. Only the lowest 8 bits of the result are kept, and stored in Vx.
					int result = (int)m_Registers[(opcode & 0x0F00) >> 8] + (int)m_Registers[(opcode &0x00F0) >> 4];
					m_Registers[(opcode & 0x0F00) >> 8] = (char)result;
					m_Registers[0xF] = result > 255 ? 1 : 0;
					IncrementPC();
				}
				break;
				case 0x0005://8XY5 - SUB Vx, Vy
				{
					//Set Vx = Vx - Vy, set VF = NOT borrow.
					//If Vx > Vy, then VF is set to 1, otherwise 0. Then Vy is subtracted from Vx, and the results stored in Vx.
					m_Registers[0xF] = m_Registers[(opcode & 0x0F00) >> 8] > m_Registers[(opcode & 0x00F0) >> 4] ? 1 : 0;
					m_Registers[(opcode & 0x0F00) >> 8] -= m_Registers[(opcode & 0x00F0) >> 4];
					IncrementPC();
				}
				break;
				case 0x0006://8XY6 - SHR Vx {, Vy}
				{
					//Set Vx = Vx SHR 1.
					//If the least - significant bit of Vx is 1, then VF is set to 1, otherwise 0. Then Vx is divided by 2.
					m_Registers[0xF] = m_Registers[(opcode & 0x0F00) >> 8] & 0x0001;
					m_Registers[(opcode & 0x0F00) >> 8] >>= 1;
					IncrementPC();
				}
				break;
				case 0x0007://8XY7 - SUBN Vx, Vy
				{					
					//Set Vx = Vy - Vx, set VF = NOT borrow.
					//If Vy > Vx, then VF is set to 1, otherwise 0. Then Vx is subtracted from Vy, and the results stored in Vx.
					m_Registers[0xF] = m_Registers[(opcode & 0x00F0) >> 4] > m_Registers[(opcode & 0x0F00) >> 8] ? 1 : 0;
					m_Registers[(opcode & 0x0F00) >> 8] = m_Registers[(opcode & 0x00F0) >> 4] - m_Registers[(opcode & 0x0F00) >> 8];
					IncrementPC();
				}
				break;
				case 0x000E://8XYE - SHL Vx {, Vy}
				{
					//Set Vx = Vx SHL 1.
					//If the most - significant bit of Vx is 1, then VF is set to 1, otherwise to 0. Then Vx is multiplied by 2.
					m_Registers[0xF] = m_Registers[(opcode & 0x0F00) >> 8] >> 7;
					m_Registers[(opcode & 0x0F00) >> 8] <<= 1;
					IncrementPC();
				}
				break;
				default:
				{
					debug::log("ERROR unhandled opcode: %04X\n", opcode);
				}
				break;
			}
		}
		break;
		case 0x9000://9XY0 - SNE Vx, Vy
		{
			//Skip next instruction if Vx != Vy.
			//The values of Vx and Vy are compared, and if they are not equal, the program counter is increased by 2.
			if (m_Registers[(opcode & 0x0F00)>>8] != m_Registers[(opcode & 0x00F0) >> 4])
			{
				IncrementPC();
			}
			IncrementPC();
		}
		break;
		case 0xA000://ANNN - LD I, addr
		{			
			//Set I = nnn.
			//The value of register I is set to nnn.
			m_AddressRegister = (opcode & 0x0FFF);
			IncrementPC();
		}
		break;
		case 0xB000://BNNN - JP V0, addr
		{			
			//Jump to location nnn + V0.
			//The program counter is set to nnn plus the value of V0.
			m_ProgramCounter = (opcode & 0x0FFF) + m_Registers[0];
		}
		break;
		case 0xC000://CXNN - RND Vx, byte
		{			
			//Set Vx = random byte AND kk.
			//The interpreter generates a random number from 0 to 255, which is then ANDed with the value kk.The results are 
			//stored in Vx.See instruction 8xy2 for more information on AND.
			m_Registers[(opcode & 0x0F00) >> 8] = (rand() % 255) & (opcode & 0x00FF);
			IncrementPC();
		}
		break;
		case 0xD000://DXYN - DRW Vx, Vy, nibble
		{			
			//Display n - byte sprite starting at memory location I at(Vx, Vy), set VF = collision.
			//The interpreter reads n bytes from memory, starting at the address stored in I.These bytes are then displayed as sprites
			//on screen at coordinates(Vx, Vy).Sprites are XORed onto the existing screen.If this causes any pixels to be erased, VF is
			//set to 1, otherwise it is set to 0. If the sprite is positioned so part of it is outside the coordinates of the display,
			//it wraps around to the opposite side of the screen.See instruction 8xy3 for more information on XOR, and section 2.4, Display,
			//for more information on the Chip - 8 screen and sprites.
			unsigned short x = m_Registers[(opcode & 0x0F00) >> 8];
			unsigned short y = m_Registers[(opcode & 0x00F0) >> 4];
			unsigned short height = opcode & 0x000F;
			unsigned short pixel;

			m_Registers[0xF] = 0;
			for (int yline = 0; yline < height; yline++)
			{
				pixel = m_SystemMemory[m_AddressRegister + yline];
				for (int xline = 0; xline < 8; xline++)
				{
					if ((pixel & (0x80 >> xline)) != 0)
					{
						//if (m_Display[(x + xline + ((y + yline) * 64))] == 1)
						if(m_Display[(x + xline + ((y + yline) * 64)) % (64 * 32)] == 1)
						{
							m_Registers[0xF] = 1;
						}
						//m_Display[x + xline + ((y + yline) * 64)] ^= 1;
						m_Display[(x + xline + ((y + yline) * 64)) % (64 * 32)] ^= 1;
					}
				}
			}

			//SwapBuffers();
			IncrementPC();

		}
		break;
		case 0xE000:
		{
			switch (opcode & 0x00FF)
			{
				case 0x009E://EX9E - SKP Vx
				{
					//Skip next instruction if key with the value of Vx is pressed.
					//Checks the keyboard, and if the key corresponding to the value of Vx is currently in the down position, PC is increased by 2.
					if (m_Keyboard[m_Registers[(opcode & 0x0F00) >> 8]] != 0)
					{
						IncrementPC();
					}
					IncrementPC();
				}
				break;
				case 0x00A1://EXA1 - SKNP Vx
				{
					//Skip next instruction if key with the value of Vx is not pressed.
					//Checks the keyboard, and if the key corresponding to the value of Vx is currently in the up position, PC is increased by 2.
					if (m_Keyboard[m_Registers[(opcode & 0x0F00) >> 8]] == 0)
					{
						IncrementPC();
					}
					IncrementPC();
				}
				break;
				default:
				{
					debug::log("ERROR unhandled opcode: %04X\n", opcode);
				}
				break;
			}
		}
		break;
		case 0xF000:
		{
			switch (opcode & 0x00FF)
			{
				case 0x0007://FX07 - LD Vx, DT
				{					
					//Set Vx = delay timer value.
					//The value of DT is placed into Vx.
					m_Registers[(opcode & 0x0F00) >> 8] = m_DelayTimer;
					IncrementPC();
				}
				break;
				case 0x000A://FX0A - LD Vx, K
				{					
					//Wait for a key press, store the value of the key in Vx.
					//All execution stops until a key is pressed, then the value of that key is stored in Vx.
					for (int i = 0; i < NUM_CHIP_8_KEYS; ++i)
					{
						if (m_Keyboard[i] != 0)
						{
							m_Registers[(opcode & 0x0F00) >> 8] = i;
							IncrementPC(); 
							break;
						}
					}
				}
				break;
				case 0x0015://FX15 - LD DT, Vx
				{				
					//Set delay timer = Vx.
					//DT is set equal to the value of Vx.
					m_DelayTimer = m_Registers[(opcode & 0x0F00) >> 8];
					IncrementPC();
				}
				break;
				case 0x0018://FX18 - LD ST, Vx
				{					
					//Set sound timer = Vx.
					//ST is set equal to the value of Vx.
					m_SoundTimer = m_Registers[(opcode & 0x0F00) >> 8];
					IncrementPC();
				}
				break;
				case 0x001E://FX1E - ADD I, Vx
				{					
					//Set I = I + Vx.
					//The values of I and Vx are added, and the results are stored in I.
					m_Registers[0xF] = ((int)m_AddressRegister + (int)m_Registers[(opcode & 0x0F00) >> 8]) > 0xFFF ? 1 : 0;
					m_AddressRegister += m_Registers[(opcode & 0x0F00) >> 8];
					IncrementPC();
				}
				break;
				case 0x0029://FX29 - LD F, Vx
				{
					//Set I = location of sprite for digit Vx.
					//The value of I is set to the location for the hexadecimal sprite corresponding to the value of Vx.See section 2.4, 
					//Display, for more information on the Chip - 8 hexadecimal font.
					m_AddressRegister = CHIP_8_FONT_LOCATION + (5 * m_Registers[(opcode & 0x0F00) >> 8]);
					IncrementPC();
				}
				break;
				case 0x0033://FX33 - LD B, Vx
				{					
					//Store BCD representation of Vx in memory locations I, I + 1, and I + 2.
					//The interpreter takes the decimal value of Vx, and places the hundreds digit in memory at location in I, the tens digit
					//at location I + 1, and the ones digit at location I + 2.
					unsigned char value = m_Registers[(opcode & 0x0F00) >> 8];
					m_SystemMemory[m_AddressRegister] = (value / 100) % 10; //hundreds
					m_SystemMemory[m_AddressRegister+1] = (value / 10) % 10; //tens
					m_SystemMemory[m_AddressRegister+2] = value % 10;//units
					IncrementPC();
				}
				break;
				case 0x0055://FX55 - LD [I], Vx
				{					
					//Store registers V0 through Vx in memory starting at location I.
					//The interpreter copies the values of registers V0 through Vx into memory, starting at the address in I.
					for (int i = 0; i <= ((opcode & 0x0F00) >> 8); ++i)
					{
						m_SystemMemory[m_AddressRegister + i] = m_Registers[i];
					}

					// On the original interpreter, when the operation is done, I = I + X + 1.
					m_AddressRegister += ((opcode & 0x0F00) >> 8) + 1;

					IncrementPC();
				}
				break;
				case 0x0065://FX65 - LD Vx, [I]
				{
					//Read registers V0 through Vx from memory starting at location I.
					//The interpreter reads values from memory starting at location I into registers V0 through Vx.
					for (int i = 0; i <= ((opcode & 0x0F00) >> 8); ++i)
					{
						m_Registers[i] = m_SystemMemory[m_AddressRegister + i];
					}

					// On the original interpreter, when the operation is done, I = I + X + 1.
					m_AddressRegister += ((opcode & 0x0F00) >> 8) + 1;
					IncrementPC();
				}
				break;
				default:
				{
					debug::log("ERROR unhandled opcode: %04X\n", opcode);
				}
				break;
			}

		}
		break;
		default:
		{
			debug::log("ERROR unhandled opcode: %04X\n", opcode);
		}
		break;
	}
}

inline void Chip8EmulatorComponent::SwapBuffers()
{
	int temp = m_BackBufferIndex;
	m_BackBufferIndex = m_FrontBufferIndex;
	m_FrontBufferIndex = temp;
}

inline void Chip8EmulatorComponent::GetInput()
{
	//clear keys
	for (int i = 0; i < NUM_CHIP_8_KEYS; ++i)
	{
		m_Keyboard[i] = 0;
	}

	//read keys
	InputDevice* pInputDevice = InputManager::Instance()->GetInputDevice();
	if (pInputDevice)
	{
		m_Keyboard[0] = pInputDevice->GetButtonInput(E_DigitalInput_Start).IsDown() ? 1 : 0;
		m_Keyboard[1] = pInputDevice->GetButtonInput(E_DigitalInput_Back).IsDown() ? 1 : 0;
		m_Keyboard[2] = pInputDevice->GetButtonInput(E_DigitalInput_LeftThumb).IsDown() ? 1 : 0;
		m_Keyboard[3] = pInputDevice->GetButtonInput(E_DigitalInput_RightThumb).IsDown() ? 1 : 0;
		m_Keyboard[4] = pInputDevice->GetButtonInput(E_DigitalInput_LeftShoulder).IsDown() ? 1 : 0;
		m_Keyboard[5] = pInputDevice->GetButtonInput(E_DigitalInput_DpadUp).IsDown() ? 1 : 0;
		m_Keyboard[6] = pInputDevice->GetButtonInput(E_DigitalInput_RightShoulder).IsDown() ? 1 : 0;
		m_Keyboard[7] = pInputDevice->GetButtonInput(E_DigitalInput_A).IsDown() ? 1 : 0;
		m_Keyboard[8] = pInputDevice->GetButtonInput(E_DigitalInput_DpadLeft).IsDown() ? 1 : 0;
		m_Keyboard[9] = pInputDevice->GetButtonInput(E_DigitalInput_DpadDown).IsDown() ? 1 : 0;
		m_Keyboard[10] = pInputDevice->GetButtonInput(E_DigitalInput_DpadRight).IsDown() ? 1 : 0;
		m_Keyboard[11] = pInputDevice->GetButtonInput(E_DigitalInput_B).IsDown() ? 1 : 0;
		m_Keyboard[12] = pInputDevice->GetButtonInput(E_DigitalInput_X).IsDown() ? 1 : 0;
		m_Keyboard[13] = pInputDevice->GetButtonInput(E_DigitalInput_Y).IsDown() ? 1 : 0;
		m_Keyboard[14] = pInputDevice->GetButtonInput(E_DigitalInput_TEMP_1).IsDown() ? 1 : 0;
		m_Keyboard[15] = pInputDevice->GetButtonInput(E_DigitalInput_TEMP_2).IsDown() ? 1 : 0;
	}

	/*
	Keyboard
	+-+-+-+-+
	|1|2|3|4|
	+-+-+-+-+
	|Q|W|E|R|
	+-+-+-+-+
	|A|S|D|F|
	+-+-+-+-+
	|Z|X|C|V|
	+-+-+-+-+
	*/
}

inline void Chip8EmulatorComponent::IncrementPC()
{
	m_ProgramCounter += 2;
}

/*
	      - Standard Chip-8 Instructions
			00E0 - CLS
			00EE - RET
			0nnn - SYS addr
			1nnn - JP addr
			2nnn - CALL addr
			3xkk - SE Vx, byte
			4xkk - SNE Vx, byte
			5xy0 - SE Vx, Vy
			6xkk - LD Vx, byte
			7xkk - ADD Vx, byte
			8xy0 - LD Vx, Vy
			8xy1 - OR Vx, Vy
			8xy2 - AND Vx, Vy
			8xy3 - XOR Vx, Vy
			8xy4 - ADD Vx, Vy
			8xy5 - SUB Vx, Vy
			8xy6 - SHR Vx {, Vy}
			8xy7 - SUBN Vx, Vy
			8xyE - SHL Vx {, Vy}
			9xy0 - SNE Vx, Vy
			Annn - LD I, addr
			Bnnn - JP V0, addr
			Cxkk - RND Vx, byte
			Dxyn - DRW Vx, Vy, nibble
			Ex9E - SKP Vx
			ExA1 - SKNP Vx
			Fx07 - LD Vx, DT
			Fx0A - LD Vx, K
			Fx15 - LD DT, Vx
			Fx18 - LD ST, Vx
			Fx1E - ADD I, Vx
			Fx29 - LD F, Vx
			Fx33 - LD B, Vx
			Fx55 - LD [I], Vx
			Fx65 - LD Vx, [I]
	      - Super Chip-48 Instructions
			00Cn - SCD nibble
			00FB - SCR
			00FC - SCL
			00FD - EXIT
			00FE - LOW
			00FF - HIGH
			Dxy0 - DRW Vx, Vy, 0
			Fx30 - LD HF, Vx
			Fx75 - LD R, Vx
			Fx85 - LD Vx, R
			
*/

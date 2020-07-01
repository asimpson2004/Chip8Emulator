#include "Vector2D.h"

#include "GameDataHelpers.h"

namespace GDb
{
	void C_Vector2d::InitialiseFromBinary(char*& buffer)
	{
		GDb::InitialiseFromBinary(&x, buffer);
		GDb::InitialiseFromBinary(&y, buffer);
	}
}

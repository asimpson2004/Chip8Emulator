#ifndef VECTOR_2D_H
#define VECTOR_2D_H

#include "DatabaseTypes.h"

namespace GDb
{
	class C_Vector2d : public C_DataItem
	{
	public:

		C_Vector2d() :x(0.0f), y(0.0f) {}
		virtual ~C_Vector2d() { }

		virtual void InitialiseFromBinary(char*& buffer);

		float x;
		float y;
	};
}//namespace GDb

#endif

#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include <math.h>

class Vector3
{
public:
	Vector3();
	Vector3(float _x, float _y, float _z, float w = 1.0f);
	~Vector3();

	float x;
	float y;
	float z;
	float w;

	float distanceSquared(const Vector3& other) const
	{
		float differenceX = other.x - x;
		float differenceY = other.y - y;
		float differenceZ = other.z - z;

		return fabsf( (differenceX * differenceX) + (differenceY * differenceY) + (differenceZ * differenceZ) );
	}

private:
};

#endif

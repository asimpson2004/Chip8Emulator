#ifndef _VECTOR2_H_
#define _VECTOR2_H_

class Vector2
{
public:
	Vector2();
	Vector2(float _x, float _y, float _w = 1.0f);
	~Vector2();

	float x;
	float y;
	float w;

private:
};

#endif

#ifndef _RECT_H_
#define _RECT_H_

class Rect
{
public:
	Rect();
	Rect(float _x, float _y, float _w, float _h);
	~Rect();

	float x;
	float y;
	float w;
	float h;

private:
};

#endif

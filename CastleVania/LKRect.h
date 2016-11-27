#ifndef _LKRECT_H_
#define _LKRECT_H_

#include <Windows.h>
#include <conio.h>
#include <d3d9.h>
#include <dinput.h>
class LKRect
{
public:
	float x;
	float y;
	float width;
	float height;

	LKRect(void);
	LKRect(float, float, float, float);
	bool intersect(LKRect rect_); // Tesst if intersect with another rect
	RECT* toRect();
	~LKRect(void);
};

#endif
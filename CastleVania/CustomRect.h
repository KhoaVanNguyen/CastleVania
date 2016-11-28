#ifndef _CustomRect_H_
#define _CustomRect_H_

#include <Windows.h>
#include <conio.h>
#include <d3d9.h>
#include <dinput.h>
class CustomRect
{
public:
	float x;
	float y;
	float width;
	float height;

	CustomRect(void);
	CustomRect(float, float, float, float);
	bool intersect(CustomRect rect_); // Tesst if intersect with another rect
	RECT* toRect();
	~CustomRect(void);
};

#endif
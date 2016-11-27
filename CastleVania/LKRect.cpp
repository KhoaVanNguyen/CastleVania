#include "LKRect.h"


LKRect::LKRect(void)
{
	x = y = width = height = 0;
}

LKRect::LKRect(float x_, float y_, float width_, float height_)
{
	x = x_;
	y = y_;
	width = width_;
	height = height_;
}

bool LKRect::intersect(LKRect rect_) //rect_ => object rect
{
	int x1 = x;
	int x2 = x + width;
	int xx1 = rect_.x;
	int xx2 = rect_.x + rect_.width;
	int y1 = y;
	int y2 = y - height;
	int yy1 = rect_.y;
	int yy2 = rect_.y - rect_.height;

	if (xx1 >= x2 || x1 >= xx2)
		return false;
	if (yy2 >= y1 || y2 >= yy1)
		return false;
	return true;
}

RECT* LKRect::toRect()
{
	RECT* rect = new RECT;
	rect->left = this->x;
	rect->top = this->y;
	rect->right = this->x + this->width;
	rect->bottom = this->y + this->height;
	return rect;
}

LKRect::~LKRect(void)
{
}

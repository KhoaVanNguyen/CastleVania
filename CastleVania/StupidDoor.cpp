
#include "StupidDoor.h"

void StupidDoor::_initialize()
{
	_localAnimationTime = 0;
	_localTime = 0;
}

void StupidDoor::_goUp()
{
	vY = _vUp;
}

void StupidDoor::_goDown()
{
	vY = -_vDown;
}

int StupidDoor::_round(float number_)
{
	int result = (int)number_;
	int temp = number_ * 10;
	if (abs(temp % 10) >= 5)
		result = result + abs(number_) / number_;
	return result;
}

int StupidDoor::_compareBound()
{
	if (posY <= _yMin)
		return -1;
	if (posY >= _yMax)
		return 1;
	return 0;
}

StupidDoor::StupidDoor(void) :GameObject()
{
	_initialize();
	_vUp = 0;
	_vDown = 0;
	_yMax = 0;
	_yMin = 0;
	_animationRate = 1;
	this->active = true;
}

StupidDoor::StupidDoor(float posX_, float posY_, float yMax_, float yMin_, float vUp_, float vDown_, int animationRate_) :GameObject(posX_, posY_, EnumID::StupidDoor_ID)
{
	vX = 0;
	vY = STUPID_DOOR_SPEED_UP;
	_initialize();
	this->active = true;
	_vUp = vUp_;
	_vDown = vDown_;
	_yMax = yMax_ - height / 2;
	_yMin = yMin_ + height / 2;
	_animationRate = animationRate_;
}

void StupidDoor::Update(int deltaTime_)
{
	_localAnimationTime += deltaTime_;
	if (_localAnimationTime >= 1000 / _animationRate)
	{
		if (this->_compareBound()>0 && vY>0)
		{
			this->_goDown();
		}
		else if (this->_compareBound()<0 && vY<0)
		{
			this->_goUp();
		}
		int deltaY = _round(vY*_localAnimationTime / 8);
		posY += deltaY * 8;
		if (posY>_yMax)
			posY = _yMax;
		if (posY<_yMin)
			posY = _yMin;
		if (abs(deltaY)>0)
			_localAnimationTime = 0;
	}
}

void StupidDoor::Draw(GCamera*camera_)
{

	D3DXVECTOR2 center = camera_->Transform(posX, posY);

	// draw the pointed nose
	this->sprite->Reset();
	this->sprite->Draw(center.x, center.y);

	// draw littles part
	this->sprite->Next();
	bool done = false;
	float Y0 = _yMax - 2 + 32;
	float tempY = posY + 14 + 8;
	while (!done)
	{
		if (tempY >= Y0)
			break;
		center = camera_->Transform(posX, tempY);
		this->sprite->Draw(center.x, center.y);
		tempY += 8;
	}
}

void StupidDoor::Collision(list<GameObject*> obj, int dt)
{

}


StupidDoor::~StupidDoor(void)
{

}

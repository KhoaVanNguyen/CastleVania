
#include "ThrowAxe.h"


ThrowAxe::ThrowAxe(void)
{
}

void ThrowAxe::_initialize()
{
	_gold = new D3DXVECTOR2(0, 0);
	_anpha = 0;
	_posX0 = posX;
	_posY0 = posY;
}

ThrowAxe::ThrowAxe(float x_, float y_, float huong_) : Weapon(x_, y_, huong_, EnumID::Throw_Axe_ID)
{
	_initialize();
	prepare(x_, y_, huong_);
}

void ThrowAxe::Update(int deltaTime_)
{
	this->sprite->Update(deltaTime_);
	vX = THROW_AXE_SPEED_X*cos(_anpha);
	vY = THROW_AXE_SPEED_X*sin(_anpha) - G*deltaTime_;
	posX += vX*deltaTime_;
	float deltaPosX = posX - _posX0;
	posY = _posY0 + vY*deltaPosX / vX - 0.5*G*pow((deltaPosX / vX), 2);
}

void ThrowAxe::prepare(float simonX_, float simonY_, float direct_)
{
	if (direct_>0)
	{
		_anpha = THROW_AXE_ANPHA;
		_posX0 = posX = simonX_ + 20;
		_gold->x = posX + 100;
	}
	else
	{
		_anpha = 180 - THROW_AXE_ANPHA;
		_posX0 = posX = simonX_ - 20;
		_gold->x = posX - 100;
	}
	_anpha = _anpha*(3.14 / 180);
	_posY0 = posY = simonY_ + 20;
}

ThrowAxe::~ThrowAxe(void)
{
}

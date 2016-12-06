#ifndef _THROWAXE_H_
#define _THROWAEX_H_

#include "Weapon.h"

#define THROW_AXE_ANPHA 45
#define THROW_AXE_SPEED_X 1.5
#define G 0.01f

class ThrowAxe :
	public Weapon
{
protected:
	D3DXVECTOR2* _gold;
	float _anpha;
	float _posX0;
	float _posY0;
	void _initialize();
public:
	ThrowAxe(void);
	ThrowAxe(float x_, float y_, float huong_);
	virtual void Update(int deltaTime_);
	void prepare(float simonX_, float simonY_, float direct_);
	~ThrowAxe(void);
};

#endif
#ifndef _HOLYWATER_H_
#define _HOLYWATER_H_

#include "weapon.h"
#include "Medusa.h"
#define	PRIMARY_STATE_RATE 1
#define SECONDARY_STATE_RATE 5
#define SPEED_X 1.f
#define G 0.01f
#define ANPHA 70

enum EThrowState
{
	Primary,
	Secondary
};


class HolyWater :
	public Weapon
{
protected:
	EThrowState _eThrowStatus;
	D3DXVECTOR2* _gold;
	float _anpha;
	float _posX0;
	float _posY0;


	void _initialize();
	int _localTime;
public:
	HolyWater(void);
	HolyWater(float x_, float y_, float huong_);
	//virtual void Draw(CCamera* camera_);
	void Update(int deltaTime_);
	void Collision(list<GameObject*> &obj, int dt);
	void prepareFighting(float simonX_, float simonY_, float direct_);
	~HolyWater(void);
};

#endif
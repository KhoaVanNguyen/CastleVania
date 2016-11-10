#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "DynamicObject.h"
#include <math.h>

using namespace std;

class Player : public DynamicObject
{
protected:
	bool bActiveHurt;
	bool _bHurt;
	DWORD _localHurtTime;
	DWORD _deltaHurtTime;
	bool _usingCross;
	bool _usingWatch;
public:
	EnumID _weaponID;
	bool _hasWeapon;

	GSprite *simonJump;

	float _vLast;
	Action _action;

	bool _hasJump;
	float _heightJump;
	float _a;			//gia toc 
	bool _allowPress;		//Cho phep nhan phim
	bool _hasSit;
	bool _onLand;
	bool _hasFall;			//Simon dang rot
	//----------------Khoi Tao
	Player(void);
	Player(int, int);
	Player(int, int, LPDIRECT3DDEVICE9);

	~Player(void);
	//----Simon Action----------------
	void Update(int deltaTime);
	void TurnLeft();
	void TurnRight();
	void Jump();
	//void KnockBack();
	//void Stop();
	void Draw(GCamera*);

	void Sit();
	bool IsFight();
	void Initialize();
	D3DXVECTOR2* getPos();
};

#endif

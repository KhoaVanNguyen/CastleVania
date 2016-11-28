#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "DynamicObject.h"
#include <math.h>
#include "MorningStar.h"
using namespace std;

class Player : public DynamicObject
{
public:
	GSprite *playerJump;
	GSprite *fightingSprite;
	GSprite *fightingSittingSprite;


	MorningStar* morningStar;

	float _direction;
	Action _action;
	float _heightJump; 
	bool _allowPress;
	bool _hasSit;
	bool _hasJump;
	float _a;
	float _vLast;
	//----------------Khoi Tao
	Player(void);
	Player(int, int);
	Player(int, int, LPDIRECT3DDEVICE9);

	~Player(void);
	//---- Action----------------
	void Update(int deltaTime);
	void TurnLeft();
	void TurnRight();
	void Jump();
	void Stop();
	void Fight();
	void OnFight(int t);

	void Draw(GCamera*);
	void Fall();
	void Sit();
	D3DXVECTOR2* getPos();
};

#endif

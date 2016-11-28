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
	GSprite *playerStair;

	GameObject* _stair;	//Thong tin stair;

	MorningStar* morningStar;

	float _vLast;
	Action _action;
	float _heightJump;
	bool _allowPress;
	bool _hasSit;
	//----stair//
	bool _hasJump;
	bool _hasStair; // co len cau thang 
	float _a; // gia toc
	
	bool _onStair;
	EKindStair _kindStair;
	bool _upStair;
	bool _downStair;
	bool OnStair();
	bool _stopOnStair;	// len, xuong, dung im tren cau thang
	int rangeStair; // Khoang cach tu simon den chan cau thang
	bool _colStair;	//kiem tra xem simon co cham 2 dau cau thang ko
	bool _outStair; //kiem tra cho phep simon ra khoi cau thang
	int _timeSpawn;	//
	
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
	//--------------// Stair
	void UpStair();
	void UpdatePlayerStair(int t);
	void ResetStair();
	//-------------// 
	void Draw(GCamera*);
	void Fall();
	void Sit();
	D3DXVECTOR2* getPos();
};

#endif
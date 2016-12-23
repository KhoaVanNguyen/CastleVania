#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "DynamicObject.h"
#include <math.h>
#include "MorningStar.h"
#include "CEnum.h"
//#include "Weapon.h"
#include "Dagger.h"
#include "ThrowAxe.h"
#include "Boomerang.h"
#include "HolyWater.h"
using namespace std;




class Player : public DynamicObject
{
protected:
	
public:
	bool _usingCross;
	bool _usingStopWatch;
	// for testing
	int currentCollideWithID;

	// cross Item

	GSprite *playerJump;
	GSprite *fightingSprite;
	GSprite *fightingSittingSprite;
	GSprite *playerStair;
	GSprite *playerKnockBack;
	GSprite *playerUpStair;
	GSprite *playerDeathSprite;

	GameObject* _stair;	//Thong tin stair;

	MorningStar* morningStar;

	float _vLast;
	Action _action;
	float _heightJump;
	bool _allowPress;
	bool _hasSit;
	bool _hasKnockBack;
	bool _hasMagicalBall;
	//----stair//
	bool _hasJump;
	bool _colBottomStair; // co len cau thang 
	float _a; // gia toc



	bool _isHurted; // Có đang bị mất máu không?
	bool _onMovingPlatform;
	bool _onLand;
	bool _beFallOutScreen; // rớt ra khỏi màn hình

	bool _onStair;
	EKindStair _kindStair;
	bool _upStair;
	bool _downStair;
	bool OnStair();
	bool _stopOnStair;	// đứng im trên cầu thang.
	int rangeStair; // Khoang cach tu player den chan cau thang
	bool _colStair;	//Có va chạm với 1 trong 2 đầu của cầu thang.
	bool _outStair; //Coi thử player có đã ra ngoài cầu thang chưa
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
	void DownStair();
	void OutStair();
	void UpdatePlayerStair(int t);
	void ResetStair();
	//-------------// 
	//------------Weapon

	// vũ khí
	list<Weapon*> *weapons;
	EnumID _weaponID;
	bool _usingWeapon; //Co cho su dung dung vk ko? - co dang nhan DIK_Q?
	bool _hasWeapon;
	void UseWeapon();
	void SetWeapon();
	void ChangeWeapon(EnumID weaponID);

	void Draw(GCamera*);
	void Fall();
	void Sit();

	void UpgradeMorningStar();

	//--------------Collision
	void Collision(list<GameObject*> &obj, float dt);
	D3DXVECTOR2* getPos();
	void KnockBack();

	Box GetBox();
	// Change Camera:
	
	GameObject *_door;
	bool _colDoor;
	EDirectDoor GetDirectDoor();
	EDirectDoor _directDoor;
	void SetDirectDoor(EDirectDoor _direct);
	
	bool AutoMove(int &range, int dt);


	// For hurting

	DWORD _deltaHurtTime;
	bool _hidden;
	DWORD _startToHiddenTime;

	bool IsHurting();
	bool _bHurt = false;
	
	// Death
	void Die(int &_timeCount);
	bool _isDie;
	bool _isReset;
};

#endif
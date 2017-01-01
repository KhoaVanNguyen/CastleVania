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
private:



public:
	int  getCurrentPosXPlayer();
	// for testing
	int currentCollideWithID;


	// Sprite
	GSprite *playerJump;
	GSprite *fightingSprite;
	GSprite *fightingSittingSprite;
	GSprite *playerStair;
	GSprite *playerKnockBack;
	GSprite *playerUpStair;
	GSprite *playerDeathSprite;
	GSprite *playerFightingDownStairSprite;
	GSprite *playerFightingUpStairSprite;
	GameObject* _stair;	//Thong tin stair
	MorningStar* morningStar;

	float _vLast;
	Action _action;
	float _heightJump;
	bool _allowPress;
	bool _hasSit;
	bool _hasKnockBack;
	bool _hasMagicalBall;

	// Cầu thang
	bool _hasJump;
	bool _colBottomStair; // co len cau thang 
	float _a; // gia toc

	bool abc;
	bool getdata();

	bool _isHurted; // Có đang bị mất máu không?
	bool _onMovingPlatform;
	bool _movingByMovingPlatform;
	bool _onLand;
	bool _beFallOutScreen; // rớt ra khỏi màn hình
	float vColMoving;
	bool _onStair;
	EKindStair _kindStair;
	bool _upStair;
	bool _downStair;
	bool OnStair();
	bool _stopOnStair;	// đứng im trên cầu thang.
	int rangeStair; // Khoang cach tu player den chan cau thang
	bool _colStair;	//Có va chạm với 1 trong 2 đầu của cầu thang.
	bool _outStair; //Coi thử player có đã ra ngoài cầu thang chưa
	int _timeOnAStair;	// thời gian trên 1 bậc cầu thang
	bool _stop; // ngừng lại khi chạm Barrier.

	// Action
	void Update(int deltaTime);
	void Draw(GCamera*);

	void TurnLeft();
	void TurnRight();
	void Jump();
	void Stop();
	void Fight();
	void OnFight(int t);
	void Fall();
	void Sit();
	// Stair
	void UpStair();
	void DownStair();
	void OutStair();
	void UpdatePlayerStair(int t);
	void ResetStair();

	// vũ khí
	bool _usingCross;
	bool _usingStopWatch;
	list<Weapon*> *weapons;
	EnumID _weaponID;
	bool _usingWeapon; //Co cho su dung dung vk ko? - co dang nhan DIK_Q?
	bool _hasWeapon;
	void UseWeapon();
	void SetWeapon();
	void ChangeWeapon(EnumID weaponID);
	
	
	void UpgradeMorningStar();

	// Collision
	void Collision(list<GameObject*> &obj, float dt);
	D3DXVECTOR2* getPos();
	void KnockBack();

	Box GetBox();
	// Change/Move Camera:
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
	void DecreaseHP(GameObject*);

	// Khoi Tao
	Player(void);
	Player(int, int);
	Player(int, int, LPDIRECT3DDEVICE9);
	~Player(void);
};

#endif
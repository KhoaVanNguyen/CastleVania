#ifndef _medusa_H_
#define _medusa_H_

#include "DynamicObject.h"
//#include "MagicalCrystal.h"
#include <vector>
#include "LittleSnake.h"
using namespace std;

#define QUEEN_medusa_STATE 20
#define QUEEN_medusa_SLEEP_STATE 10
#define QUEEN_medusa_STOP_STATE 2
#define QUEEN_medusa_SPEED_X 0.3f
#define LITTLE_SNAKE_SPEED_X 0.3f
#define QUEEN_medusa_DIE_RATE 10
#define DEAD_TIME 1500
#define PI 3.14f
#define T 1000
#define A 20
#define QUEEN_medusa_INACTIVE_RATE 1

//
//enum ERouterType
//{
//	Parabol,
//	Line,
//	Horizontal,
//	Vertical
//};

enum EMedusaState
{
	InActive,
	Stop,
	Moving,
	Dead,
	Cancel
};

class Medusa : public DynamicObject
{
protected:
	GSprite* _sleepSprite;
	GSprite* _fightSprite;
	GSprite* _deadSprite;
	D3DXVECTOR2* _routerInfo;
	vector<D3DXVECTOR2*> _vStopPos;
	D3DXVECTOR2* _gold;
	int _previousStopPos;
	int _currentStopPos;
	//ERouterType _eRouterType;
	DWORD _localTime;

	list<DynamicObject*> *_vLittleSnake;

	EMedusaState _state;
	D3DXVECTOR2* _playerPos;
	float _deltaPhi;
	float _posY0;


	void _initialize();
	void _onStop(int deltaTime_);
	void _onMoving(int deltaTime_);
	void _onDead(int deltaTime_);
	void _onInActive(int deltaTime_);

	bool _isKiss(D3DXVECTOR2 boss_, D3DXVECTOR2 gold_);
	void _drawSnakes(GCamera* camera_);
	void _updateSnakes(int deltaTime_);

public:
	bool _hasGetUp;
	//MagicalCrystal* magicalCrystal;
	Medusa(void);
	Medusa(float posX, float posY, EnumID id);
	virtual void Update(int deltaTime_);
	void Update(int deltaTime_, D3DXVECTOR2* simonPos_);
	virtual void Draw(GCamera* camera_);
	virtual void Collision(list<GameObject*> obj, int dt);
	void getUp();
	void setDead();
	void ReceiveDamage(int damagePoint);
	bool GetState();
	~Medusa(void);
public:

};

#endif


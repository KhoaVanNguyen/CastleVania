#ifndef _medusa_H_
#define _medusa_H_

#include "DynamicObject.h"
#include "MagicalBall.h"
#include <vector>
#include "LittleSnake.h"
using namespace std;

#define QUEEN_medusa_STATE 20
#define SLEEP_STATE 10
#define STOP_STATE 2
#define SPEED_X 0.3f
#define BANDAGE_SPEED_X 0.3f
#define DIE_RATE 10
#define DEAD_TIME 1500
#define PI 3.14f
#define T 1000
#define A 20
#define Sleeping_RightCameraATE 1

enum EMedusaState
{
	Sleeping,
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
	vector<D3DXVECTOR2*> _listStopPos;
	D3DXVECTOR2* _nextStopPos;
	int _previousStopPos;
	int _currentStopPos;
	DWORD _localTime;

	list<DynamicObject*> *_LittleSnake;

	EMedusaState _state;
	D3DXVECTOR2* _playerPos;
	float _deltaPhi;
	float _posY0;


	void _initialize();
	void _Stoping(int deltaTime_);
	void _Moving(int deltaTime_);
	void _Deading(int deltaTime_);
	
	bool _leaveStopPos(D3DXVECTOR2 boss_, D3DXVECTOR2 _nextStopPos);
	void _drawSnakes(GCamera* camera_);
	void _updateSnakes(int deltaTime_);

public:
	bool HasGetUp;
	Medusa(void);
	Medusa(float posX, float posY, EnumID id);
	virtual void Update(int deltaTime_);
	void Update(int deltaTime_, D3DXVECTOR2* playerPos_);
	virtual void Draw(GCamera* camera_);
	virtual void Collision(list<GameObject*> obj, int dt);
	void getUp();
	void setDead();
	void ReceiveDamage(int damagePoint);
	bool StateCancel();
	int getHp();
	~Medusa(void);
public:

};

#endif


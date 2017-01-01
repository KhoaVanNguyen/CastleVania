#ifndef _MUMMY_H_
#define _MUMMY_H_

#include "DynamicObject.h"
#include "MagicalBall.h"
#include <vector>
#include "Bandages.h"
using namespace std;

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

enum EMummyState
{
	Mummy_Stoping,
	Mummy_Moving
};

class Mummy : public DynamicObject
{
protected:
	

	int _timeSpan;
	bool _drawLeft;
	bool _isSleeping;
	EMummyState _state;
	bool _attackmode;
	int deltaX;
	int oldX;
	int timeDelay;
	
	vector<D3DXVECTOR2*> _listStopPos;
	D3DXVECTOR2* _nextStopPos;
	int _previousStopPos;
	int _currentStopPos;
	DWORD _localTime;

	list<DynamicObject*> *_bandages;


	void _drawBandages(GCamera* camera_);

	void _updateBandages(int deltaTime_);

public:

	bool HasGetUp;
	Mummy(void);
	Mummy(float posX, float posY);
	//virtual void Update(int deltaTime_);
	virtual void Update(int, int, int);
//	void Update(int deltaTime_, D3DXVECTOR2* playerPos_);
	virtual void Draw(GCamera* camera_);
	virtual void Collision(list<GameObject*> obj, int dt);
	//void ReceiveDamage(int damagePoint);

	~Mummy(void);
public:

};

#endif


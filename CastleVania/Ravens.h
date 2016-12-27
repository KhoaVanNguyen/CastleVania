#pragma once
#include "DynamicObject.h"
#include "Player.h"
#define RAVENS_STOP_STATE 2
#define RAVENS_STATE 1.0f
#define _timeDelay 50

enum ERavenState
{
	Stoping,
	moving
};

class Ravens : public DynamicObject
{
	bool _isSleeping;
	ERavenState _state;
	bool _attackmode ;
	int deltaX;
	int oldX;
	int timeDelay;
public:
	DWORD _localTime;
	Ravens(void);
	Ravens(float posX, float posY);
	~Ravens();
	void Stoping(int deltatime);
	void Moving(int deltatime);
	// 0 trong khoang thoi gian localtimeT kiem tra co va cham gach hay khong neu va cham gach thi Moving len voi goc 45 do. Moving01
	// 1 kiem tra ne posY = a, thi moving xuong goc 45 do ,Moving12
	// 2 Kiem tra neu posY = b, thi Moving ngang , Moving 23
	//void Moving(int deltatime);
	//if 
	// if (Moving 01)
	//phuo trinh 01
	virtual void Update(int deltatime);
	virtual void Collision(list<GameObject*> obj, int dt);

};


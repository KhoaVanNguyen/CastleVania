#pragma once
#include "DynamicObject.h"
#define RAVENS_STOP_STATE 2
#define RAVENS_STATE 20
enum ERavenState
{
	Stoping0,
	Stoping1,
	Stoping2,
	Moving01, 
	Moving12,
	Moving23
};

class Ravens : public DynamicObject
{
public:
	DWORD _localTime;
	ERavenState _state;
	Ravens(void);
	Ravens(float posX, float posY);
	~Ravens();
	void Stoping(int deltatime); 
	// 0 trong khoang thoi gian localtimeT kiem tra co va cham gach hay khong neu va cham gach thi Moving len voi goc 45 do. Moving01
	// 1 kiem tra ne posY = a, thi moving xuong goc 45 do ,Moving12
	// 2 Kiem tra neu posY = b, thi Moving ngang , Moving 23
	void Moving(int deltatime);
	//if 
	// if (Moving 01)
	//phuo trinh 01
	virtual void Update(int deltatime);
	virtual void Collision(list<GameObject*> obj, int dt);

};


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

	bool _drawLeft;
	bool _isSleeping;
	ERavenState _state;
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
	void  SetActive(float x, float y);
	void Draw(GCamera* camera);
	//virtual void Update(int deltatime);
	virtual void Update(int, int, int);
	virtual void Collision(list<GameObject*> obj, int dt);

};


#pragma once
#include "GameObject.h"
#include "DynamicObject.h"

#define STUPID_DOOR_RATE 4

#define STUPID_DOOR_SPEED_UP 0.03f
#define STUPID_DOOR_SPEED_DOWN 0.1f
#define STUPID_DOOR_Y_MAX 1040
#define STUPID_DOOR_Y_MIN 900

class TrapDoor :
	public 	GameObject
{
protected:
	// Return result
	// 1 if >= max position of center
	// -1 if <= min position of center
	// 0: the others
	int _compareBound();
	float _vUp;
	float _vDown;
	float _yMax;
	float _yMin;
	int _animationRate;
	DWORD _localAnimationTime;
	DWORD _localTime;
	void _initialize();
	void _goUp();
	void _goDown();

	// round to int number
	int _round(float number_);
public:
	TrapDoor(void);
	//Note: yMax_, yMin_ is not type center's position but _yMax, _yMin is in type center's position
	TrapDoor(float posX_, float posY_, float yMax_ = STUPID_DOOR_Y_MAX, float yMin_ = STUPID_DOOR_Y_MIN, float vUp_ = STUPID_DOOR_SPEED_UP, float vDown_ = STUPID_DOOR_SPEED_DOWN, int animationRate_ = STUPID_DOOR_RATE);
	virtual void  Update(int deltaTime_);
	virtual void Draw(GCamera* camera_);
	virtual void Collision(list<GameObject*> obj, int dt);
	~TrapDoor(void);
};


#pragma once
#include "DynamicObject.h"
#include "CEnum.h"
#define PI 3.14f
#define T 1000
#define A 10
#define THROW_AXE_ANPHA 60
#define THROW_AXE_SPEED_X 1
#define G 0.01f
class Skeletons : public DynamicObject
{

	float _deltaPhi;
	D3DXVECTOR2* _playerPos;
public:
	bool vangratruoc, vangrasau;
	float _anpha;
	float _posX0;
	int huong;
	float _posY0;
	~Skeletons();
	Skeletons(void);
	Skeletons(float x, float y);
	virtual void Update(int deltaTime_, D3DXVECTOR2 playerPos_);
	void Collision(list<GameObject*> obj, int dt);
	virtual void Draw(GCamera* camera_);
};




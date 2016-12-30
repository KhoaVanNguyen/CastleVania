#ifndef _BONE_H_
#define _BONE_H_

#include "DynamicObject.h"


#define THROW_AXE_ANPHA 45
#define THROW_AXE_SPEED_X 1.5
#define G 0.01f

class Bone : public DynamicObject
{
	int _timeSpawn;


	D3DXVECTOR2* _nextStopPos;
	float _anpha;
	float _posX0;
	float _posY0;

public:
	Bone(void);
	Bone(float x, float y, EnumID id);
	void Update(int dt);
	~Bone(void);
	void Draw(GCamera *camera);
	void Collision(list<GameObject*> obj, int dt);
};

#endif
#ifndef _SKELETONS_H_
#define _SKELETONS_H_

#include "DynamicObject.h"
#include "CEnum.h"
#include "Bone.h"

#define THROW_AXE_ANPHA 45
#define THROW_AXE_SPEED_X 1.5
#define G 0.01f

enum ESkeletonState
{
	Skeleton_Stoping,
	Skeleton_Moving
};

class Skeletons :public DynamicObject
{
private:
	//
	int _timeSpan;
	bool _drawLeft;
	bool _isSleeping;
	int deltaX;
	int oldX;
	int timeDelay;
	ESkeletonState _state;
	DWORD _localTime;
	int distanceXToPlayer = 0;
	int distanceYToPlayer = 0;
	//

	// For jumping
	D3DXVECTOR2* _nextStopPos;
	float _anpha;
	float _posX0;
	float _posY0;



	///
	void Jump();
	list<DynamicObject*> *_bones;
	void DrawBones(GCamera* camera_);

	void UpdateBones(int deltaTime_);

public:
	bool _hasJump;
	float _heightJump;

	Skeletons(void);
	Skeletons(float _x, float _y);
	//void Update(int dt);

	virtual void Update(int, int, int);
	void Collision(list<GameObject*> obj, int dt);

//	virtual void Collision(list<GameObject*> obj, int dt);



	void SetActive(float x, float y);
	void Draw(GCamera* camera);
	~Skeletons(void);
};

#endif


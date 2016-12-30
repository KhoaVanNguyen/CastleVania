#ifndef _SKELETONS_H_
#define _SKELETONS_H_

#include "DynamicObject.h"
#include "CEnum.h"
#include "Bone.h"
class Skeletons :public DynamicObject
{
private:

	int _timeSpan;
	void Jump();
	list<DynamicObject*> *_bones;
	void DrawBones(GCamera* camera_);

	void UpdateBones(int deltaTime_);

public:
	bool _hasJump;
	float _heightJump;

	Skeletons(void);
	Skeletons(float _x, float _y);
	void Update(int dt);
	void Collision(list<GameObject*> obj, int dt);

//	virtual void Collision(list<GameObject*> obj, int dt);



	void SetActive(float x, float y);
	void Draw(GCamera* camera);
	~Skeletons(void);
};

#endif


#ifndef _Panthers_H_
#define _Panthers_H_

#include "DynamicObject.h"
#include "EnumManager.h"

class Panthers :public DynamicObject
{
private:
	void Jump();
public:
	bool _hasJump;
	float _heightJump;

	Panthers(void);
	Panthers(float _x, float _y);
	void Update(int dt);
	void Collision(list<GameObject*> obj, int dt);
	void SetActive(float x, float y);
	void Draw(GCamera* camera);
	~Panthers(void);
};

#endif
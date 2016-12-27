#ifndef _FLEAMAN_H_
#define _FLEAMAN_H_

#include "DynamicObject.h"
#include "CEnum.h"
#define TIME_WATING 300

class Fleaman : public DynamicObject
{

private:
	bool _isSleep; // dang dung im tren tuong.
	int _xDestinate = 0;
	int _yDestinate = 0;
	int _countdown = 0;
	int _currentState = FLEAMAN_STATE::WAIT;
	bool _firstActive = false;

	bool getUp;

	float limit;
public:

	
	Fleaman(void);
	Fleaman(float x, float y);
	~Fleaman(void);
	void MoveUpdate(float deltatime);
	void SetFrame(float deltattime);
	void ChangeState(int state);

	void Update(int deltaTime);
	void Draw(GCamera* camera);
	void SetActive(float x, float y);
	void Collision(list<GameObject*> obj, int dt);
	
};
#endif
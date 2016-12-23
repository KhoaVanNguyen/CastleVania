#ifndef _Skeletons_H_
#define _Skeletons_H_

#include "DynamicObject.h"
#include "MagicalBall.h"
#include <vector>
#include "LittleSnake.h"
using namespace std;

#define SKELETONS_ANPHA 45
#define SKELETONS_SPEED_X 1.5
#define G 0.01f

#define QUEEN_Skeletons_SPEED_X 0.3f
#define LITTLE_SNAKE_SPEED_X 0.3f
#define QUEEN_Skeletons_DIE_RATE 10
#define DEAD_TIME 1500
#define PI 3.14f
#define T 1000
#define A 20
#define QUEEN_Skeletons_SleepinG_RightCameraATE 1


// chuyen dong sang trai phai va nem xuong
//Neu gap o so 1 thì nhay len
//Neu gap o so 2 thi ban nguoc lai
//Nem xuong trong update sau 1 khoang thoi gina xac dinh


class Skeletons : public DynamicObject
{
protected:
	GSprite* _sprite;
	vector<D3DXVECTOR2*> _listStopPos;
	D3DXVECTOR2* _nextStopPos;
	DWORD _localTime;

	list<DynamicObject*> *_LittleSnake;
	D3DXVECTOR2* _playerPos;
	float _anpha;
	float _posX0;
	float _posY0;
	float _deltaPhi;
	void _initialize();
	void _drawSnakes(GCamera* camera_);
	void _updateSnakes(int deltaTime_);

public:
	D3DXVECTOR2* playerpos;
	Skeletons(void);
	Skeletons(float posX, float posY, EnumID id);
	virtual void Update(int deltaTime_);
	virtual void Draw(GCamera* camera_);
	virtual void Collision(list<GameObject*> obj, int dt);
	void getUp();
	void setDead();
	void ReceiveDamage(int damagePoint);
	bool StateCancel();
	~Skeletons(void);
	void prepare(float playerX_, float playerY_, float direct_);
	 void prepare(D3DXVECTOR2* playerpos);
};

#endif


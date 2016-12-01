#ifndef _PHANTOMBAT_H_
#define _PHANTOMBAT_H_

//#include "MagicalCrystal.h"
#include "DynamicObject.h"
#include <vector>
using namespace std;

#define PHANTOM_BAT_REST_RATE 2
#define PHANTOM_BAT_RATE 5
#define PHANTOM_BAT_DIE_RATE 5
#define SPEED_X 0.2f
#define DEAD_TIME 1500

enum ERouterType
{
	Parabol,
	Line,
	Horizontal,
	Vertical
};

class PhantomBat : public DynamicObject
{
protected:
	
	D3DXVECTOR2* _routerInfo;
	vector<D3DXVECTOR2*> _vSleepPos;
	D3DXVECTOR2* _gold;
	int _currentSleepPos;
	ERouterType _eRouterType;
	DWORD _localTime;
	//phantomBat state is the State of phantom bat
	//0: sleep
	//1: on fly to SIMON
	//2: in the simon
	//3: on fly to rest place;
	//4: on rest place
	//-1: on die 
	// -2: cancel
	int _phantomBatState;
	D3DXVECTOR2* _simonPos;
	void _initialize();
	void _onSleep(int deltaTime_);
	void _onFly(int deltaTime_);
	void _onGold(int deltaTime_);
	void _onDead(int deltaTime_);

	void _updateSleepPos();
	bool _isKiss(D3DXVECTOR2* phantomBat_, D3DXVECTOR2* gold_);

public:
	PhantomBat(void);
	PhantomBat(float posX, float posY, EnumID id);
	virtual void Update(int deltaTime_);
	void Update(int deltaTime_, D3DXVECTOR2* simonPos_);
	virtual void Draw(GCamera* camera_);
	void getUp();
	void setDead();
	void ReceiveDamage(int damagePoint);
	bool GetState();
	void Collision(list<GameObject*>, int);
	~PhantomBat(void);
};

#endif
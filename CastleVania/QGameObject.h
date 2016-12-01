#ifndef _QGAMEOBJECT_H_
#define _QGAMEOBJECT_H_

#include <list>
#include <map>
#include "HeaderObj.h"
#include "Singleton.h"
#include "GCamera.h"
#include <fstream>
#include <iostream>
#include <conio.h>
#include <string>
#include <sstream>
#include <time.h>
#include <random>

//using namespace std;

class QGameObject
{
protected:
	

	D3DXVECTOR2 posDoor;
public:
	DWORD _localHurtTime;
	DWORD _deltaHurtTime;
	bool bActiveHurt;


	list<GameObject*> *_staticObject;
	list<GameObject*> *_dynamicObject;

	QGameObject(void);
	~QGameObject(void);

	QGameObject(string);
	D3DXVECTOR2 GetPosDoor();	//Lay vi tri de ve canh cua qua stage
	void Draw(GCamera *camera);
	void Update(int deltaTime);
	
	void Collision(int dt);
	int RemoveAllObjectInCamera(D3DXVECTOR2);
	void RemoveAllObject();
	
	
};

#endif
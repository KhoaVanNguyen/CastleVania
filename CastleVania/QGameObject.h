#ifndef _QGAMEOBJECT_H_
#define _QGAMEOBJECT_H_

#include <list>
#include <map>
#include "HeaderObj.h"
#include "TextureManager.h"
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
	Medusa *_medusa;
public:
	


	list<GameObject*> *_staticObject;
	list<GameObject*> *_dynamicObject;

	QGameObject(void);
	~QGameObject(void);

	QGameObject(string);
	D3DXVECTOR2 GetPosDoor();	//Lay vi tri de ve canh cua qua stage
	void Draw(GCamera *camera);
	void Update(int deltaTime);
	void Update(int, int, int deltaTime);

	void Collision(int dt);
	int RemoveAllObjectInCamera(D3DXVECTOR2);
	void RemoveAllObject();
	Medusa* getMedusa();

	// For StopWatch
	DWORD _deltaHurtTime;
	bool _pausing;
	DWORD _startToPauseTime;
	void PauseUpdate();
	bool IsPausing();
	
	
};

#endif
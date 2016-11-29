#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "GSprite.h"
#include "Singleton.h"
#include "GCamera.h"
#include "SweptAABB.h"
#include <list>
using namespace std;
class GameObject
{
public:
	GSprite* sprite;
	//posX, posY -> toa do center
	float posX, posY;
	int width;
	int height;
	float vX, vY;
	ObjectType type;
	bool canMove;
	bool active;
	//bool death;
	//Cac thong so
	EnumID id;
	//int hearts;
	//int hp;
	//int damage;
	//int point;

	virtual void Update(int dt);
	virtual void Draw(GCamera*);
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int t);
	virtual void OnKeyDown(int KeyCode);
	virtual void CreateSprite();
	virtual void SetActive(float x, float y);
	virtual void SetActive();
	GameObject(void);
	GameObject(float posX, float posY, EnumID id);
	~GameObject(void);
};

#endif

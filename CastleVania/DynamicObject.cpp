#include "DynamicObject.h"
#include <d3d9.h>

DynamicObject::DynamicObject(void) : GameObject()
{
}

DynamicObject::DynamicObject(float _posX, float _posY, float _vX, float _vY, EnumID id)
	: GameObject(_posX, _posY, id)
{
	//Di nguoc huong lai player
	vX = _vX;
	vY = _vY;
	canMove = true;
	//active = false;
	Initialize();
}

void DynamicObject::Update(int deltaTime)
{
	//if (sprite == NULL || !active)
	//	return;
	//posX += vX*deltaTime;
	//if (posX <= width / 2 + 2 || posX >= G_MapWidth - (width / 2 - 2))
	//	vX = -vX;
	//posY += vY*deltaTime;
	//sprite->Update(deltaTime);
}

void DynamicObject::Draw(GCamera* camera)
{
	//if (sprite == NULL || !active)
	//	return;
	//D3DXVECTOR2 center = camera->Transform(posX, posY);
	//if (vX > 0)
	//	sprite->DrawFlipX(center.x, center.y);
	//else
	//	sprite->Draw(center.x, center.y);
}

void DynamicObject::SetActive(float x, float y)
{
	//if (active) return;
	//if (abs(posX - x) <= 350 && abs(posY - y) <= 200)
	//{
	//	if (posX - x > 0)
	//	{
	//		vX = -vX;
	//	}
	//	active = true;
	//}
}

DynamicObject::~DynamicObject(void)
{
}

//void DynamicObject::Collision(list<GameObject*> obj, int dt)
//{
//	//list<GameObject*>::iterator _itBegin;
//	//for (_itBegin = obj.begin(); _itBegin != obj.end(); _itBegin++)
//	//{
//	//	float moveX;
//	//	float moveY;
//	//	float normalx;
//	//	float normaly;
//	//	GameObject* other = (*_itBegin);
//	//}
//}

//Box DynamicObject::GetBox()
//{
//	Box result(posX - width / 2, posY + height / 2, width, height, vX, 0);
//	return result;
//}

void DynamicObject::Initialize()
{
	//bActiveHurt = false;
	//_localHurtTime = 0;
}

//bool DynamicObject::IsHurt()
//{
//	//if (!bActiveHurt)
//	//	return false;
//	//DWORD now = GetTickCount();
//	//DWORD deltaTime = now - _localHurtTime;
//	//if (deltaTime >= 300)
//	//{
//	//	bActiveHurt = false;
//	//}
//	return true;
//}
//
//void DynamicObject::ReceiveDamage(int damagePoint)
//{
//	//if (!IsHurt())
//	//{
//	//	if (hp <= 0)
//	//		return;
//	//	hp -= damagePoint;
//	//	if (hp == 0)
//	//		death = true;
//	//	bActiveHurt = true;
//	//	_localHurtTime = GetTickCount();
//	//}
//}
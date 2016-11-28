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
	active = true;
	Initialize();
	//
}

void DynamicObject::Update(int deltaTime)
{
	if (sprite == NULL || !active)
		return;
	posX += vX*deltaTime;
	if (posX <= width / 2 + 2 || posX >= G_MapWidth - (width / 2 - 2))
		vX = -vX;
	posY += vY*deltaTime;
	sprite->Update(deltaTime);
}

void DynamicObject::Draw(GCamera* camera)
{
	if (sprite == NULL || !active)
		return;
	D3DXVECTOR2 center = camera->Transform(posX, posY);
	if (vX < 0)
		sprite->DrawFlipX(center.x, center.y);
	else
		sprite->Draw(center.x, center.y);
}

void DynamicObject::SetActive(float x, float y)
{
}

DynamicObject::~DynamicObject(void)
{
}

void DynamicObject::Initialize()
{
}
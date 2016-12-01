#include "MedusaHeads.h"

#define A 80
#define PI 3.14
#define T 0.5

MedusaHeads::MedusaHeads(void) : DynamicObject()
{
}

MedusaHeads::MedusaHeads(float _x, float _y) : DynamicObject(_x, _y, 0.3f, 0, EnumID::MedusaHeads_ID)
{
	_alpha = 0;
	type = ObjectType::Enemy_Type;
	//point = 300;
	_posY0 = posY;
}

MedusaHeads::~MedusaHeads(void)
{
}

void MedusaHeads::MoveSinPath(int deltaTime)
{
	//float nextX = vX * deltaTime + posX;
	//float nextY = 10 * sin(nextX/10);
	float nextY = A * cos((2 * PI*deltaTime) / T + _alpha);
	_alpha += (2 * PI*deltaTime) / T;
	vY = nextY;
	posX += vX * deltaTime;
	posY = nextY + _posY0;
}

void MedusaHeads::Draw(GCamera* camera)
{
	if (sprite == NULL || !active)
		return;
	if (posX + width / 2 <= camera->viewport.x || posX - width / 2 >= camera->viewport.x + G_ScreenWidth)
	{
		active = false;
		return;
	}
	D3DXVECTOR2 center = camera->Transform(posX, posY);
	if (vX > 0)
		sprite->DrawFlipX(center.x, center.y);
	else
		sprite->Draw(center.x, center.y);
}

void MedusaHeads::Collision(list<GameObject*> obj, int dt) {}

void MedusaHeads::Update(int deltaTime)
{
	//posY += vY*deltaTime;
	MoveSinPath(deltaTime);
	sprite->Update(deltaTime);
}
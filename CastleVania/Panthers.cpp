#include "Panthers.h"

#define SPEED_X 0.4f
#define SPEED_Y 0.3f
#define MAX_HEIGHT 20.0f

Panthers::Panthers(void) :DynamicObject()
{
}

Panthers::Panthers(float x, float y) : DynamicObject(x, y, 0, -0.4, EnumID::Panthers_ID)
{
	active = true;
	_hasJump = false;
	_heightJump = 0;
	type = ObjectType::Enemy_Type;
	//point = 200;
}

void Panthers::Draw(GCamera* camera)
{
	if (sprite == NULL || !active)
		return;
	if ((posX + width / 2 <= camera->viewport.x || posX - width / 2 >= camera->viewport.x + G_ScreenWidth)
		&& sprite->GetIndex() != 0)
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

void Panthers::Collision(list<GameObject*> obj, int dt)
{
	
}

void Panthers::Update(int dt)
{
	/*if (sprite->GetIndex() == 0)
		return;*/
	posX += vX *dt;
	if (posX <= width / 2 + 5 || posX >= G_MapWidth - width / 2 - 5)
		vX = -vX;
	//posY += vY *dt;
	if (!_hasJump)
		sprite->Update(dt);
	if (_hasJump)
	{
		_heightJump += vY * dt;
		if (_heightJump >= MAX_HEIGHT)
		{
			vY = -(SPEED_Y + 0.2f);
		}
	}
}

void Panthers::SetActive(float x, float y)
{
	if (abs(posX - x) <= 200)
	{
		if (abs(posY - y) <= 50)
		{
			vX = -SPEED_X;
			sprite = new GSprite(Singleton::getInstance()->getTexture(EnumID::Panthers_ID), 1, 3, 60);
		}
		else
		{
			if (abs(posY - y) <= 150)
			{
				Jump();
			}
		}
	}
}

void Panthers::Jump()
{
	if (vX > 0)
		vX = SPEED_X + 0.1f;
	else
		vX = -(SPEED_X + 0.1f);
	vY = SPEED_Y;
	_hasJump = true;
	_heightJump = 0.0f;
	sprite = new GSprite(Singleton::getInstance()->getTexture(EnumID::Panthers_ID), 1, 3, 60);
	sprite->SelectIndex(3);
}

Panthers::~Panthers(void)
{
}

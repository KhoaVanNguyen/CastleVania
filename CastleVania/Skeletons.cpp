#include "Skeletons.h"
#define SPEED_X 0.4f
#define SPEED_Y 0.6f
#define MAX_HEIGHT 20.0f

Skeletons::Skeletons(void) :DynamicObject()
{
}

Skeletons::Skeletons(float x, float y) : DynamicObject(x, y, 0, -0.4, EnumID::Skeletons_ID)
{
	active = true;
	_hasJump = false;
	_heightJump = 0;
	type = ObjectType::Enemy_Type;
	point = 200;
}

void Skeletons::Draw(GCamera* camera)
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
void Skeletons::Collision(list<GameObject*> obj, int dt)
{
	list<GameObject*>::iterator _itBegin;
	for (_itBegin = obj.begin(); _itBegin != obj.end(); _itBegin++)
	{
		float moveX;
		float moveY;
		float normalx;
		float normaly;
		GameObject* other = (*_itBegin);
		if (other->id == EnumID::Brick_ID)
		{
			Box box = this->GetBox();
			Box boxOther = other->GetBox();

			if (AABB(box, boxOther, moveX, moveY) == true)
			{
				if (vY < 0)
				{
					posY += moveY;
					if (_hasJump && _heightJump <= 0)
					{
						_hasJump = false;
						if (vX < 0)
							vX = SPEED_X;
						else
						{
							vX = -SPEED_X;
						}
						vY = 0;
					}
					return;
				}
				if ((posX - width / 2 - (other->posX - other->width / 2) <= 0
					|| posX + width / 2 - (other->posX + other->width / 2) >= 0)
					&& vY == 0)
					Jump();
			}

			if (AABB(box, boxOther, moveX, moveY) == false)
			{
				if (other->canMove == true)
				{
					box.vx -= boxOther.vx;
					box.vy -= boxOther.vy;
					boxOther.vx = 0;
					boxOther.vy = 0;
				}
				Box broadphasebox = GetSweptBroadphaseBox(box, dt);
				if (AABBCheck(GetSweptBroadphaseBox(box, dt), boxOther) == true)
				{
					float collisiontime = SweptAABB(box, boxOther, normalx, normaly, dt);
					if (collisiontime > 0.0f && collisiontime < 1.0f)
					{
						ECollisionDirect colDirect = GetCollisionDirect(normalx, normaly);
						// perform response here
						switch (colDirect)
						{
						case Colls_Left:
							if (vX > 0)
								vX = -vX;
							break;
						case Colls_Right:
							if (vX < 0)
								vX = -vX;
							break;
						case Colls_Bot:
							posY += vY * collisiontime;
							vY = 0;
							break;
						}
					}
				}
			}
		}
	}
}

void Skeletons::Update(int dt)
{
	if (sprite->GetIndex() == 0)
		return;
	//posX += vX *dt;
	if (posX <= width / 2 + 5 || posX >= G_MapWidth - width / 2 - 5)
		vX = -vX;
	posY += vY *dt;
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

void Skeletons::SetActive(float x, float y)
{
	if (abs(posX - x) <= 200)
	{
		if (abs(posY - y) <= 50)
		{
			//vX = -SPEED_X;
			sprite = new GSprite(Singleton::getInstance()->getTexture(EnumID::Skeletons_ID), 1, 1, 60);
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

void Skeletons::Jump()
{
	//if (vX > 0)
	//	vX = SPEED_X + 0.1f;
	//else
	//	vX = -(SPEED_X + 0.1f);
	vY = SPEED_Y;
	_hasJump = true;
	_heightJump = 0.0f;
	sprite = new GSprite(Singleton::getInstance()->getTexture(EnumID::Skeletons_ID), 0,1, 60);
	sprite->SelectIndex(0);
}

Skeletons::~Skeletons(void)
{
}
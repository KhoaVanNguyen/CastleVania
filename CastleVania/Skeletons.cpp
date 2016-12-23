#include "Skeletons.h"


Skeletons::Skeletons(void) : DynamicObject()
{
}

Skeletons::Skeletons(float _x, float _y) : DynamicObject(_x, _y, 0.3f, 0, EnumID::Skeletons_ID)
{
	_playerPos = new D3DXVECTOR2(0, 0);
	canBeKilled = true;
	type = ObjectType::Enemy_Type;
	point = 100;
	_posX0 = _x;
	_posY0 = _y;
	vangratruoc = false;
	vangrasau = false;
	huong = 1;
	IsSkeletons = true;
}

Skeletons::~Skeletons(void)
{
}

void Skeletons::Update(int deltaTime_, D3DXVECTOR2 playerPos_)
{
	
	if (sprite == NULL || !active)
		return;

	this->sprite->Update(deltaTime_);

	//this->_playerPos = playerPos_;
	
	if (playerPos_.x > posX)
	{
		_anpha = THROW_AXE_ANPHA;
		huong = 1;
	}
	else
	{
		_anpha = 180 - THROW_AXE_ANPHA;
		huong =-1;
	}

	
	

	if (vangratruoc == true  )
	{
		vX = THROW_AXE_SPEED_X*cos(_anpha);
		vY = THROW_AXE_SPEED_X*sin(_anpha) - G*deltaTime_;
		posX += vX*deltaTime_;
		float deltaPosX = posX - _posX0;
		posY = _posY0 + vY*deltaPosX / vX - 0.5*G*pow((deltaPosX / vX), 2);
		vangratruoc = false;
	}
	else
	{
		posX += vX*deltaTime_;
		if (posX <= width / 2 + 2 || posX >= G_MapWidth - (width / 2 - 2))
			vX = -vX;
		posY += vY*deltaTime_;
	}
	
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

		Box box = this->GetBox();
		Box boxOther = other->GetBox();
		if (AABB(box, boxOther, moveX, moveY) == true)
		{
			if (other->id == EnumID::BrickCollision_ID)

				vangratruoc = true;

		}
			
		//if (other->id != EnumID::Brick_ID)
		//{
		//	Box box = this->GetBox();
		//	Box boxOther = other->GetBox();

		//	if (AABB(box, boxOther, moveX, moveY) == true)
		//	{
		//		/*if (vY < 0)
		//		{
		//		posY += moveY;
		//		vY = 0;
		//		return;
		//		}
		//		if ((posX - width / 2 + 10) - (other->posX - other->width / 2) <= 0
		//		|| (posX + width / 2 - 10) - (other->posX + other->width / 2) >= 0)
		//		vX = -vX;
		//		}
		//		else
		//		if (AABB(box, boxOther, moveX, moveY) == false)
		//		{
		//		if (other->canMove == true)
		//		{
		//		box.vx -= boxOther.vx;
		//		box.vy -= boxOther.vy;
		//		boxOther.vx = 0;
		//		boxOther.vy = 0;
		//		}

		//		}*/
			//if(other->id == EnumID::BrickCollision_ID) vangratruoc= true;
				 //if (other->id == EnumID::28_ID) vangrasau= true;
	}
}

		
	

void Skeletons::Draw(GCamera* camera_)
{
	D3DXVECTOR2 center = camera_->Transform(posX, posY);
	 if (huong =1)
	sprite->DrawFlipX(center.x, center.y);
	else
	sprite->Draw(center.x, center.y);
}
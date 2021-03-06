#include "Skeletons.h"
#define SPEED_X 0.3f
#define SPEED_Y 0.5f
#define MAX_HEIGHT 20.0f

Skeletons::Skeletons(void) :DynamicObject()
{
}

Skeletons::Skeletons(float x, float y) : DynamicObject(x, y, 0, 0, EnumID::Skeletons_ID)
{
	_nextStopPos = new D3DXVECTOR2(0, 0);
	active = true;
	canBeKilled = true;
	neededPlayerPosition = true;
	_bones = new list<DynamicObject*>();
	_hasJump = false;
	_heightJump = 0;
	type = ObjectType::Enemy_Type;
	_localTime = 0;
	point = 200;
	_state = ESkeletonState::Skeleton_Stoping;


	///

	_anpha = THROW_AXE_ANPHA;
	_posX0 = posX = x + 20;
	_nextStopPos->x = posX + 100;


	_anpha = _anpha*(3.14 / 180);
	_posY0 = posY = y + 20;
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
	if (_drawLeft)
		sprite->Draw(center.x, center.y);
	else
		sprite->DrawFlipX(center.x, center.y);


	DrawBones(camera);
}


void Skeletons::Update(int playerX, int playerY, int dt)
{


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




	_timeSpan += dt;
	if (_timeSpan % 25 == 0) {
		_bones->push_back(new Bone(posX, posY + 10, EnumID::Bone_ID));


	}
	int randomDeltaX;
	switch (_state)
	{
	case ESkeletonState::Skeleton_Stoping:

	
		_localTime += dt;
		

		
		distanceXToPlayer = abs(playerX - posX);
		distanceYToPlayer = abs(playerY - posY);
		 if (distanceXToPlayer <= 200 && distanceYToPlayer <= 100) {
			_state = ESkeletonState::Skeleton_Moving;
			return;
		}

		break;
	case ESkeletonState::Skeleton_Moving:


		deltaX += (abs(oldX - posX));
		oldX = posX;


		if (playerX > posX) {
			_drawLeft = false;
			posX += vX*dt;

			// Jump to Right here
			Jump();
		}
		else {
			// Jump to Left here

			posX -= vX*dt;
			_drawLeft = true;
		}
	
		distanceXToPlayer = abs(playerX - posX);
		distanceYToPlayer = abs(playerY - posY);
		if (distanceXToPlayer >= 200 && distanceYToPlayer >= 150) {
			_state = ESkeletonState::Skeleton_Stoping;
			_hasJump = false;
			return;
		}
		


		break;

	default:
		break;

	}


	UpdateBones(dt);
}

void Skeletons::SetActive(float x, float y)
{
	//if (abs(posX - x) <= 200)
	//{
	//	if (abs(posY - y) <= 50)
	//	{
	//		//vX = -SPEED_X;
	//		sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Skeletons_ID), 1, 1, 60);
	//	}
	//	else
	//	{
	//		if (abs(posY - y) <= 150)
	//		{
	//			Jump();
	//		}
	//	}
	//}
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
	sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Skeletons_ID), 0,1, 60);
	sprite->SelectIndex(0);
}


void Skeletons::UpdateBones(int deltaTime_)
{
	list<DynamicObject*>::iterator it = _bones->begin();
	while (it != _bones->end())
	{
		if (!(*it)->active)
			_bones->erase(it++);
		else
		{
			(*it)->Update(deltaTime_);
			++it;
		}
	}

}

void Skeletons::DrawBones(GCamera* camera_)
{
	for (list<DynamicObject*>::iterator iter = _bones->begin(); iter != _bones->end(); iter++)
	{
		DynamicObject* tempSnake = (*iter);
		tempSnake->Draw(camera_);
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
Skeletons::~Skeletons(void)
{
}
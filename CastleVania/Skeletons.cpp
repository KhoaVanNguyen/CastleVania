
#include "Skeletons.h"


void Skeletons::_initialize()
{
	_playerPos = new D3DXVECTOR2(0, 0);
	_localTime = 0;
	_LittleSnake = new list<DynamicObject*>();
	_deltaPhi = 0;
	_posY0 = posY;
	active = true;
	type = ObjectType::None;
	hp = 100;
	damage = 4;
	canBeKilled = true;
	playerpos = new D3DXVECTOR2(0, 0);
}

void Skeletons::setDead()
{
	active = false;
}

void Skeletons::ReceiveDamage(int damagePoint)
{

	if (!IsHurt())
	{
		if (hp <= 0)
			return;
		hp -= damagePoint;
		if (hp == 0)
			death = true;
		bActiveHurt = true;
		_localHurtTime = GetTickCount();

		if (hp == 0)
			this->setDead();
	}
}

void Skeletons::_updateSnakes(int deltaTime_)
{
	/*list<DynamicObject*>::iterator it = _LittleSnake->begin();
	while (it != _LittleSnake->end())
	{
		if (!(*it)->active)
			_LittleSnake->erase(it++);
		else
		{
			(*it)->Update(deltaTime_);
			++it;
		}
	}*/

}

void Skeletons::_drawSnakes(GCamera* camera_)
{
	/*for (list<DynamicObject*>::iterator iter = _LittleSnake->begin(); iter != _LittleSnake->end(); iter++)
	{
		DynamicObject* tempSnake = (*iter);
		tempSnake->Draw(camera_);
	}*/
}

Skeletons::Skeletons(void)
{
	this->_initialize();
}

Skeletons::Skeletons(float posX_, float posY_,  EnumID id_) :DynamicObject(posX_, posY_, QUEEN_Skeletons_SPEED_X, 0, id_)
{
	_initialize();
	//prepare(posX_, posY_, huong);
	_sprite = new GSprite(Singleton::getInstance()->getTexture(id_), 4, 4, 1000 / SKELETONS_SPEED_X);
}

void Skeletons::prepare(D3DXVECTOR2* playerpos)
{
	float dentax = posX - playerpos->x;
	if (dentax > 0)
	{
		_anpha = SKELETONS_ANPHA;
		_posX0 = posX = posX + 20;
	}
	else
	{
		_anpha = 180 - SKELETONS_ANPHA;
		_posX0 = posX = posX - 20;
	}
	_anpha = _anpha*(3.14 / 180);
	_posY0 = posY = posY + 20;
}

void Skeletons::Update(int deltaTime_)
{
	

	this->sprite->Update(deltaTime_);
	vX = SKELETONS_SPEED_X*cos(_anpha);
	vY = SKELETONS_SPEED_X*sin(_anpha) - G*deltaTime_;
	posX += vX*deltaTime_;
	float deltaPosX = posX - _posX0;
	posY = _posY0 + vY*deltaPosX / vX - 0.5*G*pow((deltaPosX / vX), 2);
	//_updateSnakes(deltaTime_);
}
void Skeletons::Draw(GCamera* camera_)
{
	D3DXVECTOR2 center = camera_->Transform(posX, posY);
	_sprite->Draw(center.x, center.y);
	//this->_drawSnakes(camera_);
		
}

void Skeletons::Collision(list<GameObject*> obj, int dt)
{
	// xet va cham cua Snake voi gameObject
	for (list<DynamicObject*>::iterator iter = _LittleSnake->begin(); iter != _LittleSnake->end(); iter++)
	{
		DynamicObject* Snake = (*iter);
		Snake->Collision(obj, dt);
		
	}
}

void Skeletons::prepare(float posX, float posY, float huong)
{
	if (huong>0)
	{
		_anpha = SKELETONS_ANPHA;
		_posX0 = posX = posX + 20;
	}
	else
	{
		_anpha = 180 - SKELETONS_ANPHA;
		_posX0 = posX = posX - 20;
	}
	_anpha = _anpha*(3.14 / 180);
	_posY0 = posY = posY + 20;
}

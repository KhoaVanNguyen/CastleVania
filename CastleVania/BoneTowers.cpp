
#include "BoneTowers.h"


BoneTowers::BoneTowers(void) : DynamicObject()
{
}

BoneTowers::BoneTowers(float x, float y) : DynamicObject(x, y, 0, 0, EnumID::BoneTowers_ID)
{
	_listFire = new list<DynamicObject*>();
	type = ObjectType::Enemy_Type;
	point = 400;
	hp = 4;
	active = true;

	_timeSpan = 0;

}

void BoneTowers::Update(int dt)
{

	_timeSpan += dt;
	if (_timeSpan % 13 == 0)
	{
		_listFire->push_back(new Fire(posX, posY+10, EnumID::Fire_ID));
	}

	_upDateFire(dt);
	

}

void BoneTowers::Draw(GCamera* camera)
{
	
	D3DXVECTOR2 center = camera->Transform(posX, posY);
	sprite->Draw(center.x, center.y);
	this->_drawFire(camera);
	
}

BoneTowers::~BoneTowers(void)
{
	delete _listFire;
}


void BoneTowers::_upDateFire(float deltaTime_)
{
	list<DynamicObject*>::iterator it = _listFire->begin();
	while (it != _listFire->end())
	{
		if (!(*it)->active)
			_listFire->erase(it++);
		else
		{
			(*it)->Update(deltaTime_);
			++it;
		}
	}
}

void BoneTowers::_drawFire(GCamera* camera_)
{
	for (list<DynamicObject*>::iterator iter = _listFire->begin(); iter != _listFire->end(); iter++)
	{
		DynamicObject* fire = (*iter);
		fire->Draw(camera_);
	}
}

void BoneTowers::Collision(list<GameObject*> obj, int dt)
{
	// xet va cham cua Snake voi gameObject
	for (list<DynamicObject*>::iterator iter = _listFire->begin(); iter != _listFire->end(); iter++)
	{
		DynamicObject* Fire = (*iter);
		Fire->Collision(obj, dt);

	}
}

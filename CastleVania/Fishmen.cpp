#include "Fishmen.h"

#define SPEED_X 0.3f
#define SPEED_Y 0.45f
#define MAX_HEIGHT 250.0f

Fishmen::Fishmen(void) : DynamicObject()
{
}

Fishmen::Fishmen(float x, float y) : DynamicObject(x, y, 0, 0, EnumID::Fishmen_ID)
{
	_hasJump = false;
	_heightJump = 0;
	_listFire = new list<Fire*>();
	type = ObjectType::Enemy_Type;
	//point = 300;
}

void Fishmen::Update(int dt)
{
	list<Water*>::iterator it = w->begin();
	while (it != w->end())
	{
		if (!(*it)->active)
			w->erase(it++);
		else
		{
			(*it)->Update(dt);
			++it;
		}
	}
	list<Fire*>::iterator i = _listFire->begin();
	while (i != _listFire->end())
	{
		if (!(*i)->active)
		{
			_listFire->erase(i++);
			//_listFire->push_back(new Fire(posX, posY + 20, vX, EnumID::Fire_ID));
			_listFire->push_back(new Fire(posX, posY + 20, EnumID::Fire_ID));
		}
		else
		{
			(*i)->Update(dt);
			++i;
		}
	}
	if (!_hasJump)
		posX += vX*dt;
	posY += vY*dt;
	if (!_hasJump)
		sprite->Update(dt);
	if (_hasJump)
	{
		_heightJump += vY * dt;
		if (_heightJump >= MAX_HEIGHT)
		{
			vY = -(SPEED_Y + 0.3f);
		}
	}
}

void Fishmen::Collision(list<GameObject*> obj, int dt)
{
	
}

void Fishmen::Draw(GCamera* camera)
{
	for (list<Water*>::iterator i = w->begin(); i != w->end(); i++)
	{
		if ((*i)->active)
			(*i)->Draw(camera);
	}
	for (list<Fire*>::iterator i = _listFire->begin(); i != _listFire->end(); i++)
	{
		if ((*i)->active)
			(*i)->Draw(camera);
	}
	D3DXVECTOR2 center = camera->Transform(posX, posY);
	if (vX > 0)
		sprite->DrawFlipX(center.x, center.y);
	else
		sprite->Draw(center.x, center.y);

}

void Fishmen::SetActive(float x, float y)
{
	if (abs(posX - x) <= 50 && abs(posY - y) <= 200)
	{
		if (posX - x > 0)
			vX = -SPEED_X;
		else vX = SPEED_X;
		active = true;
		Jump();
	}
}

void Fishmen::Jump()
{
	vY = SPEED_Y;
	_hasJump = true;
	_heightJump = 0.0f;
	w = new list<Water*>();
	w->push_back(new Water(posX, posY, -0.01));
	w->push_back(new Water(posX, posY, -0.2));
	w->push_back(new Water(posX, posY, 0.2));
	
}

Fishmen::~Fishmen(void)
{
}

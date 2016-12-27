#include "Mummy.h"


Mummy::Mummy(void) : DynamicObject()
{
}



Mummy::~Mummy()
{
}

Mummy::Mummy(float posX_, float posY_) : DynamicObject(posX_, posY_, 1.0f, 1.0f, EnumID::Mummy_ID)
{
	_bandages = new list<DynamicObject*>();
	neededPlayerPosition = true;
	_localTime = 0;
	active = true;
	type = ObjectType::Enemy_Type;
	hp = 50;
	damage = 4;
	canBeKilled = true;
	_state = EMummyState::Mummy_moving;
	_isSleeping = true;
	_attackmode = true;
	//vX = vY = Mummy_STATE;
	deltaX = 0;
	oldX = posX;
	timeDelay = 50;
	_timeSpan = 0;
}



void Mummy::Draw(GCamera* camera)
{
	if (sprite == NULL || !active)
		return;
	/*if (posX + width / 2 <= camera->viewport.x || posX - width / 2 >= camera->viewport.x + G_ScreenWidth)
	{
	active = false;
	return;
	}*/
	D3DXVECTOR2 center = camera->Transform(posX, posY);
	if (_drawLeft)
		sprite->Draw(center.x, center.y);
	else
		sprite->DrawFlipX(center.x, center.y);

	_drawBandages(camera);
}



void Mummy::Update(int playerX, int playerY, int deltaTime)
{
	int randomDeltaX;



	
	_timeSpan+= deltaTime;
	if (_timeSpan % 25 == 0){
		_bandages->push_back(new Bandages(posX, posY, vX*0.24f, 0.0f, EnumID::Bandage_ID));


	}

	
	switch (_state)
	{
	case EMummyState::Mummy_Stoping:


		sprite->Update(deltaTime);
		_localTime += deltaTime;

		
		if (_localTime >= 700)
		{
			_localTime = 0;
			_state = EMummyState::Mummy_moving;
			return;
		}


		break;
	case EMummyState::Mummy_moving:


		deltaX += (abs(oldX - posX));
		oldX = posX;


		if (playerX > posX){
			_drawLeft = false;
			posX += vX*deltaTime;
		}
		else {
			posX -= vX*deltaTime;
			_drawLeft = true;
		}
		sprite->Update(deltaTime);

		 randomDeltaX = rand() % 120 + 20;
		if (deltaX >= 20)
		{
			deltaX = 0;
			this->_state = EMummyState::Mummy_Stoping;
			return;
		}


		break;
	default:
		break;

	}
	_updateBandages(deltaTime);

}

// neu va cham voi vien gach thi chuyen qua stage moving 
void Mummy::Collision(list<GameObject*> obj, int dt)
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
				//EMummyState::Stoping0;
			}
		}
	}
}




void Mummy::_updateBandages(int deltaTime_)
{
	list<DynamicObject*>::iterator it = _bandages->begin();
	while (it != _bandages->end())
	{
		if (!(*it)->active)
			_bandages->erase(it++);
		else
		{
			(*it)->Update(deltaTime_);
			++it;
		}
	}

}

void Mummy::_drawBandages(GCamera* camera_)
{
	for (list<DynamicObject*>::iterator iter = _bandages->begin(); iter != _bandages->end(); iter++)
	{
		DynamicObject* tempSnake = (*iter);
		tempSnake->Draw(camera_);
	}
}

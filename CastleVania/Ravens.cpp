#include "Ravens.h"


Ravens::Ravens(void) : DynamicObject()
{
}



Ravens::~Ravens()
{
}

Ravens::Ravens(float posX_, float posY_) :DynamicObject(posX_, posY_, 1.0f, 1.0f, EnumID::Ravens_ID)
{
	_localTime = 0;
	active = true;
	type = ObjectType::Enemy_Type;
	hp = 50;
	damage = 4;
	canBeKilled = true;
	_state = ERavenState::moving;
	_isSleeping = true;
	_attackmode = true;
	//vX = vY = RAVENS_STATE;
	deltaX = 0;
	oldX = posX;
	timeDelay = _timeDelay;
}

//void Ravens::Stoping(int deltaTime_)
//{
//	
//	switch (_state)
//	{
//	case Stoping0:
//	{
//		_localTime += deltaTime_;
//		sprite->Update(deltaTime_);
//		if (_localTime > 1000 / RAVENS_STOP_STATE)
//		{
//			_localTime = 0;
//			_state = ERavenState::Moving01;
//			break;
//		}
//	}
//		
//		break;
//		
//
//	case Stoping1:
//	{
//		sprite->Update(deltaTime_);
//		_localTime += deltaTime_;
//		if (_localTime > 1000 / RAVENS_STOP_STATE)
//		{
//			_localTime = 0;
//			_state = ERavenState::Moving12;
//			break;
//		}
//	}
//		
//		break;
//	case Stoping2:
//	{
//		sprite->Update(deltaTime_);
//		_localTime += deltaTime_;
//		if (_localTime > 1000 / RAVENS_STOP_STATE)
//		{
//			_localTime = 0;
//			_state = ERavenState::Moving23;
//			break;
//		}
//	}
//		
//		break;
//	default :
//		break;
//		
//
//	}
//}

//void Ravens::Moving(int deltaTime_)
//{
//	
//	switch (_state)
//	{
//	case Moving01:
//	{
//		posX += vX*deltaTime_;
//		posY = 2 * posX + 4;
//		//posX = 3650;
//		//posY = 96;
//		_localTime += deltaTime_;
//		if (_localTime > 500)
//		{
//			_localTime = 0;
//			_state = ERavenState::Stoping1;
//			break;
//		}
//	}
//	
//		break;
//		
//	case Moving12:
//	{
//		//posX = 3709;
//		//posY = 286;
//		posX += vX*deltaTime_;
//		posY = -posX + 4;
//		_localTime += deltaTime_;
//		if (_localTime >500)
//		{
//			_localTime = 0;
//			_state = ERavenState::Stoping2;
//			break;
//		}
//	}
//		
//		break;
//	
//	case Moving23:
//		////posX = 3992;
//		//posY = 222;
//		posX += vX*deltaTime_;
//
//		break;
//	}
//
//}


void Ravens::Stoping(int deltaTime_)
{
      sprite->Update(deltaTime_);
	_localTime += deltaTime_;
	if (_localTime >= 1000)
	{
		_localTime = 0;
		_state = ERavenState::moving;
		return;
	}
}

void Ravens::Moving(int deltaTime_)
{
	deltaX += (abs(oldX - posX));
	oldX = posX;
	posX += vX*deltaTime_;
	posY += vY*deltaTime_;
	sprite->Update(deltaTime_);
	if (deltaX >= 50)
	{
		this->_state = ERavenState::Stoping;
		return;
	}
	
	
}

void Ravens::Update(int deltaTime)
{
	switch (_state)
	{
	case ERavenState::Stoping:
		Stoping(deltaTime);
		break;
	case ERavenState::moving:
		Moving(deltaTime);
		break;
	default :
		break;

	}
		
	
}

// neu va cham voi vien gach thi chuyen qua stage moving 
void Ravens::Collision(list<GameObject*> obj, int dt)
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
				//ERavenState::Stoping0;
			}
		}
	}
}
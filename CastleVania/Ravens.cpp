#include "Ravens.h"


Ravens::Ravens(void) : DynamicObject()
{
}



Ravens::~Ravens()
{
}

Ravens::Ravens(float posX_, float posY_) :DynamicObject(posX_, posY_, 0.3f, 0.3f, EnumID::Ravens_ID)
{
	_localTime = 0;
	active = true;
	type = ObjectType::Enemy_Type;
	hp = 50;
	damage = 4;
	canBeKilled = true;
	_state = Stoping0;
}

void Ravens::Stoping(int deltaTime_)
{
	
	switch (_state)
	{
	case Stoping0:
		_localTime += deltaTime_;
		sprite->Update(deltaTime_);
		if (_localTime > 1000 / RAVENS_STOP_STATE)
		{
			_localTime = 0;
			_state= Moving01;
		}
		break;

	case Stoping1:
		sprite->Update(deltaTime_);
		_localTime += deltaTime_;
		if (_localTime > 1000 / RAVENS_STOP_STATE)
		{
			_localTime = 0;
			_state = Moving12;
		}
		break;
	case Stoping2:
		sprite->Update(deltaTime_);
		_localTime += deltaTime_;
		if (_localTime > 1000 / RAVENS_STOP_STATE)
		{
			_localTime = 0;
			_state = Moving23;
		}
		break;
	default :
		break;
		

	}
	/*if (ERavenState::Stoping0)
	{
		_localTime += deltaTime_;
		if (_localTime > 1000 / RAVENS_STOP_STATE)
		{
			_localTime = 0;
			ERavenState::Moving01;
		}
	}
	if (ERavenState::Stoping1)
	{
		_localTime += deltaTime_;
		if (_localTime > 1000 / RAVENS_STOP_STATE)
		{
			_localTime = 0;
			ERavenState::Moving12;
		}
	}

	if (ERavenState::Stoping2)
	{
		_localTime += deltaTime_;
		if (_localTime > 1000 / RAVENS_STOP_STATE)
		{
			_localTime = 0;
			ERavenState::Moving23;
		}
	}
*/
}

void Ravens::Moving(int deltaTime_)
{
	
	switch(_state)
	{
		case Moving01:
			posX += vX*deltaTime_;
			posY = -3 * posX + 4;
			_localTime += deltaTime_;
			if (_localTime > 1000 / RAVENS_STOP_STATE)
			{
				_localTime = 0;
				_state = Stoping1;
			}
			break;
		case Moving12:
			posX += vX*deltaTime_;
			posY = -3 * posX + 4;
			_localTime += deltaTime_;
			if (_localTime > 1000 / RAVENS_STOP_STATE)
			{
				_localTime = 0;
				_state = Stoping2;
			}
			
			break;
		case Moving23:
			posX += vX*deltaTime_;

			break;


		/*case Moving01:
			sprite->Update(deltaTime_);
			 _localTime += deltaTime_;
				posX += -vX*deltaTime_;
				posY = -3 * posX + 4;
				if (_localTime > 10)
				{
					_localTime = 0;
					_state = Stoping1;
					break;
				}
			
		case Moving12:
			sprite->Update(deltaTime_);
			_localTime += deltaTime_;
			posX += -vX*deltaTime_;
			posY = 3 * posX + 4;
			if (_localTime > 10)
			{
				_localTime = 0;
				_state = Stoping2;
				break;
			}
			
		case Moving23:
			sprite->Update(deltaTime_);
			posX += -vX*deltaTime_;
			break;*/


	//case Moving01:
	//	while (_localTime > 1000 )
	//	{
	//		posX += vX*deltaTime_;
	//		posY = -3 * posX + 4;

	//		_localTime += deltaTime_;
	//	}
	//	_localTime = 0;
	//	_state=Stoping1;
	//	break;
	//case Moving12:
	//	while (_localTime > 1000)
	//	{
	//		//
	//		//
	//		_localTime += deltaTime_;
	//	}
	//	_localTime = 0;
	//	_state=Stoping2;
	//	break;
	//case Moving23:
	//	posX += vX*deltaTime_;
	}
	//
	//if (ERavenState::Moving01)
	//{
	//	while (_localTime > 1000 / RAVENS_STATE)
	//	{
	//		//
	//		posX += vX*deltaTime_;
	//		posY = 3 * posX + 4;
	//		_localTime += deltaTime_;
	//	}
	//	_localTime = 0;
	//	ERavenState::Stoping1;
	//}

	//if (ERavenState::Moving12)
	//{
	//	while (_localTime > 1000 / RAVENS_STATE)
	//	{
	//		//
	//		//
	//		_localTime += deltaTime_;
	//	}
	//	_localTime = 0;
	//	ERavenState::Stoping2;
	//}


	//if (ERavenState::Moving23)
	//{
	//	posX += vX*deltaTime_;
	//	posY += vY*deltaTime_;
	//	
	//}

}

void Ravens::Update(int deltaTime_)
{
	switch (_state)
	{
	case Moving01:
	case Moving12:
	case Moving23:
		Moving(deltaTime_);
		break;
	case Stoping0:
	case Stoping1:
	case Stoping2:
		Stoping(deltaTime_);
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
				ERavenState::Stoping0;
			}
		}
	}
}
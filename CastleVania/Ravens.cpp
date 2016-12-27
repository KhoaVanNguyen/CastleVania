#include "Ravens.h"


Ravens::Ravens(void) : DynamicObject()
{
}



Ravens::~Ravens()
{
}

Ravens::Ravens(float posX_, float posY_) :DynamicObject(posX_, posY_, 1.0f, 1.0f, EnumID::Ravens_ID)
{
	neededPlayerPosition = true;
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

void Ravens::Draw(GCamera* camera)
{
	if (sprite == NULL || !active)
		return;
	/*if (posX + width / 2 <= camera->viewport.x || posX - width / 2 >= camera->viewport.x + G_ScreenWidth)
	{
		active = false;
		return;
	}*/
	D3DXVECTOR2 center = camera->Transform(posX, posY);
	if (_drawLeft )
		sprite->Draw(center.x, center.y);
	else
		sprite->DrawFlipX(center.x, center.y);
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

void Ravens::Update(int playerX, int playerY, int deltaTime)
{

	switch (_state)
	{
	case ERavenState::Stoping:
		

		sprite->Update(deltaTime);
		_localTime += deltaTime;
		if (_localTime >= 800)
		{
			_localTime = 0;
			_state = ERavenState::moving;
			return;
		}


		break;
	case ERavenState::moving:
		

		deltaX += (abs(oldX - posX));
		oldX = posX;
		
		if (posY <= playerY && posX > playerX) {
			posX -= vX*deltaTime;
			posY += vY*deltaTime;
			_drawLeft = true;
		}

		else if (posY <= playerY && posX < playerX){
			posX += vX*deltaTime;
			posY += vY*deltaTime;
			_drawLeft = false;
		}
		else if (posY >= playerY && posX > playerX){
			posX -= vX*deltaTime;
			posY -= vY*deltaTime;
			_drawLeft = true;
		}
		else if (posY >= playerY && posX < playerX) {
			posX += vX*deltaTime;
			posY -= vY*deltaTime;
			_drawLeft = false;
		}


		
		sprite->Update(deltaTime);
		if (deltaX >= 50)
		{
			deltaX = 0;
			this->_state = ERavenState::Stoping;
			return;
		}


		break;
	default:
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

#include "QueenMedusa.h"


void QueenMedusa::_initialize()
{
	_vStopPos = vector<D3DXVECTOR2*>();
	_vStopPos.push_back(new D3DXVECTOR2(posX - 172, 0));
	_vStopPos.push_back(new D3DXVECTOR2(posX - 70, 0));
	_vStopPos.push_back(new D3DXVECTOR2(posX, 0));
	_vStopPos.push_back(new D3DXVECTOR2(posX + 70, 0));
	_vStopPos.push_back(new D3DXVECTOR2(posX + 220, 0));
	_previousStopPos = 0;
	_currentStopPos = 0;
	_state = EQueenMedusaState::InActive;
	_playerPos = new D3DXVECTOR2(0, 0);
	_routerInfo = new D3DXVECTOR2(0, 0);
	_gold = new D3DXVECTOR2(0, 0);
	_localTime = 0;
	_vLittleSnake = new list<DynamicObject*>();
	_deltaPhi = 0;
	_posY0 = posY;
	active = true;
	type = ObjectType::None;
	_hasGetUp = false;
	
}


void QueenMedusa::_onStop(int deltaTime_)
{
	this->_fightSprite->Update(deltaTime_);
	_localTime += deltaTime_;
	if (_localTime > 1000 / QUEEN_MEDUSA_STOP_STATE)
	{
		_localTime = 0;
		switch (_currentStopPos)
		{
		case 0:
		{
			_previousStopPos = _currentStopPos;
			int modNumber = rand() % 20;
			if (modNumber % 2 == 0)
				_currentStopPos = 2;
			else
				_currentStopPos = 4;
			if (vX <0)
				vX = -vX;
		}
		break;
		case 1:
		{
			_previousStopPos = _currentStopPos;
			_currentStopPos = 0;
			float deltaX = posX - _playerPos->x; // deltaX between boss and player
			float littleSnakeVx = -deltaX / abs(deltaX)*LITTLE_SNAKE_SPEED_X;
			/*LittleSnake* littleSnake = new LittleSnake(posX,100,littleSnakeVx,0,EnumID::LittleSnake_ID);
			littleSnake->active = true;*/
			
		}
		break;

		case 2:
		{
			_previousStopPos = _currentStopPos;
			float deltaX = posX - _playerPos->x; // deltaX between boss and player
			if (deltaX>0)
			{
				_currentStopPos = 1;
				if (vX>0)
					vX = -vX;
			}
			else
			{
				_currentStopPos = 3;
				if (vX<0)
					vX = -vX;
			}
		}
		break;
		case 3:
		{
			_previousStopPos = _currentStopPos;
			_currentStopPos = 4;
			float deltaX = posX - _playerPos->x; // deltaX between boss and player
			float littleSnakeVx = -deltaX / abs(deltaX)*LITTLE_SNAKE_SPEED_X;
			/*LittleSnake* littleSnake = new LittleSnake(posX,100,littleSnakeVx,0,EnumID::LittleSnake_ID);
			littleSnake->active = true;*/
			
		}
		break;
		case 4:
		{
			_previousStopPos = _currentStopPos;
			int modNumber = rand() % 20;
			if (modNumber % 2 == 0)
				_currentStopPos = 0;
			else
				_currentStopPos = 2;
			if (vX >0)
				vX = -vX;
		}
		break;
		default:
			break;
		}

		_gold = _vStopPos.at(_currentStopPos);
		// changing state
		_state = EQueenMedusaState::Moving;

	}
}

void QueenMedusa::_onMoving(int deltaTime_)
{
	if (_isKiss(D3DXVECTOR2(posX, posY), *this->_gold))
	{
		this->_state = EQueenMedusaState::Stop;
		return;
	}
	posX += vX*deltaTime_;
	posY = _posY0 + A*cos(2 * PI*deltaTime_ / T + _deltaPhi);
	_deltaPhi += 2 * PI*deltaTime_ / T;

	_fightSprite->Update(deltaTime_);
}

void QueenMedusa::_onDead(int deltaTime_)
{
	_deadSprite->Update(deltaTime_);
	_localTime += deltaTime_;
	if (_localTime >= DEAD_TIME)
	{
		active = false;
		this->_state = EQueenMedusaState::Cancel;
	}
}

void QueenMedusa::_onInActive(int deltaTime_)
{
	_localTime += deltaTime_;
	if (_localTime>1000 / QUEEN_MEDUSA_INACTIVE_RATE)
	{
		this->setDead();
	}
}


bool QueenMedusa::_isKiss(D3DXVECTOR2 _boss, D3DXVECTOR2 gold_)
{
	float deltaX0 = _boss.x - gold_.x;
	if (deltaX0*vX>0)
		return true;
	return false;
}

void QueenMedusa::getUp()
{
	this->_state = EQueenMedusaState::Stop;
	if (!_hasGetUp)
	{
		
		type = ObjectType::Enemy_Type;
		_hasGetUp = true;
		G_MaxSize = G_MinSize + G_ScreenWidth;
	}
}

void QueenMedusa::setDead()
{
	_state = EQueenMedusaState::Dead;
}

void QueenMedusa::ReceiveDamage(int damagePoint)
{
}

bool QueenMedusa::GetState()
{
	if (this->_state == EQueenMedusaState::Cancel)
		return true;
	else return false;
}

void QueenMedusa::_updateSnakes(int deltaTime_)
{
	list<DynamicObject*>::iterator it = _vLittleSnake->begin();
	while (it != _vLittleSnake->end())
	{
		if (!(*it)->active)
			_vLittleSnake->erase(it++);
		else
		{
			(*it)->Update(deltaTime_);
			++it;
		}
	}

}

void QueenMedusa::_drawSnakes(GCamera* camera_)
{
	for (list<DynamicObject*>::iterator iter = _vLittleSnake->begin(); iter != _vLittleSnake->end(); iter++)
	{
		DynamicObject* tempSnake = (*iter);
		tempSnake->Draw(camera_);
	}
}

QueenMedusa::QueenMedusa(void)
{
	this->_initialize();
}

QueenMedusa::QueenMedusa(float posX_, float posY_, EnumID id_) :DynamicObject(posX_, posY_, QUEEN_MEDUSA_SPEED_X, 0, id_)
{
	_initialize();
	_sleepSprite = new GSprite(Singleton::getInstance()->getTexture(id_), 4, 4, 1000 / QUEEN_MEDUSA_SLEEP_STATE);
	_fightSprite = new GSprite(Singleton::getInstance()->getTexture(id_), 0, 3, 1000 / QUEEN_MEDUSA_STATE);
	
}



void QueenMedusa::Update(int deltaTime_)
{
	switch (_state)
	{
	case InActive:
		//this->_onInActive(deltaTime_);
		break;

	case Moving:
		_onMoving(deltaTime_);
		break;
	case Stop:
		_onStop(deltaTime_);
		break;
	case Dead:
		_onDead(deltaTime_);
	default:
		break;
	}
	_updateSnakes(deltaTime_);
}

void QueenMedusa::Update(int deltaTime_, D3DXVECTOR2* playerPos_)
{
	this->_playerPos = playerPos_;
	this->Update(deltaTime_);
}



void QueenMedusa::Draw(GCamera* camera_)
{
	D3DXVECTOR2 center = camera_->Transform(posX, posY);
	switch (_state)
	{
	case InActive:
		_sleepSprite->Draw(center.x, center.y);
		break;
	case Stop:case Moving:
		// draw the boss
		_fightSprite->Draw(center.x, center.y);
		// draw the snake
		this->_drawSnakes(camera_);
		break;
	case Dead:
		_deadSprite->Draw(center.x - 40, center.y);
		_deadSprite->Draw(center.x, center.y);
		_deadSprite->Draw(center.x + 40, center.y);

		_deadSprite->Draw(center.x - 40, center.y - 15);
		_deadSprite->Draw(center.x, center.y - 15);
		_deadSprite->Draw(center.x + 40, center.y - 15);
		break;
	case Cancel:
		break;
	default:
		break;
	}
}

void QueenMedusa::Collision(list<GameObject*> obj, int dt)
{
	for (list<DynamicObject*>::iterator iter = _vLittleSnake->begin(); iter != _vLittleSnake->end(); iter++)
	{
		DynamicObject* tempSnake = (*iter);
		
	}
}


QueenMedusa::~QueenMedusa(void)
{

}

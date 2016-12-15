
#include "Medusa.h"


void Medusa::_initialize()
{
	_vStopPos = vector<D3DXVECTOR2*>();
	_vStopPos.push_back(new D3DXVECTOR2(posX - 172, 0));
	_vStopPos.push_back(new D3DXVECTOR2(posX - 70, 0));
	_vStopPos.push_back(new D3DXVECTOR2(posX, 0));
	_vStopPos.push_back(new D3DXVECTOR2(posX + 70, 0));
	_vStopPos.push_back(new D3DXVECTOR2(posX + 220, 0));
	_previousStopPos = 0;
	_currentStopPos = 0;
	_state = EMedusaState::InActive;
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
	hp = 20;
	damage = 4;
	canBeKilled = true;
}


void Medusa::_onStop(int deltaTime_)
{
	this->_fightSprite->Update(deltaTime_);
	_localTime += deltaTime_;
	if (_localTime > 1000 / QUEEN_medusa_STOP_STATE)
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
			float deltaX = posX - _playerPos->x; // deltaX between boss and simon
			float littleSnakeVx = -deltaX / abs(deltaX)*LITTLE_SNAKE_SPEED_X;
			
			_vLittleSnake->push_back(new LittleSnake(posX, posY, littleSnakeVx, -0.2f, EnumID::LittleSnake_ID));
		}
		break;

		case 2:
		{
			_previousStopPos = _currentStopPos;
			float deltaX = posX - _playerPos->x; // deltaX between boss and simon
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
			float deltaX = posX - _playerPos->x; // deltaX between boss and simon
			float littleSnakeVx = -deltaX / abs(deltaX)*LITTLE_SNAKE_SPEED_X;
			
			_vLittleSnake->push_back(new LittleSnake(posX, posY, littleSnakeVx, -0.2f, EnumID::LittleSnake_ID));
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
		_state = EMedusaState::Moving;

	}
}

void Medusa::_onMoving(int deltaTime_)
{
	if (_isKiss(D3DXVECTOR2(posX, posY), *this->_gold))
	{
		this->_state = EMedusaState::Stop;
		return;
	}
	posX += vX*deltaTime_;
	posY = _posY0 + A*cos(2 * PI*deltaTime_ / T + _deltaPhi);
	_deltaPhi += 2 * PI*deltaTime_ / T;

	_fightSprite->Update(deltaTime_);
}

void Medusa::_onDead(int deltaTime_)
{
	_deadSprite->Update(deltaTime_);
	_localTime += deltaTime_;
	if (_localTime >= DEAD_TIME)
	{
		active = false;
		this->_state = EMedusaState::Cancel;
	}
}

void Medusa::_onInActive(int deltaTime_)
{
	_localTime += deltaTime_;
	if (_localTime>1000 / QUEEN_medusa_INACTIVE_RATE)
	{
		this->setDead();
	}
}


bool Medusa::_isKiss(D3DXVECTOR2 _boss, D3DXVECTOR2 gold_)
{
	float deltaX0 = _boss.x - gold_.x;
	if (deltaX0*vX>0)
		return true;
	return false;
}

void Medusa::getUp()
{
	this->_state = EMedusaState::Stop;
	if (!_hasGetUp)
	{
		//Sound::GetInst()->RemoveAllBGM();
		//Sound::GetInst()->PlayBGSound(EBGSound::EBoss);
		type = ObjectType::Enemy_Type;
		_hasGetUp = true;
		G_MaxSize = G_MinSize + G_ScreenWidth;
	}
}

void Medusa::setDead()
{
	_state = EMedusaState::Dead;
}

void Medusa::ReceiveDamage(int damagePoint)
{
	/*if (!IsHurt())
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
	}*/
}

bool Medusa::GetState()
{
	if (this->_state == EMedusaState::Cancel)
		return true;
	else return false;
}

void Medusa::_updateSnakes(int deltaTime_)
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

void Medusa::_drawSnakes(GCamera* camera_)
{
	for (list<DynamicObject*>::iterator iter = _vLittleSnake->begin(); iter != _vLittleSnake->end(); iter++)
	{
		DynamicObject* tempSnake = (*iter);
		tempSnake->Draw(camera_);
	}
}

Medusa::Medusa(void)
{
	this->_initialize();
}

Medusa::Medusa(float posX_, float posY_, EnumID id_) :DynamicObject(posX_, posY_, QUEEN_medusa_SPEED_X, 0, id_)
{
	_initialize();
	_sleepSprite = new GSprite(Singleton::getInstance()->getTexture(id_), 4, 4, 1000 / QUEEN_medusa_SLEEP_STATE);
	_fightSprite = new GSprite(Singleton::getInstance()->getTexture(id_), 0, 3, 1000 / QUEEN_medusa_STATE);
	//_deadSprite = new GSprite(Singleton::getInstance()->getTexture(EnumID::Fire_ID), 0, 2, 1000 / QUEEN_medusa_DIE_RATE);
}



void Medusa::Update(int deltaTime_)
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

void Medusa::Update(int t, D3DXVECTOR2* playerpos)
{
	this->_playerPos = playerpos;
	this->Update(t);
}



void Medusa::Draw(GCamera* camera_)
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

void Medusa::Collision(list<GameObject*> obj, int dt)
{
	for (list<DynamicObject*>::iterator iter = _vLittleSnake->begin(); iter != _vLittleSnake->end(); iter++)
	{
		DynamicObject* tempSnake = (*iter);
		tempSnake->Collision(obj, dt);
		
	}
}


Medusa::~Medusa(void)
{

}

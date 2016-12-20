
#include "Medusa.h"


void Medusa::_initialize()
{
	//luu  4 vi tri Stop cua Player
	_listStopPos = vector<D3DXVECTOR2*>();
	_listStopPos.push_back(new D3DXVECTOR2(posX - 165, 0));
	_listStopPos.push_back(new D3DXVECTOR2(posX - 80, 0));
	_listStopPos.push_back(new D3DXVECTOR2(posX, 0));
	_listStopPos.push_back(new D3DXVECTOR2(posX + 90, 0));
	_listStopPos.push_back(new D3DXVECTOR2(posX + 210, 0));
	_previousStopPos = 0;
	_currentStopPos = 0;
	_state = EMedusaState::Sleeping;
	_playerPos = new D3DXVECTOR2(0, 0);
	
	_nextStopPos = new D3DXVECTOR2(0, 0); //luu tao do Stop cua Player
	_localTime = 0;
	_LittleSnake = new list<DynamicObject*>();
	_deltaPhi = 0;
	_posY0 = posY;
	active = true;
	type = ObjectType::None;
	HasGetUp = false;
	hp = 100;
	damage = 4;
	canBeKilled = true;
}


void Medusa::_Stoping(int deltaTime_)
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
			int random = rand() % 4;
			if (random % 2 == 0)
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
			float deltaX = posX - _playerPos->x; // tinh do chenh lech tao do cua Player va boss de lay chieu Vx Snake
			float littleSnakeVx = -deltaX / abs(deltaX)*LITTLE_SNAKE_SPEED_X; // Tinh Vx cua Snake
			_LittleSnake->push_back(new LittleSnake(posX, posY, littleSnakeVx, -0.2f, EnumID::LittleSnake_ID));
		}
		break;

		case 2:
		{
			_previousStopPos = _currentStopPos;
			float deltaX = posX - _playerPos->x; 
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
			float deltaX = posX - _playerPos->x; 
			float littleSnakeVx = -deltaX / abs(deltaX)*LITTLE_SNAKE_SPEED_X;
			
			_LittleSnake->push_back(new LittleSnake(posX, posY, littleSnakeVx, -0.2f, EnumID::LittleSnake_ID));
		}
		break;
		case 4:
		{
			_previousStopPos = _currentStopPos;
			int random = rand() % 4;
			if (random % 2 == 0)
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

		_nextStopPos = _listStopPos.at(_currentStopPos);
		_state = EMedusaState::Moving;

	}
}

void Medusa::_Moving(int deltaTime_)
{
	if (_leaveStopPos(D3DXVECTOR2(posX, posY), *this->_nextStopPos))
	{
		this->_state = EMedusaState::Stop;
		return;
	}
	posX += vX*deltaTime_;
	posY = _posY0 + A*cos(2 * PI*deltaTime_ / T + _deltaPhi); // Phuong trinh chuyen dong duong hinh sin x = 2pi. t/ lamda
	_deltaPhi += 2 * PI*deltaTime_ / T;
	_fightSprite->Update(deltaTime_);
}

void Medusa::_Deading(int deltaTime_)
{
	_deadSprite->Update(deltaTime_);
	_localTime += deltaTime_;
	if (_localTime >= DEAD_TIME)
	{
		active = false;
		this->_state = EMedusaState::Cancel;
	}
}


// Kiem tra boss co roi khoi NextStopPos  khong hay la di gan lai
bool Medusa::_leaveStopPos(D3DXVECTOR2 _boss, D3DXVECTOR2 _nextStopPos)
{
	float deltaX0 = _boss.x - _nextStopPos.x;
	if (deltaX0*vX>0)
		return true;
	return false;
}

void Medusa::getUp()
{
	this->_state = EMedusaState::Stop;
	if (!HasGetUp)
	{
		//Sound::GetInst()->RemoveAllBGM();
		//Sound::GetInst()->PlayBGSound(EBGSound::EBoss);
		type = ObjectType::Enemy_Type;
		HasGetUp = true;
		G_MaxSize = G_MinSize + G_ScreenWidth;
	}
}

void Medusa::setDead()
{
	_state = EMedusaState::Dead;
}

void Medusa::ReceiveDamage(int damagePoint)
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

bool Medusa::StateCancel()
{
	if (this->_state == EMedusaState::Cancel)
		return true;
	else return false;
}

void Medusa::_updateSnakes(int deltaTime_)
{
	list<DynamicObject*>::iterator it = _LittleSnake->begin();
	while (it != _LittleSnake->end())
	{
		if (!(*it)->active)
			_LittleSnake->erase(it++);
		else
		{
			(*it)->Update(deltaTime_);
			++it;
		}
	}

}

void Medusa::_drawSnakes(GCamera* camera_)
{
	for (list<DynamicObject*>::iterator iter = _LittleSnake->begin(); iter != _LittleSnake->end(); iter++)
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
	_deadSprite = new GSprite(Singleton::getInstance()->getTexture(EnumID::FireBossDie_ID), 0, 2, 1000 / QUEEN_medusa_DIE_RATE);
}



void Medusa::Update(int deltaTime_)
{
	switch (_state)
	{
	case Sleeping:
		break;
	case Moving:
		_Moving(deltaTime_);
		break;
	case Stop:
		_Stoping(deltaTime_);
		break;
	case Dead:
		_Deading(deltaTime_);
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
	case Sleeping:
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
	// xet va cham cua Snake voi gameObject
	for (list<DynamicObject*>::iterator iter = _LittleSnake->begin(); iter != _LittleSnake->end(); iter++)
	{
		DynamicObject* tempSnake = (*iter);
		tempSnake->Collision(obj, dt);
		
	}
}


Medusa::~Medusa(void)
{

}

#include "PhantomBat.h"

void PhantomBat::_initialize()
{
	_vSleepPos = vector<D3DXVECTOR2*>();
	_vSleepPos.push_back(new D3DXVECTOR2(posX - 208, posY));
	_vSleepPos.push_back(new D3DXVECTOR2(posX - 208, posY - 100));
	_vSleepPos.push_back(new D3DXVECTOR2(posX - 100, posY));
	_vSleepPos.push_back(new D3DXVECTOR2(posX - 100, posY - 100));
	_vSleepPos.push_back(new D3DXVECTOR2(posX, posY));
	_vSleepPos.push_back(new D3DXVECTOR2(posX, posY - 100));
	_vSleepPos.push_back(new D3DXVECTOR2(posX + 100, posY));
	_vSleepPos.push_back(new D3DXVECTOR2(posX + 100, posY - 100));
	_vSleepPos.push_back(new D3DXVECTOR2(posX + 221, posY));
	_vSleepPos.push_back(new D3DXVECTOR2(posX + 221, posY - 100));
	_currentSleepPos = 0;
	_eRouterType = ERouterType::Parabol;
	//posX  = _vSleepPos.at(_currentSleepPos)->x;
	//posY  = _vSleepPos.at(_currentSleepPos)->y;
	_phantomBatState = 0;
	_simonPos = new D3DXVECTOR2(0, 0);
	_routerInfo = new D3DXVECTOR2(0, 0);
	_gold = new D3DXVECTOR2(0, 0);
	_localTime = 0;
	active = true;
	//_hasGetUp = false;
	type = ObjectType::None;
	
}

void PhantomBat::_onGold(int deltaTime_)
{
	// 1. calc next gold & next state
	// if current state is on rest => next state is fly to simon

	if (this->_phantomBatState == 4)
	{
		_localTime += deltaTime_;
		if (_localTime >= 1000 / PHANTOM_BAT_REST_RATE)
		{
			_localTime = 0;
			(*_gold) = D3DXVECTOR2(this->_simonPos->x, this->_simonPos->y + 45);
			//update sleep pos
			this->_updateSleepPos();
			this->_phantomBatState = 1; // fly to simon
		}
		else
		{
			return;
		}

	}
	// if current state is on fight simon => next state is fly to sleep
	else
	{
		*_gold = *this->_vSleepPos.at(_currentSleepPos);
		this->_phantomBatState = 3; // fly to sleep
	}

	//2. calc the road & the velocity
	float deltaX = this->_gold->x - this->posX;
	float deltaY = this->_gold->y - this->posY;
	if (abs(deltaX)<2)
	{
		//calc router type
		_eRouterType = ERouterType::Vertical;
		this->_routerInfo->x = 1;
		this->_routerInfo->y = 1;
	}
	else
	{
		// calc router type
		{
			_eRouterType = ERouterType::Parabol;
			this->_routerInfo->x = (float)(_gold->y - this->posY) / (pow(_gold->x, 2) - pow(this->posX, 2));
			this->_routerInfo->y = this->posY - this->_routerInfo->x*pow(this->posX, 2);
		}

	}

	// calc velocity
	if (abs(deltaX)<2)
	{
		vX = 0;
	}
	else
	{
		vX = (deltaX / 150)*SPEED_X;
	}

	if (deltaY == 0)
	{
		vY = 0;
	}
	else if (deltaY>0)
	{
		vY = SPEED_X;
	}
	else
	{
		vY = -SPEED_X;
	}
}

void PhantomBat::_onDead(int deltaTime_)
{

	_localTime += deltaTime_;
	if (_localTime >= DEAD_TIME)
	{
		active = false;
		this->_phantomBatState = -2;
	}
}



void PhantomBat::getUp()
{
}

void PhantomBat::ReceiveDamage(int damagePoint)
{
	
}

void PhantomBat::setDead()
{
	this->_phantomBatState = -1;
	this->_localTime = 0;// reset to timing the dead animation time
}

bool PhantomBat::GetState()
{
	if (_phantomBatState == -2)
		return true;
	else return false;
}

void PhantomBat::_onSleep(int deltaTime_)
{
	if (_simonPos->x - posX >= 100)
		this->getUp();
}

void PhantomBat::_onFly(int deltaTime_)
{
	// if it gone to the gold/sleep pos then change the state to on gold/sleep pos
	if (_isKiss(new D3DXVECTOR2(posX, posY), this->_gold))
	{
		switch (this->_phantomBatState)
		{
		case 1:
			this->_phantomBatState = 2;
			return;
		case 3:
			this->_phantomBatState = 4;
			return;
		default:
			return;
		}

	}
	//else
	// update to animate
	
	// update position
	switch (_eRouterType)
	{
	case Parabol:
		posX += vX*deltaTime_;
		posY = _routerInfo->x*pow(posX, 2) + _routerInfo->y;
		break;
	case Line:
		posX += vX*deltaTime_;
		posY = _routerInfo->x*posX + _routerInfo->y;
		break;
	case Vertical:
		posX += vX*deltaTime_;
		posY += vY*deltaTime_;
	default:
		break;
	}
}


void PhantomBat::_updateSleepPos()
{
	_currentSleepPos = (_currentSleepPos + 1) % _vSleepPos.size();
}

bool PhantomBat::_isKiss(D3DXVECTOR2* phantomBat_, D3DXVECTOR2* gold_)
{
	switch (_eRouterType)
	{
	case Parabol:
	{
		float deltaX0 = phantomBat_->x - gold_->x;
		if (deltaX0*vX>0)
			return true;
	}
	break;
	case Line:
	{
		float deltaX0 = phantomBat_->x - gold_->x;
		float deltaY0 = phantomBat_->y - gold_->y;
		if (deltaX0*vX>0 && deltaY0*vY>0)
			return true;
	}
	break;
	case Horizontal:
	{
		float deltaX0 = phantomBat_->x - gold_->x;
		if (deltaX0*vX>0)
			return true;
	}
	break;
	case Vertical:
	{
		float deltaY0 = phantomBat_->y - gold_->y;
		if (deltaY0*vY>0)
			return true;
	}
	break;
	default:
		break;
	}
	return false;
}

PhantomBat::PhantomBat(void)
{
}

PhantomBat::PhantomBat(float posX_, float posY_, EnumID id_) :DynamicObject(posX_, posY_, SPEED_X, 0, id_)
{
	_initialize();
	
}

void PhantomBat::Update(int deltaTime_)
{
	//_phantomBatState
	//0: sleep
	//1: on fly to SIMON
	//2: in the simon
	//3: on fly to rest place;
	//4: on rest place
	switch (_phantomBatState)
	{
		// on sleep
	case 0:
		this->_onSleep(deltaTime_);
		break;
		// on Fly
	case 1:case 3:
		this->_onFly(deltaTime_);
		break;
		//on rest or simon
	case 2: case 4:
		this->_onGold(deltaTime_);
		break;
	case -1:
		this->_onDead(deltaTime_);
		break;
	default:
		break;
	}
}

void PhantomBat::Update(int deltaTime_, D3DXVECTOR2* simonPos_)
{
	this->_simonPos = simonPos_;
	this->Update(deltaTime_);
}

void PhantomBat::Draw(GCamera* camera_)
{
}

void PhantomBat::Collision(list<GameObject*> list, int dt)
{
}

PhantomBat::~PhantomBat(void)
{
}

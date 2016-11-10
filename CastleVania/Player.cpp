#include "Player.h"

#define Player_FIGHT_RATE 20
#define Player_RATE 10
#define HURT_STATE 25

#define SPEED_X 0.3f
#define SPEED_Y 0.4f
//#define SPEED_X 0.01f
//#define SPEED_Y 0.01f

#define MAX_HEIGHT 70.0f
#define A 0.005f

#define MAX_HEIGHT_KNOCKBACK 32.0f
#define MAX_WIDTH_KNOCKBACK 40.0f

Player::Player(void) : DynamicObject()
{
}

Player::Player(int _posX, int _posY) : DynamicObject(_posX, _posY, 0, -SPEED_Y, EnumID::Player_ID)
{
	_action = Action::Idle;
	_allowPress = true;
	_vLast = 0.2f;
	_hasJump = false;
	_hasSit = false;
	_heightJump = 0.0f;
	_heightJump = 0.0f;
	playerJump = new GSprite(Singleton::getInstance()->getTexture(EnumID::Player_ID), 4, 4, 300);
	Initialize();
}

void Player::Update(int deltaTime)
{
	//return;
	switch (_action)
	{
	case Action::Run_Left:
		sprite->Update(deltaTime);
		break;
	case Action::Run_Right:
		sprite->Update(deltaTime);
		break;
	}
}

void Player::Draw(GCamera* camera)
{
	//---------Ve Player------------
	D3DXVECTOR2 center = camera->Transform(posX, posY);
	if (_PlayerDeath)
	{
		_PlayerDeathSprite->DrawFlipX(center.x, center.y);
	}
	else
	{
		if (IsHurt())
		{
		}
		else
		{
			for (list<Weapon*>::iterator i = _weapon->begin(); i != _weapon->end(); i++)
			{
				if ((*i)->active)
					(*i)->Draw(camera);
			}
			if (_hasKnockBack)
			{
				if (_vLast > 0)
				{
					_PlayerKnockBack->Draw(center.x, center.y);
					return;
				}
				else if (_vLast < 0)
				{
					_PlayerKnockBack->DrawFlipX(center.x, center.y);
					return;
				}
			}
			else
			{
				if (vX > 0 || _vLast>0)
				{
					if (_action == Action::Fight)
					{
						if (!_usingWeapon)
							_morningStar->Draw(camera);
						if (_onStair)
						{
							if (_kindStair == EKindStair::DownLeft || _kindStair == EKindStair::DownRight)
								_PlayerFightingDownStairSprite->DrawFlipX(center.x, center.y);
							else
							{
								_PlayerFightingUpStairSprite->DrawFlipX(center.x, center.y);
							}
						}
						else
							if (!_hasSit)
								_PlayerFightingSprite->DrawFlipX(center.x, center.y);
							else
							{
								_PlayerFightingSittingSprite->DrawFlipX(center.x, center.y);
							}
						return;
					}
					if (_action == Action::IntoCastle)
					{
						sprite->Draw(center.x, center.y);
						return;
					}
					if ((_hasJump && vY > (-0.5f)/*&& _heightJump >= MAX_HEIGHT / 2*/) || _hasSit)
					{
						PlayerJump->DrawFlipX(center.x, center.y);
						return;
					}
					if (_onStair)
					{
						if (_kindStair == EKindStair::UpRight || _kindStair == EKindStair::DownRight)
							_PlayerStair->DrawFlipX(center.x, center.y);
						return;
					}
					sprite->DrawFlipX(center.x, center.y);
				}
				else
				{
					if (_action == Action::Fight)
					{
						if (!_usingWeapon)
							_morningStar->Draw(camera);
						if (_onStair)
						{
							if (_kindStair == EKindStair::DownLeft || _kindStair == EKindStair::DownRight)
								_PlayerFightingDownStairSprite->Draw(center.x, center.y);
							else
							{
								_PlayerFightingUpStairSprite->Draw(center.x, center.y);
							}
						}
						else
							if (!_hasSit)
								_PlayerFightingSprite->Draw(center.x, center.y);
							else
							{
								_PlayerFightingSittingSprite->Draw(center.x, center.y);
							}
						return;
					}
					if (_action == Action::IntoCastle)
					{
						sprite->Draw(center.x, center.y);
						return;
					}
					if ((_hasJump && vY >= (-0.5f)/*&& _heightJump >= MAX_HEIGHT / 2*/) || _hasSit)
					{
						PlayerJump->Draw(center.x, center.y);
						return;
					}
					if (_onStair)
					{
						if (_kindStair == EKindStair::DownLeft || _kindStair == EKindStair::UpLeft)
							_PlayerStair->Draw(center.x, center.y);
						return;
					}
					sprite->Draw(center.x, center.y);
				}
			}
		}
	}
}

void Player::TurnLeft()
{
	if (_allowPress)
	{
		if (_action == Action::Fall)
			return;
		if (_action == Action::Fight)
			return;
		if (_hasJump || _hasSit)
			return;
		vX = -SPEED_X;
		_vLast = vX;
		_hasSit = false;
		_action = Action::Run_Left;
	}
}

void Player::TurnRight()
{
	if (_allowPress)
	{
		if (_usingWeapon)
			_usingWeapon = false;
		if (_action == Action::Fall)
			return;
		if (_action == Action::Fight)
			return;
		if (_hasJump || _hasSit)
			return;
		if (_hasStair)
			return;
		if (_colCastleGate)
			return;
		ResetStair();
		vX = SPEED_X;
		_vLast = vX;
		_hasSit = false;
		_action = Action::Run_Right;

	}
}

void Player::Jump()
{
	if (_allowPress)
	{
		if (_action == Action::Fall)
			return;
		if (_action == Action::Fight)
			return;
		if (_hasSit)
			return;
		if (_onStair)
			return;
		if (_hasStair)
			return;
		if (_colCastleGate)
			return;
		if (!_hasJump)
		{
			_a = -A;
			vY = sqrt(-2 * _a*MAX_HEIGHT);//SPEED_Y;
			_heightJump = 0;
			sprite->SelectIndex(0);
			_action = Action::Jump;
			_hasJump = true;
		}
	}
}

void Player::KnockBack()
{
	if (_colCastleGate)
		return;
	if (!_hasKnockBack)
	{
		_allowPress = false;
		_a = -A;
		if (vX > 0 || _vLast > 0)
			vX = -(sqrt(-2 * _a * MAX_WIDTH_KNOCKBACK));
		else if (vX < 0 || _vLast < 0)
			vX = (sqrt(-2 * _a * MAX_WIDTH_KNOCKBACK));
		vY = sqrt(-2 * _a * MAX_HEIGHT_KNOCKBACK);
		_heightJump = 0;
		_hasJump = false;
		_hasKnockBack = true;
	}

}

void Player::Fall()
{
	_action = Action::Fall;
	vX = 0;
	vY = -(SPEED_Y + 0.4f);
}

void Player::Sit()
{
	if (_allowPress)
	{
		if (_action == Action::Fall)
			return;
		if (_action == Action::Fight)
			return;
		if (_hasSit)
			return;
		if (_hasStair)
			return;
		if (_onStair)
			return;
		if (_colCastleGate)
			return;
		if (!_hasJump)
		{
			vX = 0;
			vY = -(SPEED_Y + 0.3f);
			_hasSit = true;
			_action = Action::Sit;
		}
	}
}

void Player::Initialize()
{
	bActiveHurt = false;
	_localHurtTime = 0;
	_bHurt = false;
	_a = 0;
}

bool Player::IsHurt()
{
	if (!bActiveHurt)
		return false;
	bool result = _bHurt;
	DWORD now = GetTickCount();
	DWORD deltaTime = now - _localHurtTime;
	if (deltaTime >= 1500)
	{
		bActiveHurt = false;
	}
	if (deltaTime % (int)(1000 / HURT_STATE) < 15)
	{
		_bHurt = !_bHurt;
	}
	return result;
}

void Player::UpStair()
{
	if (!_downStair)
	{
		_upStair = true;
		if (_onStair)
		{
			if (_kindStair == EKindStair::DownLeft)
			{
				vX = _vLast = -1;
				_kindStair = EKindStair::UpRight;
			}
			if (_kindStair == EKindStair::DownRight)
			{
				vX = _vLast = 1;
				_kindStair = EKindStair::UpLeft;
			}
		}
	}
	if (_hasJump)
		return;
	if (_action == Action::Fight)
		return;
	if (_hasStair)
		return;
	if (abs(rangeStair) < 40)
	{
		if (_colStair && (_stair->id == EnumID::StairUpLeft_ID || _stair->id == EnumID::StairUpRight_ID))
		{
			if (!_hasStair)
				_hasStair = true;
			else
			{
				_onStair = true;
				_timeSpawn = 0;
			}
			if (rangeStair != 0)
			{
				_onStair = false;
			}
			else
			{
				_onStair = true;
				if (_kindStair == EKindStair::DownLeft)
				{
					vX = _vLast = -1;
					_kindStair = EKindStair::UpRight;
				}
				if (_kindStair == EKindStair::DownRight)
				{
					vX = _vLast = 1;
					_kindStair = EKindStair::UpLeft;
				}
				_PlayerStair->SelectIndex(13);
				_timeSpawn = 0;

			}
		}
	}

}



void Player::OutStair()
{
	if (_upStair || _downStair)
	{
		_upStair = false;
		_downStair = false;
		_hasStair = false;
		_onStair = false;
		vY = -SPEED_Y;
		vX = 0;
		sprite->SelectIndex(0);
		switch (_stair->id)
		{
		case EnumID::StairDownLeft_ID:
			_kindStair = EKindStair::DownLeft;
			break;
		case EnumID::StairDownRight_ID:
			_kindStair = EKindStair::DownRight;
			break;
		case EnumID::StairUpLeft_ID:
			_kindStair = EKindStair::UpLeft;
			break;
		case EnumID::StairUpRight_ID:
			_kindStair = EKindStair::UpRight;
			break;
		default:
			break;
		}
	}
}

bool Player::OnStair()
{
	if ((_colStair && (_stair->id == EnumID::StairDownLeft_ID || _stair->id == EnumID::StairDownRight_ID)) || _onStair)
		return true;
	return false;
}

void Player::ResetStair()
{
	if (_upStair || _downStair)
		_upStair = _downStair = false;
	//_kindStair = EKindStair::None;
	_colStair = false;
}

void Player::OnGateCastle()
{
	if (_colCastleGate)
	{
		ResetStair();
		_hasJump = false;
		_hasSit = false;
		_hasWeapon = false;

	}
}

void Player::Stop()
{
	if (_usingWeapon)
		_usingWeapon = false;
	if (_stopOnStair && _timeSpawn == 0)
	{
		_upStair = false;
		_downStair = false;
		_stopOnStair = false;
		return;
	}
	switch (_action)
	{
	case Action::Idle:
	case Action::Fight:
	case Action::Fall:
		return;
	}
	if (_hasSit)
	{
		_hasSit = false;
		posY += 16;
	}
	if (_action == Action::IntoCastle)
	{
		vX = 0;
		return;
	}
	if (!_hasJump && !_movingByMovingPlatform) vX = 0;
	_action = Action::Idle;
	sprite->SelectIndex(0);
}

void Player::UseWeapon()
{
	if (_weaponID != EnumID::None_ID)
	{
		if (!_usingWeapon)
		{
			_usingWeapon = true;
		}
	}
}


void Player::ChangeWeapon(EnumID idWeapon)
{
	_weaponID = idWeapon;
}

void Player::Fight()
{
	if (_allowPress)
	{
		if (_action == Action::Fight)
			return;
		if (_onStair && (_upStair || _downStair))
			return;
		if (!_hasJump) vX = 0;
		if (_usingWeapon && !_hasWeapon && hearts > 0)
		{
			_hasWeapon = true;
			hearts -= 1;
		}
		SoundManager::GetInst()->PlaySoundEffect(ESoundEffect::ES_UsingMorningStar);
		_action = Action::Fight;
	}
}

void Player::UpgradeMorningStar()
{
	_morningStar->updateLevel();
}

void Player::OnFight(int t)
{
	if (_hasSit)
		_PlayerFightingSittingSprite->Update(t);
	else
		if (_onStair)
		{
			if (_kindStair == EKindStair::DownLeft || _kindStair == EKindStair::DownRight)
				_PlayerFightingDownStairSprite->Update(t);
			else _PlayerFightingUpStairSprite->Update(t);
		}
		else
			_PlayerFightingSprite->Update(t);

	if (_usingWeapon && _hasWeapon)
	{
		if (_PlayerFightingSittingSprite->GetIndex() == 17
			|| _PlayerFightingSprite->GetIndex() == 7
			|| _PlayerFightingDownStairSprite->GetIndex() >= 21
			|| _PlayerFightingUpStairSprite->GetIndex() >= 24)
		{
			this->SetWeapon();
		}
	}
	//else
	{
		// Update the moringStar index
		_morningStar->Update(t);

		// Update the Vx of morningStar
		float morningStarVx = -1;
		if (vX > 0 || _vLast > 0)
			morningStarVx = -morningStarVx;
		_morningStar->updateVx(morningStarVx);


		// Update the pos of morningStar
		_morningStar->updateXY(posX, posY);///////==============================================>> fishing

	}
	if (_onStair)
	{
		if ((_kindStair == EKindStair::DownLeft || _kindStair == EKindStair::DownRight)
			&& _PlayerFightingDownStairSprite->GetIndex() >= 21)
		{
			_action = Action::Idle;
			_PlayerFightingDownStairSprite->Reset();
			_morningStar->reset();
		}
		else if (_PlayerFightingUpStairSprite->GetIndex() >= 24)
		{
			_action = Action::Idle;
			_PlayerFightingUpStairSprite->Reset();
			_morningStar->reset();
		}
	}
	else
		if (!_hasSit && _PlayerFightingSprite->GetIndex() >= 8)
		{
			_action = Action::Idle;
			_PlayerFightingSprite->Reset();
			_morningStar->reset();
		}
		else
			if (_hasSit && _PlayerFightingSittingSprite->GetIndex() >= 18)
			{
				_action = Action::Sit;
				_PlayerFightingSittingSprite->Reset();
				_morningStar->reset();
			}
}

Player::~Player(void)
{
}

D3DXVECTOR2* Player::getPos()
{
	return new D3DXVECTOR2(this->posX, this->posY);
}

void Player::SetDirectDoor(EDirectDoor _direct)
{
	_directDoor = _direct;
	_colDoor = false;
}

EDirectDoor Player::GetDirectDoor()
{
	if (_colDoor)
	{
		switch (_door->id)
		{
		case DoorDown_ID:
			_directDoor = EDirectDoor::DoorDown;
			break;
		case DoorUp_ID:
			_directDoor = EDirectDoor::DoorUp;
			break;
		case DoorLeft_ID:
			_directDoor = EDirectDoor::DoorLeft;
			break;
		case DoorRight_ID:
			_directDoor = EDirectDoor::DoorRight;
			break;
		default:
			break;
		}
	}
	_colDoor = false;
	return _directDoor;
}

bool Player::AutoMove(int &range, int dt)
{
	if (range == 0)
		return true;
	if (range > 0)
	{
		range -= 4;
		posX += 4;
	}
	else
	{
		range += 4;
		posX -= 4;
	}
	sprite->Update(dt);
	return false;
}

void Player::PlayerDeath(int &_timeCount)
{
	if (_PlayerDeath)
	{
		_allowPress = false;
		_timeCount -= 1;
		_PlayerDeathSprite->SelectIndex(0);
		if (_timeCount == 0)
		{
			//_PlayerDeath = false;
			_allowPress = true;
			_isReset = true;
		}
	}
}

int Player::GetHPPlayer()
{
	return hp;
}

bool Player::GetUsingCross()
{
	return _usingCross;
}

void Player::SetUsingCross(bool value)
{
	if (!value)
	{
		_usingCross = false;
	}
	else if (!_usingCross)
	{
		_usingCross = true;
		SoundManager::GetInst()->PlaySoundEffect(ESoundEffect::ES_HolyCross);
	}
}

bool Player::GetUsingWatch()
{
	return _usingWatch;
}

void Player::SetUsingWatch(bool value)
{
	_usingWatch = value;
}
#include "Player.h"

#define PLAYER_FIGHT_RATE 20
#define Player_RATE 10
#define HURT_STATE 25

#define SPEED_X 0.3f
#define SPEED_Y 0.4f
#define MAX_HEIGHT 70.0f
#define A 0.005f
Player::Player(void) : DynamicObject()
{
}

Player::Player(int _posX, int _posY) : DynamicObject(_posX, _posY, 0, -SPEED_Y, EnumID::Player_ID)
{
	_action = Action::Idle;
	_a = 0.005f;
	_allowPress = true;
	_hasSit = false;
	_hasJump = false;
	_hasStair = false;
	_upStair = false;
	_downStair = false;

	playerJump = new GSprite(Singleton::getInstance()->getTexture(EnumID::Player_ID), 4, 4, 300);

	fightingSprite = new GSprite(Singleton::getInstance()->getTexture(EnumID::Player_ID), 5, 8, 1000 / PLAYER_FIGHT_RATE);
	fightingSittingSprite = new GSprite(Singleton::getInstance()->getTexture(EnumID::Player_ID), 15, 18, 1000 / PLAYER_FIGHT_RATE);
	playerStair = new GSprite(Singleton::getInstance()->getTexture(EnumID::Player_ID), 10, 13, 320);
	morningStar = new MorningStar(_posX, _posY, 0, 0, EnumID::MorningStar_ID, 1000 / PLAYER_FIGHT_RATE);
	Initialize();
}

void Player::Update(int deltaTime)
{
	switch (_action)
	{
	case Action::Run_Left:
		sprite->Update(deltaTime);
		break;
	case Action::Run_Right:
		sprite->Update(deltaTime);
		break;
	case Action::Fight:
		this->OnFight(deltaTime);
		break;
		/*case Action::Idle:
		sprite->SelectIndex(0);
		break;*/
	}
	if (_hasStair)
	{
		UpdatePlayerStair(deltaTime);
	}
	posX += vX * deltaTime;
#pragma region Xu ly nhay
	if (_hasJump)
	{
		sprite->SelectIndex(4);
		posY += vY * deltaTime + 0.4 * deltaTime * deltaTime * _a;
		if (vY > -0.6f)
			vY += _a * deltaTime;
		if (posY < 64)//xét va chạm thì thay tại đây
		{
			posY = 64;// xét va chạm thì thay tại đây
			sprite->SelectIndex(0); // khi rơi xuống, posY sẽ <0, nên pải đưa về selectIndex = 0 
			_a = 0; // khi chạm đất rồi, a =0;
			_hasJump = false;// chạm đất r thì không còn nhảy
		}
		return;
	}
#pragma endregion

	//posY += vY *deltaTime;
}
void Player::Draw(GCamera* camera)
{
	D3DXVECTOR2 center = camera->Transform(posX, posY);
	// đi sang phải
	if (vX > 0 || _vLast > 0)
	{
		if (_action == Action::Fight) {
			if (!_hasSit) {
				fightingSprite->DrawFlipX(center.x, center.y);
				morningStar->Draw(camera);
			}
			else {
				fightingSittingSprite->DrawFlipX(center.x, center.y);
			}
			// vẽ Fight rồi return luôn
			return;
		}
		sprite->DrawFlipX(center.x, center.y);
	}
	// đi sang trái
	else
	{
		if (_action == Action::Fight) {
			if (!_hasSit) {
				fightingSprite->Draw(center.x, center.y);
				morningStar->Draw(camera);
			}
			else {
				fightingSittingSprite->Draw(center.x, center.y);
			}
			return;
		}
		sprite->Draw(center.x, center.y);
	}


}
void Player::UpdatePlayerStair(int t)
{
	if (_onStair)
	{
		if (_upStair)
		{
			if (_kindStair == EKindStair::UpRight)
			{
				_vLast = vX = 1;
				_timeSpawn += 1;
				if (_timeSpawn <= 10)
				{

					posX += 1.6;
					posY += 1.6;
					if (_timeSpawn > 1 && _timeSpawn < 7)
						playerStair->SelectIndex(13);
					else
					{
						playerStair->SelectIndex(12);
					}
					if (_timeSpawn == 10)
					{
						_stopOnStair = true;
						_timeSpawn = 0;
						return;
					}
				}
			}
			else if (_kindStair == EKindStair::UpLeft)
			{
				_vLast = vX = -1;
				_timeSpawn += 1;
				if (_timeSpawn <= 10)
				{

					posX -= 1.6;
					posY += 1.6;
					if (_timeSpawn > 1 && _timeSpawn < 7)
						playerStair->SelectIndex(13);
					else
					{
						playerStair->SelectIndex(12);
					}
					if (_timeSpawn == 10)
					{
						_stopOnStair = true;
						_timeSpawn = 0;
						return;
					}
				}
			}
		}
		else if (_downStair)
		{
			if (_kindStair == EKindStair::DownLeft)
			{
				_vLast = vX = -1;
				_timeSpawn += 1;
				if (_timeSpawn <= 10)
				{
					posX -= 1.6;
					posY -= 1.6;
					if (_timeSpawn > 1 && _timeSpawn < 7)
						playerStair->SelectIndex(11);
					else
					{
						playerStair->SelectIndex(10);
					}
					if (_timeSpawn == 10)
					{
						_stopOnStair = true;
						_timeSpawn = 0;
						return;
					}
				}
			}
			else if (_kindStair == EKindStair::DownRight)
			{
				_vLast = vX = 1;
				_timeSpawn += 1;
				if (_timeSpawn <= 10)
				{
					posX += 1.6;
					posY -= 1.6;
					if (_timeSpawn > 1 && _timeSpawn < 7)
						playerStair->SelectIndex(11);
					else
					{
						playerStair->SelectIndex(10);
					}
					if (_timeSpawn == 10)
					{
						_stopOnStair = true;
						_timeSpawn = 0;
						return;
					}
				}
			}
		}
	}
	else
	{
		if (_hasStair)
		{
			if (rangeStair < 0)
			{
				_vLast = vX = 1;
				posX += 1;
				rangeStair += 1;
			}
			else if (rangeStair > 0)
			{
				_vLast = vX = -1;
				posX -= 1;
				rangeStair -= 1;
			}
			if (rangeStair == 0)
			{
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


				//------------------Thay van toc
				if (_kindStair == EKindStair::UpRight || _kindStair == EKindStair::DownRight)
				{
					vX = _vLast = 1;
				}
				else if (_kindStair == EKindStair::UpLeft || _kindStair == EKindStair::DownLeft)
				{
					vX = _vLast = -1;
				}

				_onStair = true;
				_timeSpawn = 0;
				if (_kindStair == EKindStair::UpRight || _kindStair == EKindStair::UpLeft)
				{
					posY += 2;
					playerStair->SelectIndex(12);
				}
				else if (_kindStair == EKindStair::DownLeft)
				{
					posY -= 16;
					playerStair->SelectIndex(10);
				}
				else if (_kindStair == EKindStair::DownRight)
				{
					posY -= 16;
					playerStair->SelectIndex(10);
				}
			}
			sprite->Update(t);
		}
		else if (_outStair)
		{
			sprite->SelectIndex(0);
			_kindStair = EKindStair::None_Kind;
			_action = Action::Idle;
		}
	}
}
void Player::TurnLeft()
{
	if (_allowPress)
	{
		if (_hasJump)
			return;
		if (_hasSit)
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
		if (_hasJump)
			return;
		if (_hasSit)
			return;
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
		if (_hasSit)
			return;
		if (!_hasJump)
		{
			vY = -10;
			posY += 30;
			_a = -A;
			vY = sqrt(-2 * _a*MAX_HEIGHT);
			//_heightJump = 0;
			sprite->SelectIndex(4);
			_action = Action::Jump;
			_hasJump = true;
		}
	}
}
void Player::Fall()
{
}

void Player::Sit()
{
	if (_allowPress && !_hasSit && !_hasJump)
	{
		if (_action == Action::Fight)
			return;
		sprite->SelectIndex(4);
		vX = 0;
		posY -= 18;
		_hasSit = true;
		_action = Action::Sit;
	}
}
void Player::Fight() {
	if (_allowPress)
	{
		if (_action == Action::Fight)
			return;
		if (!_hasJump)
			vX = 0;

		_action = Action::Fight;
	}
}
void Player::OnFight(int t)
{
	if (_hasSit) {
		fightingSittingSprite->Update(t);
	}
	else {
		fightingSprite->Update(t);
	}

	morningStar->Update(t);

	// Update the Vx of morningStar
	float morningStarVx = -1;
	if (vX > 0 || _vLast > 0)
		morningStarVx = -morningStarVx;
	morningStar->updateVx(morningStarVx);

	morningStar->updateXY(posX, posY);
	if (!_hasSit && fightingSprite->GetIndex() >= 8)
	{
		_action = Action::Idle;
		fightingSprite->Reset();
		morningStar->reset();
	}

	else if (_hasSit && fightingSittingSprite->GetIndex() >= 18)
	{
		_action = Action::Sit;
		fightingSittingSprite->Reset();
		morningStar->reset();
	}
}

void Player::Stop() {
	/*if (_hasJump == true)
	{
	}
	else
	{
	_action = Action::Idle;
	vX = 0;
	}*/
	// Xử lý tạm thôi
	vX = 0;
	switch (_action)
	{
	case Action::Idle:
	case Action::Fight:
	case Action::Fall:
		return;
	}
	if (_hasSit)
	{
		posY = 64;// va chạm thay tại đây.
		_hasSit = false;
	}
	if ((_hasJump == true && posY == 64))
	{
		_hasJump = false;
		sprite->SelectIndex(0);
		_a = 0;
	}
	_action = Action::Idle;
	sprite->SelectIndex(0);
}
void Player::UpStair()
{

}
bool Player::OnStair()
{
	if ((_colStair && (_stair->id == EnumID::StairDownLeft_ID || _stair->id == EnumID::StairDownRight_ID)) || _onStair)
		return true;
	return false;
}
Player::~Player(void)
{
}
D3DXVECTOR2* Player::getPos()
{
	return new D3DXVECTOR2(this->posX, this->posY);
}
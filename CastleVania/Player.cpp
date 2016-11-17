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
	switch (_action)
	{
	case Action::Run_Left:
		sprite->Update(deltaTime);
		posX += vX * deltaTime;
		_action = Action::Idle;
		vX = 0;
		break;
	case Action::Run_Right:
		sprite->Update(deltaTime);
		posX += vX * deltaTime;
		_action = Action::Idle;
		vX = 0;
		break;
	case Action::Idle:
		sprite->SelectIndex(0);
		break;
	case Action::Sit:
		sprite->Update(deltaTime);
		posX += vX * deltaTime;
		posY += vY *deltaTime/3;
		vX = 0;
		_action = Action::Idle;
		break;
	}
}
void Player::Draw(GCamera* camera)
{
	//---------Ve Player------------
	D3DXVECTOR2 center = camera->Transform(posX, posY);
	if (vX > 0 || _vLast > 0)
	{
		if ((_hasJump && vY > (-0.5f)) || _hasSit)
		{
			playerJump->DrawFlipX(center.x, center.y);
			return;
		}

		sprite->DrawFlipX(center.x, center.y);
	}
	else
	{

		if ((_hasJump && vY >= (-0.5f)/*&& _heightJump >= MAX_HEIGHT / 2*/) || _hasSit)
		{
			playerJump->Draw(center.x, center.y);
			return;
		}

		sprite->Draw(center.x, center.y);
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

		if (_action == Action::Fall)
			return;
		if (_action == Action::Fight)
			return;
		if (_hasJump || _hasSit)
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
		if (_action == Action::Fall)
			return;
		if (_action == Action::Fight)
			return;
		if (_hasSit)
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
void Player::Fall()
{
	_action = Action::Fall;
	vX = 0;
	vY = -(SPEED_Y + 0.4f);
}

void Player::Sit()
{
	if (_allowPress && !_hasSit)
	{
		vX = 0;
		vY = -(SPEED_Y + 0.3f);
		_hasSit = true;
		_action = Action::Sit;
	}
}

void Player::Initialize()
{
	_a = 0;
}

void Player::Stop(){

}
Player::~Player(void)
{
}

D3DXVECTOR2* Player::getPos()
{
	return new D3DXVECTOR2(this->posX, this->posY);
}







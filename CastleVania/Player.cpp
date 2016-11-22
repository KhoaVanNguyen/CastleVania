#include "Player.h"

#define Player_FIGHT_RATE 20
#define Player_RATE 10
#define HURT_STATE 25

#define SPEED_X 0.3f
#define SPEED_Y 0.4f
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
	_hasSit = false;
	playerJump = new GSprite(Singleton::getInstance()->getTexture(EnumID::Player_ID), 4, 4, 300);
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
	case Action::Idle:
		sprite->SelectIndex(0);
		break;
	//case Action::Sit:
	//	sprite->Update(deltaTime);
	//	break;
	}
	posX += vX * deltaTime;
}
void Player::Draw(GCamera* camera)
{
	//---------Ve Player------------
	D3DXVECTOR2 center = camera->Transform(posX, posY);
	if (vX > 0 || _vLast > 0)
	{
		sprite->DrawFlipX(center.x, center.y);
	}
	else
	{
		sprite->Draw(center.x, center.y);
	}
}

void Player::TurnLeft()
{
	if (_allowPress)
	{
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
		vX = SPEED_X;
		_vLast = vX;
		_hasSit = false;
		_action = Action::Run_Right;
	}
}
void Player::Jump()
{
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
		sprite->SelectIndex(4);
		vX = 0;
		posY -= 20;
//		vY = -(SPEED_Y + 0.3f);
		_hasSit = true;
		_action = Action::Sit;
	}
}

void Player::Stop() {
	_action = Action::Idle;
	vX = 0;
	if (_hasSit == true)
	{
		posY += 20;
		_hasSit = false;
	}

}
Player::~Player(void)
{
}

D3DXVECTOR2* Player::getPos()
{
	return new D3DXVECTOR2(this->posX, this->posY);
}







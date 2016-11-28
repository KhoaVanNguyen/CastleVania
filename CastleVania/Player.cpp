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

Player::Player(int _posX, int _posY) : DynamicObject
(_posX, _posY, 0, -SPEED_Y, EnumID::Player_ID)
{
	_action = Action::Idle;
	_a = 0.005f;
	_direction = 0.1;// hướng nhìn nhân vật qua phải (nếu >0), nhìn qua trái (nếu <=0)
	_allowPress = true;
	_hasSit = false;
<<<<<<< HEAD
	_hasJump = false;
	playerJump = new GSprite(Singleton::getInstance()->getTexture
	(EnumID::Player_ID), 4, 4, 300);
=======
	_hasJump = false; 

	playerJump = new GSprite(Singleton::getInstance()->getTexture(EnumID::Player_ID), 4, 4, 300);

	fightingSprite = new GSprite(Singleton::getInstance()->getTexture(EnumID::Player_ID), 5, 8, 1000 / PLAYER_FIGHT_RATE);
	fightingSittingSprite = new GSprite(Singleton::getInstance()->getTexture(EnumID::Player_ID), 15, 18, 1000 / PLAYER_FIGHT_RATE);
	
	morningStar = new MorningStar(_posX, _posY, 0, 0, EnumID::MorningStar_ID, 1000 / PLAYER_FIGHT_RATE);
	Initialize();
>>>>>>> origin/AddFight
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
	posX += vX * deltaTime;
#pragma region Xu ly nhay
	if (_hasJump)
	{
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
<<<<<<< HEAD
	if (vX > 0 || _direction > 0)
	{
		sprite->DrawFlipX(center.x, center.y);// vẽ hình nhìn về phía phải
=======
	// đi sang phải
	if (vX > 0 || _vLast > 0)
	{
		if (_action == Action::Fight){
			if (!_hasSit){
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
>>>>>>> origin/AddFight
	}
	// đi sang trái
	else
	{
		if (_action == Action::Fight){
			if (!_hasSit){
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

void Player::TurnLeft()
{
	if (_allowPress)
	{
		if (_hasJump)
			return;
		if (_hasSit)
			return;
		vX = -SPEED_X;
		_direction = vX;
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
		_direction = vX;
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
			posY += 30;
			_a = -A;
			vY = sqrt(-2 * _a*MAX_HEIGHT);
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
	if (_allowPress && !_hasSit&& !_hasJump) // nếu mà chưa ngồi,
									//và chưa nhảy thì được ngồi
	{
<<<<<<< HEAD
		sprite->SelectIndex(4);//khi ngồi thì vẽ hình số 4
		vX = 0;// vận tốc = 0.
		posY -= 18;//vị trí bị giảm xuống 18 cho đẹp, ngồi sát đất
		_hasSit = true;// xác nhận là đã ngồi
		_action = Action::Sit;// đưa hành động về Sit
	}
}
void Player::Stop() // hàm đưa về vị trí đâu (selec index = 0)
					//stop dc gọi khi k ấn nút
{
	if (_hasJump == true)	
=======
		if (_action == Action::Fight)
			return;
		sprite->SelectIndex(4);
		vX = 0;
		posY -= 18;
		_hasSit = true;
		_action = Action::Sit;
	}
}
void Player::Fight(){
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
	if (_hasSit){
		fightingSittingSprite->Update(t);
	}
	else{
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
>>>>>>> origin/AddFight
	{
		// đang nhảy thì tiếp tục giữ nguyên, đợi khi về vị trí ban đầu,
		//code ở dưới sẽ trả về false.
	}
	else // các trường hợp còn lại (hông di chuyển) là đưa về vị trí ban đầu
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
<<<<<<< HEAD

	if (_hasSit == true)
=======
	if (_hasSit)
>>>>>>> origin/AddFight
	{
		// nếu nhân vật hết ngồi
		posY = 64;// va chạm thay tại đây.
		//đưa về vị trí cũ, vì khi ngồi hình bị đổi posision
		_hasSit = false;
		//đưa về là không ngồi
	}
	if ((_hasJump == true && posY == 64))
		//nếu mà nhân vật đã chạm đất (khi nhảy xong).
	{
		//đưa về vị trí đầu
		_hasJump = false;
		_action = Action::Idle;
		vX = 0;
		_a = 0;
	}
<<<<<<< HEAD
=======
	_action = Action::Idle;
	sprite->SelectIndex(0);

>>>>>>> origin/AddFight
}

Player::~Player(void)
{
}
D3DXVECTOR2* Player::getPos()
{
	return new D3DXVECTOR2(this->posX, this->posY);
}







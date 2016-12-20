#include "Player.h"

#define PLAYER_FIGHT_RATE 20
#define Player_RATE 10
#define HURT_STATE 25

#define SPEED_X 0.3f
#define SPEED_Y 0.4f
#define MAX_HEIGHT 140.0f
#define A 0.005f
Player::Player(void) : DynamicObject()
{
}

Player::Player(int _posX, int _posY) : DynamicObject(_posX, _posY, 0, -SPEED_Y, EnumID::Player_ID)
{
	hp = 10;
	_isHurted = false;
	_action = Action::Idle;
	_a = 0.005f;
	_allowPress = true;
	_hasSit = false;
	_hasJump = false;
	_hasMagicalBall = false;
	//_onLand = false;
	_colBottomStair = false;
	_hasKnockBack = false;

	//Door
	_colDoor = false;
	_directDoor = EDirectDoor::NoneDoor;

	_colStair = false;

	_upStair = false;
	_downStair = false;
	_stopOnStair = false;
	_outStair = false;
	hearts = 1000;
	_weaponID = EnumID::Dagger_ID;
	_weapons = new list<Weapon*>();
	playerJump = new GSprite(Singleton::getInstance()->getTexture(EnumID::Player_ID), 4, 4, 300);

	fightingSprite = new GSprite(Singleton::getInstance()->getTexture(EnumID::Player_ID), 5, 8, 1000 / PLAYER_FIGHT_RATE);
	fightingSittingSprite = new GSprite(Singleton::getInstance()->getTexture(EnumID::Player_ID), 15, 18, 1000 / PLAYER_FIGHT_RATE);
	playerStair = new GSprite(Singleton::getInstance()->getTexture(EnumID::Player_ID), 10, 13, 320);
	morningStar = new MorningStar(_posX, _posY, 0, 0, EnumID::MorningStar_ID, 1000 / PLAYER_FIGHT_RATE);
	playerKnockBack = new GSprite(Singleton::getInstance()->getTexture(EnumID::Player_ID), 8, 8, 100);
	Initialize();
}


void Player::Update(int deltaTime)
{

	list<Weapon*>::iterator it = _weapons->begin();
	while (it != _weapons->end())
	{
		if (!(*it)->active)
			_weapons->erase(it++);
		else
		{
			(*it)->Update(deltaTime);
			++it;
		}
	}

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


	if (_colBottomStair)
	{
		UpdatePlayerStair(deltaTime);
	}
	else {
		posX += vX * deltaTime;

#pragma region Xu ly nhay
		if (_hasJump)
		{
			sprite->SelectIndex(4);
			posY += vY * deltaTime + 0.4 * deltaTime * deltaTime * _a;
			if (vY > -0.6f)
				vY += _a * deltaTime;
			//if (posY < 64)//xét va chạm thì thay tại đây
			//{
			//	posY = 64;// xét va chạm thì thay tại đây
			//	sprite->SelectIndex(0); // khi rơi xuống, posY sẽ <0, nên pải đưa về selectIndex = 0 
			//	_a = 0; // khi chạm đất rồi, a =0;
			//	_hasJump = false;// chạm đất r thì không còn nhảy
			//}
			return;
		}
#pragma endregion
#pragma region - xử lý bị knock_back
		if (_hasKnockBack)
		{
			posY += vY * deltaTime + 0.5 * deltaTime * deltaTime * _a;
			if (_vLast > 0)
			{
				posX += vX * deltaTime + 0.5 * deltaTime * deltaTime * (_a);
				if (vX < 0)
					vX += (-_a) * deltaTime;
				else vX = 0;
			}
			else if (_vLast < 0)
			{
				posX += vX * deltaTime + 0.5 * deltaTime * deltaTime * (_a);
				if (vX > 0)
					vX += (_a)* deltaTime;
				else vX = 0;
			}
			if (vY > -0.6f)
				vY += _a * deltaTime;
			return;
		}
#pragma endregion
		posY += vY *deltaTime;
	}
}
void Player::Draw(GCamera* camera)
{
	D3DXVECTOR2 center = camera->Transform(posX, posY);


	for (list<Weapon*>::iterator i = _weapons->begin(); i != _weapons->end(); i++)
	{
		if ((*i)->active)
			(*i)->Draw(camera);
	}
#pragma region Ve khi has KnockBack
	if (_hasKnockBack)
	{
		if (_vLast > 0)
		{
			playerKnockBack->Draw(center.x, center.y);
			return;
		}
		else if (_vLast < 0)
		{
			playerKnockBack->DrawFlipX(center.x, center.y);
			return;
		}
	}

#pragma endregion 
	// đi sang phải
	if (vX > 0 || _vLast > 0)
	{

		if (_onStair) {
			if (_kindStair == EKindStair::UpRight) {
				playerStair->DrawFlipX(center.x, center.y);
			}
			//?
				return;
		}

		if (_action == Action::Fight) {
			if (!_usingWeapon)
				morningStar->Draw(camera);
			if (!_hasSit) {
				fightingSprite->DrawFlipX(center.x, center.y);

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
			if (!_usingWeapon)
				morningStar->Draw(camera);
			if (!_hasSit) {
				fightingSprite->Draw(center.x, center.y);

			}
			else {
				fightingSittingSprite->Draw(center.x, center.y);

			}
			//morningStar->Draw(camera);
			return;
		}
		if (_onStair)
		{
			if (_kindStair == EKindStair::DownLeft || _kindStair == EKindStair::UpLeft)
				playerStair->Draw(center.x, center.y);
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
		if (_colBottomStair)
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
			_colStair = false;//mới thêm
			_kindStair = EKindStair::None_Kind;
			_action = Action::Idle;
		}
	}
}
void Player::TurnLeft()
{
	if (_allowPress)
	{
		if (_usingWeapon)
			_usingWeapon = false;
		if (_hasJump)
			return;
		if (_hasSit)
			return;
		ResetStair();
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
		if (_hasJump)
			return;
		if (_hasSit)
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
		if (_hasSit)
			return;
		if (!_hasJump)
		{
			//vY = -10;
			//posY += 30;
			_a = -A;
			vY = sqrt(-2 * _a*MAX_HEIGHT);
			//_heightJump = 0;
			sprite->SelectIndex(4);
			_action = Action::Jump;
			_hasJump = true;
			
		}
	}
	ResetStair();
}
void Player::Fall()
{
	_action = Action::Fall;
	vX = 0;
	vY = -(SPEED_Y + 0.3f);
}
void Player::Sit()
{
	if (_allowPress)
	{
		if (_action == Action::Fight)
			return;
		if (_hasSit) {
			return;
		}
		if (!_hasJump) {
			posY -= 16;
			sprite->SelectIndex(4);
			vX = 0;
			vY = -(SPEED_Y + 0.3f);
			_hasSit = true;
			_colStair = false;
			_action = Action::Sit;
		}
	}
}
void Player::Fight() {
	if (_allowPress)
	{
		if (_action == Action::Fight)
			return;
		if (!_hasJump)
			vX = 0;


		if (_usingWeapon && !_hasWeapon && hearts > 0)
		{
			_hasWeapon = true;
			hearts -= 1;
		}
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


	if (_usingWeapon && _hasWeapon)
	{

		this->SetWeapon();
	}
	else {
		morningStar->Update(t);

		// Update the Vx of morningStar
		float morningStarVx = -1;
		if (vX > 0 || _vLast > 0)
			morningStarVx = -morningStarVx;
		morningStar->updateVx(morningStarVx);

		morningStar->updateXY(posX, posY);
	}
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
	if (_usingWeapon)
		_usingWeapon = false;

	if (_stopOnStair && _timeSpawn == 0)
	{
		_upStair = false;
		_downStair = false;
		_stopOnStair = false;
		return;
	}
	vX = 0;
	if (_usingWeapon)
		_usingWeapon = false;
	switch (_action)
	{
	case Action::Idle:
	case Action::Fight:
	case Action::Fall:
		return;
	}
	if (_hasSit)
	{
		posY += 16;
		_hasSit = false;
	}
	//if ((_hasJump == true && posY == 64))// fix lỗi ở đây nếu qua bên game khác
	//{
	//	_hasJump = false;
	//	sprite->SelectIndex(0);
	//	_a = 0;
	//}
	_action = Action::Idle;
	sprite->SelectIndex(0);
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
	if (_colBottomStair)
		return;
	if (abs(rangeStair) <= 40)
	{
		if (_colStair && (_stair->id == EnumID::StairUpLeft_ID || _stair->id == EnumID::StairUpRight_ID))
		{
			if (!_colBottomStair)
				_colBottomStair = true;
			else
			{
				_onStair = true;
				_timeSpawn = 0;
			}
			if (rangeStair != 0)
			{
				_onStair = false;
				//_colStair = false;
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
				playerStair->SelectIndex(13);
				_timeSpawn = 0;
			}
		}
	}
	else
	{
		_colStair = false;
	}
}
void Player::DownStair()
{
	if (!_upStair)
	{
		_downStair = true;
		if (_onStair)
		{
			if (_kindStair == EKindStair::UpRight)
			{
				_kindStair = EKindStair::DownLeft;
				vX = _vLast = -1;
			}
			if (_kindStair == EKindStair::UpLeft)
			{
				vX = _vLast = 1;
				_kindStair = EKindStair::DownRight;
			}
		}
	}
	if (_hasJump)
		return;
	if (_action == Action::Fight)
		return;
	if (_colBottomStair)
		return;
	if (abs(rangeStair) < 40)
	{
		if (_colStair && (_stair->id == EnumID::StairDownLeft_ID || _stair->id == EnumID::StairDownRight_ID))
		{
			if (!_colBottomStair) _colBottomStair = true;
			else
			{
				_onStair = true;
				_timeSpawn = 0;
			}
			if (rangeStair != 0)
			{
				_onStair = false;
				//_colStair = false;

			}
			else
			{
				if (_kindStair == EKindStair::UpRight)
				{
					_kindStair = EKindStair::DownLeft;
					vX = _vLast = -1;
				}
				if (_kindStair == EKindStair::UpLeft)
				{
					vX = _vLast = 1;
					_kindStair = EKindStair::DownRight;
				}
				_onStair = true;
				playerStair->SelectIndex(11);
				_timeSpawn = 0;
			}
		}
	}
	else
	{
		_colStair = false;
	}
}
void Player::OutStair()
{
	if (_upStair || _downStair)
	{
		_upStair = false;
		_downStair = false;
		_colBottomStair = false;
		_onStair = false;
		_colStair = false;
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
//	_action = Action::Idle;
 }
Player::~Player(void)
{
}
D3DXVECTOR2* Player::getPos()
{
	return new D3DXVECTOR2(this->posX, this->posY);
}
void Player::UpgradeMorningStar() {

}
Box Player::GetBox()
{
	if ((_hasJump && _heightJump >= MAX_HEIGHT / 2) || _hasSit)
	{
		return Box(posX - width / 2 + 14.5f, posY + height / 2 - 3, width - 29, height - 22);
	}
	return Box(posX - width / 2 + 14.5f, posY + height / 2 - 3, width - 29, height - 6);
}
void Player::Collision(list<GameObject*> &obj, float dt) {
	if (_action == Action::Fight)
	{
		morningStar->Collision(obj, dt);
		point += morningStar->point;
		morningStar->point = 0;
	}

	for (list<GameObject*>::iterator _itBegin = obj.begin(); _itBegin != obj.end(); _itBegin++)
	{
		GameObject* other = (*_itBegin);
		float moveX = 0;
		float moveY = 0;
		float normalx;
		float normaly;

		Box boxPlayer = this->GetBox();
		Box boxOther = other->GetBox();

		//
		if (other->active)
		{
			if (AABB(boxPlayer, boxOther, moveX, moveY) == true) {
				// moveY ,  moveX
#pragma region Va chạm với item
				if (other->type == ObjectType::Item && other->id != EnumID::FireBossDie_ID) {
					other->Remove(); // deactive here!
					switch (other->id)
					{

					case EnumID::Whip_Upgrade: // not yet
						this->UpgradeMorningStar();
						break;
					case EnumID::Small_Heart:
					case EnumID::Large_Heart:
						hearts += other->hearts;
						break;
					case EnumID::Red_Money_Bag:
					case EnumID::Purple_Money_Bag:
					case EnumID::White_Money_Bag:
						//cong tien
						point += other->point;
						break;
					case EnumID::MagicalBall_ID:
						//Qua man
						_hasMagicalBall = true;
						//SoundManager::GetInst()->RemoveAllBGM();
						//SoundManager::GetInst()->PlaySoundEffect(ESoundEffect::ES_StageClear);
						break;
					}
				}
#pragma endregion 

				else {
					switch (other->id)
					{
#pragma region - va chạm với gạch
					case EnumID::Brick_ID:
						_MovingPlatform = false;
						//_onStair = false;
						if (vY < 0 && moveY < 16)
						{
							//đang rơi xuống
							if (_action == Action::Fall)
							{
								if (moveY != 0)
								{
									posY += moveY;
									vY = 0;
									_a = 0;
									_action = Action::Idle;
									_onLand = true;
									Stop();
								}
							}
							else
							{
								posY += moveY;
								//if (abs(rangeStair) >= 40)
								//{
								//	_colStair = false;
								//}
								if (_hasJump || _hasKnockBack)
									if (moveY > 0)
									{
										posY += moveY;
										if (_hasJump || _hasKnockBack)
										{
											_hasJump = false;
											if (_hasKnockBack)
											{
												if (!_isHurted)
												{
													_isHurted = true;

													if (hp >= 0)
													{
														hp -= other->damage;
													}

												}
												_hasKnockBack = false;
											}

											_hasKnockBack = false;
										}
										vY = 0;
										vX = 0;
										_a = 0;
										_allowPress = true;
										sprite->SelectIndex(0);
										if (boxPlayer.h < 60)
											posY += 16;
									}
									else
										if (!_hasJump)
										{
											_a = 0;
											vY = 0;
											vX = 0;
											_a = 0;
											_allowPress = true;
											sprite->SelectIndex(0);
											if (boxPlayer.h < 60)
												posY += 16;
										}
										else
											if (!_hasJump)
											{
												_a = 0;
												vY = 0;
											}
							}
						}
						else if (moveY > 0)
						{

						}

						if ((!_onLand || _action != Action::Idle) && !_hasJump)//Xu ly rot khoi cuc gach 
						{
							vY = -(SPEED_Y + 0.4f);// chỗ này là chỗ rơi xuống tự do
							if (!_onLand)
							{
								//_colStair = false;
							}
							_beFallOutScreen = true;
						}
						//--------------------
						if (_onLand && moveX != 0 && vX != 0 && !_onStair && !_hasJump && !_MovingPlatform)// && !_hasKnockBack)
						{
							posX += moveX;
						}



						//Xu ly rot khoi cuc gach 
						if ((!_onLand || _action != Action::Idle) && !_hasJump)
						{


							vY = -(SPEED_Y + 0.4f);
							//_beFallOutScreen = true;
						}
						//--------------------

						break;


#pragma endregion


#pragma region Va chạm cầu thang

					case EnumID::StairUpRight_ID:
					{
						if (_colStair == false && _hasJump == false)
							_colStair = true;
						if (!_colBottomStair)
							rangeStair = posX - (other->posX - 11);
						_stair = other;
						if (_upStair && _onStair)
						{
							_kindStair = EKindStair::UpRight;
						}

						// 80 - 16 - ( 97 - 33)
						//float _compareHeigh = abs((other->posY - other->height / 2) - (posY - height / 2)); //so sanh do cao player co bang do cao box ko

						float _compareHeigh = abs((other->posY - posY));
						if (_compareHeigh < 15 && _kindStair == EKindStair::DownLeft)
						{
							_outStair = true;
							OutStair();
						}

					}
					break;
					case EnumID::StairUpLeft_ID:
					{
						if (_colStair == false && _hasJump == false)
							_colStair = true;
						if (!_colBottomStair)
							rangeStair = posX - (other->posX + 11);

						_stair = other;
						if (_upStair && _onStair)
						{
							_kindStair = EKindStair::UpLeft;
						}
						float _compareHeigh = abs((other->posY - other->height / 2) - (posY - height / 2)); //so sanh do cao player co bang do cao box ko
						if (_compareHeigh < 2 && _kindStair == EKindStair::DownRight)
						{
							_outStair = true;
							OutStair();
						}
					}
					break;
					case EnumID::StairDownLeft_ID:
					{
						if (_colStair == false && _hasJump == false)
							_colStair = true;
						if (!_colBottomStair)
							rangeStair = posX - (other->posX - 32);

						_stair = other;


						if (_downStair && _onStair)
						{
							_kindStair = EKindStair::DownLeft;
						}
						float _compareHeigh = abs((other->posY - other->height / 2) - (posY - height / 2)); //so sanh do cao player co bang do cao box ko
						if (_compareHeigh < 2 && _kindStair == EKindStair::UpRight)
						{
							_outStair = true;
							OutStair();
						}
					}
					break;
					case EnumID::StairDownRight_ID:
					{
						if (_colStair == false && _hasJump == false)
							_colStair = true;
						if (!_colBottomStair)
							rangeStair = posX - (other->posX + 32);

						_stair = other;

						if (_downStair && _onStair)
						{
							_kindStair = EKindStair::DownRight;
						}
						float _compareHeigh = abs((other->posY - other->height / 2) - (posY - height / 2)); //so sanh do cao player co bang do cao box ko
						if (_compareHeigh < 2 && _kindStair == EKindStair::UpLeft)
						{
							_outStair = true;
							OutStair();
						}
					}
					break;
#pragma endregion 


#pragma region    Va cham voi cac loai cua


					case EnumID::DoorDown_ID:
					{
						// other->y = 432 , posY = 465.0003 , height = 66

						// vì 1 tile size : 32x32 mà player->height = 66. Chia đôi ra tính cho chuẩn
						float dentaHeight = abs((other->posY) - (posY - height / 2));
						if (dentaHeight < 3 && _downStair) // Tại sao là 3 ? Muốn số nào cũng đc, số càng nhỏ , khi 
						{
							_colDoor = true;
						}							// lên xuống cầu thang sẽ càng khỏe

						_door = other;
					}
					break;
					
					case EnumID::DoorUp_ID:
					{
						float dentaHeight = abs((other->posY) - (posY - height / 2));
						if (dentaHeight < 3 && _upStair)
						{
							_colDoor = true;
						}
						_door = other;
					}
					break;
					case EnumID::DoorLeft_ID:
					{
						_door = other;
						_allowPress = false;
						_colDoor = true;
					}
					break;
					case EnumID::DoorRight_ID:
					{
						_door = other;
						_allowPress = false;
						_colDoor = true;
					}
					break;

					
					case EnumID::TrapDoor_ID:
						hp = 0;
						break;

#pragma endregion
					default:

						switch (other->type)
						{
							//#pragma region Va cham Enemy
							//						case ObjectType::Enemy_Type:
							//							if (!_onStair && !_hasStair)
							//							{
							//								if (!_isHurted)
							//									KnockBack();
							//
							//								_isHurted = false;
							//							}
							//							else
							//							{
							//								// chưa có cầu thang
							//								if (!_isHurted)
							//								{
							//
							//									// trừ Hp ở đây
							//									_isHurted = false;
							//
							//								}
							//							}
							//							break;
							//#pragma endregion 
						default:

							break;
						}
						break;
					}

					}

			}
		}
	}
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
	void Player::KnockBack()
	{
		if (!_hasKnockBack)
		{

			if (hp > 0)
			{
				hp -= 1;
				//hp -= other->damage;
			}
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
			_isHurted = true;
		}
	}
	void Player::UseWeapon() {
		if (!_usingWeapon)
		{
			_usingWeapon = true;
		}
	}
	void Player::SetWeapon() {
		switch (_weaponID)
		{
			/*case EnumID::Stop_Watch:
				_usingWatch = true;
				break; */

		case EnumID::Throw_Axe_ID:
			_weapons->push_back(new ThrowAxe(posX, posY, _vLast));
			break;

		case EnumID::Boomerang_ID:
			_weapons->push_back(new Boomerang(posX, posY, _vLast));
			break;
		case EnumID::Dagger_ID:
			_weapons->push_back(new Dagger(posX, posY, _vLast));
			break;

		}
		_hasWeapon = false;
	}
	void Player::ChangeWeapon(EnumID weaponId) {
		_weaponID = weaponId;

	}
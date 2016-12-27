#include "Player.h"

#define PLAYER_FIGHT_RATE 20
#define Player_RATE 10
#define HURT_STATE 25

#define SPEED_X 0.3f
#define SPEED_Y 0.4f
#define MAX_HEIGHT 70.0f
#define A 0.005f

#define MAX_HEIGHT_KNOCKBACK 32.0f
#define MAX_WIDTH_KNOCKBACK 38.0f
Player::Player(void) : DynamicObject()
{
}

Player::Player(int _posX, int _posY) : DynamicObject(_posX, _posY, 0, -SPEED_Y, EnumID::Player_ID)
{

	hp = 12;
	vColMoving = 0;
	_isHurted = false;
	_startToHiddenTime = 0;
	_bHurt = false;
	_action = Action::Idle;
	_a = 0.005f;
	_allowPress = true;
	_hasSit = false;
	_hasJump = false;
	_hasMagicalBall = false;
	//_onLand = false;
	_movingByMovingPlatform = false;
	_colBottomStair = false;
	_hasKnockBack = false;
	_usingStopWatch = false;
	//Door
	_colDoor = false;
	_directDoor = EDirectDoor::NoneDoor;

	_colStair = false;

	_upStair = false;
	_downStair = false;
	_stopOnStair = false;
	_outStair = false;
	//stop
	_stop = false;
	// Death
	_isDie = false;
	hearts = 100;
	_weaponID = EnumID::None_ID;
	weapons = new list<Weapon*>();
	playerJump = new GSprite(Singleton::getInstance()->getTexture(EnumID::Player_ID), 4, 4, 300);

	fightingSprite = new GSprite(Singleton::getInstance()->getTexture(EnumID::Player_ID), 5, 8, 1000 / PLAYER_FIGHT_RATE);
	fightingSittingSprite = new GSprite(Singleton::getInstance()->getTexture(EnumID::Player_ID), 15, 18, 1000 / PLAYER_FIGHT_RATE);
	playerFightingDownStairSprite = new GSprite(Singleton::getInstance()->getTexture(EnumID::Player_ID), 18, 21, 1000 / PLAYER_FIGHT_RATE);
	playerFightingUpStairSprite = new GSprite(Singleton::getInstance()->getTexture(EnumID::Player_ID), 21, 24, 1000 / PLAYER_FIGHT_RATE);
	playerStair = new GSprite(Singleton::getInstance()->getTexture(EnumID::Player_ID), 10, 13, 320);
	morningStar = new MorningStar(_posX, _posY, 0, 0, EnumID::MorningStar_ID, 1000 / PLAYER_FIGHT_RATE);
	playerKnockBack = new GSprite(Singleton::getInstance()->getTexture(EnumID::Player_ID), 8, 8, 100);

	playerDeathSprite = new GSprite(Singleton::getInstance()->getTexture(EnumID::PlayerDeath_ID), 0, 0, 100);
	Initialize();
}


void Player::Update(int deltaTime)
{
	abc = morningStar->getdata();
	list<Weapon*>::iterator it = weapons->begin();
	while (it != weapons->end())
	{
		if (!(*it)->active)
			weapons->erase(it++);
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

		posY += vY *deltaTime;
	}
}
void Player::Draw(GCamera* camera)
{

	if (posY < (camera->viewport.y - G_ScreenHeight))
	{
		hp = 0;
	}

	D3DXVECTOR2 center = camera->Transform(posX, posY);
	if (_isDie)
	{
		playerDeathSprite->DrawFlipX(center.x, center.y);
	}
	else {
		if (!IsHurting())
		{
			for (list<Weapon*>::iterator i = weapons->begin(); i != weapons->end(); i++)
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
			else {

#pragma endregion 
				// đi sang phải
				if (vX > 0 || _vLast > 0)
				{
					if (_action == Action::Fight) {
						if (!_hasSit && !_onStair) {
							fightingSprite->DrawFlipX(center.x, center.y);
						}
						else if (_onStair)
						{
							if (_kindStair == EKindStair::UpRight) {
								playerFightingUpStairSprite->DrawFlipX(center.x, center.y);
							}
							if (_kindStair == EKindStair::DownRight)
							{
								playerFightingDownStairSprite->DrawFlipX(center.x, center.y);
							}
						}
						else
						{
							fightingSittingSprite->DrawFlipX(center.x, center.y);

						}
						if (!_usingWeapon)
							morningStar->Draw(camera);

						// vẽ Fight rồi return luôn
						return;
					}
					if (_onStair) {
						if (_kindStair == EKindStair::UpRight || _kindStair == EKindStair::DownRight) {
							playerStair->DrawFlipX(center.x, center.y);
						}
						//?
						return;
					}
					sprite->DrawFlipX(center.x, center.y);
				}
				// đi sang trái
				else
				{
					if (_action == Action::Fight) {

						if (!_hasSit && !_onStair) {
							fightingSprite->Draw(center.x, center.y);

						}
						else if (_onStair)
						{
							if (_kindStair == EKindStair::UpLeft) {
								playerFightingUpStairSprite->Draw(center.x, center.y);
							}
							if (_kindStair == EKindStair::DownLeft)
							{
								playerFightingDownStairSprite->Draw(center.x, center.y);
							}
						}
						else {
							fightingSittingSprite->Draw(center.x, center.y);

						}
						if (!_usingWeapon)
							morningStar->Draw(camera);
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
		}
		else {
			// ko ve gi het
		}
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
		if (_onStair)
			return;
		ResetStair();
		if (_stop && _vLast<0)
		{
			vX = 0;
		}
		else
		{
			_stop = false;
			vX = -SPEED_X;
			_vLast = vX;
		}
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
		if (_onStair)
			return;
		ResetStair();
		if (_stop && _vLast > 0)

		{
			vX = 0;
		}
		else
		{
			_stop = false;
			vX = SPEED_X;
			_vLast = vX;
		}
		_hasSit = false;
		_action = Action::Run_Right;
	}
}
void Player::Jump()
{
	if (_allowPress)
	{
		if (_action == Action::Fight)
			return;
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
		if (_onMovingPlatform) vY = 0;
		//	return;
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
		if (_action == Action::Run_Left || _action == Action::Run_Right)
			return;
		if (_action == Action::Fight)
			return;
		if (!_hasJump)
			vX = 0;


		if (_usingWeapon && !_hasWeapon && hearts > 0)
		{
			_hasWeapon = true;
			hearts -= 1;
		}
		Sound::GetInst()->PlaySoundEffect(ESoundEffect::ESoundUsingMorningStar);
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
	if (!_hasJump && !_movingByMovingPlatform) vX = 0;
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
		if (_colStair && _stair->posY == posY - 14 && (_stair->id == EnumID::StairUpLeft_ID || _stair->id == EnumID::StairUpRight_ID))
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
		if (_colStair && _stair->posY == posY - 14 && (_stair->id == EnumID::StairDownLeft_ID || _stair->id == EnumID::StairDownRight_ID))
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
	if ((_colStair && _stair->posY == posY - 14 && (_stair->id == EnumID::StairDownLeft_ID || _stair->id == EnumID::StairDownRight_ID)) || _onStair)
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
	if (_onMovingPlatform && _action == Action::Sit)
	{
		vY = 0;
		posX += vColMoving*7.6;// vận tốc di chuyển của movingPlatform
	}
	if (_action == Action::Fight)
	{
		morningStar->Collision(obj, dt);
		point += morningStar->point;
		morningStar->point = 0;
	}
	for (list<Weapon*>::iterator i = weapons->begin(); i != weapons->end(); i++)
	{
		if ((*i)->active)
		{
			(*i)->Collision(obj, dt);
			point += (*i)->point;
			(*i)->point = 0;
		}
	}
	for (list<GameObject*>::iterator _itBegin = obj.begin(); _itBegin != obj.end(); _itBegin++)
	{
		GameObject* other = (*_itBegin);
		if (((other->id == EnumID::Bats_ID||other->id ==EnumID::Skeletons_ID) && other->sprite->GetIndex() == 0))
			other->SetActive(posX, posY);
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
				currentCollideWithID = other->id;
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
					case EnumID::CrossItem_ID:
						_usingCross = true;
						break;
					case EnumID::PorkChop_ID:
						// ăn Pork Chop, máu +6
						hp += 6;
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
						_onMovingPlatform = false;
						//_onStair = false;

						// số 32 ? số càng bé càng khó bắt đc va chạm vs gạch
						if (vY < 0 && moveY < 16)
						{


							if (moveY > 0) {
								// do vẽ ở center của sprite nên + với 1 khoảng = 1/2 của sprite là oke :))
								posY += moveY;

								if (_hasJump || _hasKnockBack)
								{
									_hasJump = false;
									if (_hasKnockBack)
									{
										if (!_hidden)
										{
											_hidden = true;
											_startToHiddenTime = GetTickCount();
											if (hp > 0)
											{
												if (hp <= 3)
												{
													hp -= 1;
												}
												else
													hp -= other->damage;
											}

										}
										_hasKnockBack = false;
									}

									vY = 0;
									vX = 0;
									_a = 0;
									_allowPress = true;
									sprite->SelectIndex(0);
								}

							}
						}
						//--------------------
						if (_onLand && moveX != 0 && vX != 0 && !_onStair && !_hasJump && !_onMovingPlatform)// && !_hasKnockBack)
						{
							posX += moveX;
						}



						//Xu ly rot khoi cuc gach 
						if ((!_onLand || _action != Action::Idle) && !_hasJump)
						{

							// Rơi tự do được
							vY = -(SPEED_Y + 0.4f);

							// Ko roi tu do dc
							//vY = 0;
							//_beFallOutScreen = true;
						}
						//--------------------

						break;


#pragma endregion

#pragma region va chạm với Barrier
					case EnumID::Barrier_ID:
					case EnumID::BrickHide_ID:
					{
						vX = 0;
						if ((_vLast > 0 && _action == Action::Run_Left) || (_vLast < 0 && _action == Action::Run_Right))
						{
							_stop = false;
						}
						else
						{
							_stop = true;
						}

					}
						break;
#pragma endregion

#pragma region Va chạm với MovingPlatform
					case EnumID::MovingPlatform_ID:
					{
						// còn lỗi với knockback....
						//posY += moveY;
						float _compareHeigh = abs((other->posY + other->height / 2) - (posY - height / 2) - moveY);
						// khoảng cách của chân nhân vật cách vị trí của movingPlatform
						// chọn số 4 vì nếu số quá lớn thì nhân vật sẽ tự nhận va chạm ngay
						// -> lỗi. code thay nhiều số, thấy số phù hợp từ khoảng 4->10.
						
						if (vY < 0 && _compareHeigh < 5)
						{
							if (_hasKnockBack) // nếu knockback thì thoát knockback khi chạm Movingplatform
							{
								_hasKnockBack = false;
								vY = -SPEED_Y;
								vX = 0;
								_a = 0;
								_allowPress = true;
								sprite->SelectIndex(0);
								return;
							}
							if (_hasJump)
							{
								_action = Action::Idle;
								sprite->SelectIndex(0);
							}
							_hasJump = false; // vì đang nhảy, mà gặp movingPlatform thì _hasJump vẫn bằng True
							posY += moveY;

							_onMovingPlatform = true;
						}
						
						if (_onMovingPlatform && (_action == Action::Idle|| _action == Action::Fight))

						{
							posX += (other->vX)*15.69;// vận tốc di chuyển của movingPlatform
							vColMoving = other->vX;
						}
						else if (_onMovingPlatform && _hasJump && _action == Action::Run_Right)
						{
							vX = SPEED_X;
							vY = -SPEED_Y;
						}
						else if (_onMovingPlatform && _hasJump && _action == Action::Run_Left)
						{
							vX = -SPEED_X;
							vY = -SPEED_Y;
						}
						else if (_onMovingPlatform && !_hasJump)
						{
							vY = -SPEED_Y;
						}
					}
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


#pragma region    Va chạm với cửa và chuyển stage


					case EnumID::TeleDown_ID:
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

					case EnumID::TeleUp_ID:
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
							// để enemy ở cuối để check được nhiều loại cùng lúc
#pragma region Va chạm với Enemy
						case ObjectType::Enemy_Type:
							// nếu ở trên cầu thang thì chỉ bị mất máu, không bị Knockback, và ngược lại
							if (!_onStair) //&& !_colBottomStair)
							{
								if (!_hidden)
								{
									_hidden = true;
									KnockBack();
									// trừ Hp ở đây
									_startToHiddenTime = GetTickCount();
									if (hp > 0)
									{
										if (hp <= 3)
										{
											hp -= 1;
										}
										else
											hp -= other->damage;
										//hp -= other->damage;
									}

								}
							}
							else
							{
								// đã lên cầu thang
								DecreaseHP(other);


							}

							break;
#pragma endregion 

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
		case TeleDown_ID:

			_directDoor = EDirectDoor::TeleDown;
			break;
		case TeleUp_ID:
			_directDoor = EDirectDoor::TeleUp;
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
	Stop();
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
void Player::UseWeapon() {
	if (!_usingWeapon)
	{
		_usingWeapon = true;
	}
}
void Player::SetWeapon() {
	switch (_weaponID)
	{
	case EnumID::StopWatch_ID:
		_usingStopWatch = true;
		Sound::GetInst()->PlaySoundEffect(ESoundEffect::ESoundMagicBall);
		break;

	case EnumID::Throw_Axe_ID:
		weapons->push_back(new ThrowAxe(posX, posY, _vLast));
		break;

	case EnumID::Boomerang_ID:
		weapons->push_back(new Boomerang(posX, posY, _vLast));
		break;
	case EnumID::Dagger_ID:
		weapons->push_back(new Dagger(posX, posY, _vLast));
		break;
	case EnumID::HolyWater_ID:
		weapons->push_back(new HolyWater(posX, posY, _vLast));
		break;
	}
	_hasWeapon = false;
}
void Player::ChangeWeapon(EnumID weaponId) {
	_weaponID = weaponId;

}

// xem player có đang bị sát thương hay không?
bool Player::IsHurting()
{

	if (!_hidden)
		return false;
	bool result = false;
	DWORD now = GetTickCount();
	DWORD deltaTime = now - _startToHiddenTime;
	if (deltaTime >= 1500)
	{
		_hidden = false;
	}
	if (deltaTime % (int)(1000 / HURT_STATE) < 15)
	{
		_bHurt = !_bHurt;
	}
	return result;
}


void Player::Die(int &_timeCount)
{
	if (_isDie)
	{
		_allowPress = false;
		_timeCount -= 1;
		playerDeathSprite->SelectIndex(0);
		if (_timeCount == 0)
		{
			//_simonDeath = false;
			_allowPress = true;
			_isReset = true;
		}
	}
}

void Player::DecreaseHP(GameObject* other) {
	if (!_hidden)
	{
		_hidden = true;
		// trừ Hp ở đây
		_startToHiddenTime = GetTickCount();
		if (hp > 0)
		{
			if (hp <= 3)
			{
				hp -= 1;
			}
			else
				hp -= other->damage;
			//hp -= other->damage;
		}

	}

}
bool Player::getdata()
{
	return abc;
}
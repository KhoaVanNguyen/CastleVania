
#include "Fleaman.h"

Fleaman::Fleaman(void) : DynamicObject()
{
}

Fleaman::Fleaman(float x, float y) : DynamicObject(x, y, 0.2f, 0, EnumID::Fleaman_ID)
{
	limit = 0;
	canBeKilled = true;
	type = ObjectType::Enemy_Type;
	//point = 200;
	active = true;
	getUp = false;
}

Fleaman::~Fleaman(void)
{
}


void Fleaman::Draw(GCamera* camera)
{
	if (sprite == NULL || !active)
		return;
	if (posX + width / 2 <= camera->viewport.x || posX - width / 2 >= camera->viewport.x + G_ScreenWidth)
	{
		active = false;
		return;
	}
	D3DXVECTOR2 center = camera->Transform(posX, posY);
	if (vX > 0)
		sprite->DrawFlipX(center.x, center.y);
	else
		sprite->Draw(center.x, center.y);
}

void Fleaman::MoveUpdate(float deltaTime)
{
#pragma region __XU_LY_CHUYEN_DONG__

	if (this->_currentState == FLEAMAN_STATE::WAIT) {
		return;
	}
	this->posX += this->vX*deltaTime;
	this->posY += this->vY*deltaTime;
	if (vY <= -0.2)
		vY += 0.2;
	else
		vY = 1.5f; //GRAVITY;


//#pragma endregion
//	_box.x = _x;
//	_box.y = _y;
//	_box.vx = _vx;
//	_box.vy = _vy;
}

void Fleaman::SetFrame(float deltaTime)
{
#pragma region __XU_LY_CHUYEN_DOI_FRAME__
	if (this->_isSleep) {
		this->sprite->_start = 0;
		this->sprite->_end = 0;
	}
	else {
		this->sprite->_start = 0;
		this->sprite->_end = 1;
	}
#pragma endregion
}
void Fleaman::ChangeState(int state) {

	_currentState = state;
	switch (state)
	{
	case FLEAMAN_STATE::WAIT:
		_isSleep = true;
		break;
	case FLEAMAN_STATE::MOVE:
		_isSleep = false;
		_countdown = 0;
		/*if (Simon::getCurrentSimon()->_x>this->_x)
			_vx = 1.5f;
		else
		{
			_vx = -1.5f;
		}*/
		vX = -1.5f;
		vY = -3.0f;
		break;
	}
}
void Fleaman::Update(int deltaTime)
{

	if (hp == 0) {
		this->death = true;
	//	this->_timeDeath += deltatime;
	//	this->_spriteDeath->Update(deltatime);
	}

	if (this->death) {
		return;
	}
	if (_countdown >= TIME_WATING)
		ChangeState(FLEAMAN_STATE::MOVE);
	if ((_currentState == FLEAMAN_STATE::WAIT) && _firstActive)
		_countdown += deltaTime;
	this->MoveUpdate(deltaTime);
	this->SetFrame(deltaTime);
	this->sprite->Update(deltaTime);
	
}

void Fleaman::Collision(list<GameObject*> obj, int dt) {

}

void Fleaman::SetActive(float x, float y)
{
	if (abs(posX - x) <= 300 && abs(posY - y) <= 300)
	{
		if (posX - x > 0)
		{
			vX = -0.2f;
		}
		else vX = 0.2f;
		getUp = true;
		sprite->_start = 1;
	}
}


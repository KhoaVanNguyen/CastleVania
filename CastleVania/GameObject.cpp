
#include "GameObject.h"
#include <d3d9.h>

GameObject::GameObject(void)
{
	posX = 0;
	posY = 0;
	width = 0;
	height = 0;
	canMove = false;
	canBeKilled = true;
}


GameObject::GameObject(float _posX, float _posY, EnumID _id)
{
	posX = _posX;
	posY = _posY;
	vX = 0;
	vY = 0;
	id = _id;
	
	hp = 1;
	point = 1;
	type = ObjectType::None;
	canMove = false;
	active = true;
	
	CreateSprite();
	if (sprite != NULL)
	{
		width = sprite->_texture->FrameWidth;
		height = sprite->_texture->FrameHeight;
	}
}

void GameObject::CreateSprite()
{
	switch (id)
	{
	case EnumID::Player_ID:
		sprite = new GSprite(Singleton::getInstance()->getTexture(id), 0, 3, 100);
		break;
	case EnumID::Brick_ID:
	case EnumID::StairUpRight_ID:
	case EnumID::StairUpLeft_ID:
	case EnumID::StairDownLeft_ID:
	case EnumID::StairDownRight_ID:
	case EnumID::CastleGate_ID:
	case EnumID::TeleDown_ID:
	case EnumID::DoorLeft_ID:
	case EnumID::DoorRight_ID:
	case EnumID::TeleUp_ID:
	case EnumID::Barrier_ID:
		sprite = NULL;
		break;
	case EnumID:: Candle_ID:
		sprite = new GSprite(Singleton::getInstance()->getTexture(id), 0, 3, 100);
		break;
	case EnumID ::MedusaHeads_ID:
		sprite = new GSprite(Singleton::getInstance()->getTexture(id), 0, 1, 100);
		break;
	case EnumID::Bats_ID:
		sprite = new GSprite(Singleton::getInstance()->getTexture(id), 0, 3, 100);
		break;
	case EnumID::Fishmen_ID:
		sprite = new GSprite(Singleton::getInstance()->getTexture(id), 150);
		break;
	case EnumID::OpenDoor_ID:
		sprite = new GSprite(Singleton::getInstance()->getTexture(id), 0, 0, 10);
		break;
	default:
		sprite = new GSprite(Singleton::getInstance()->getTexture(id), 100);
		break;
	}
}


void GameObject::Update(int deltaTime)
{
	if (sprite != NULL)
		sprite->Update(deltaTime);
}

void GameObject::Draw(GCamera* camera)
{
	if (sprite != NULL)
	{
		D3DXVECTOR2 center = camera->Transform(posX, posY);
		sprite->Draw(center.x, center.y);
	}
}
void GameObject::ReceiveDamage(int damage)
{
	if (hp > 0) {
		hp -= damage;
	}
	else {
		death = true;
	}
}
void GameObject::Collision(list<GameObject*> obj, int dt)
{
}
void GameObject::Remove()
{
	active = false;
	death = true;
}
Box GameObject::GetBox()
{
	Box result(posX - width / 2, posY + height / 2, width, height);
	return result;
}
void GameObject::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int t) {}
void GameObject::OnKeyDown(int KeyCode) {}
GameObject::~GameObject(void) {}
void GameObject::SetActive(float x, float y){}
void GameObject::SetActive()
{
	if (!active)
		active = true;
}

void GameObject::Pause() {
	vX = 0;
	vY = 0;
}

ECollisionDirect GameObject::GetCollisionDirect(float normalx, float normaly)
{
	if (normalx == 0 && normaly == 1)
	{
		return ECollisionDirect::Colls_Bot;
	}
	if (normalx == 0 && normaly == -1)
	{
		return ECollisionDirect::Colls_Top;
	}
	if (normalx == 1 && normaly == 0)
	{
		return ECollisionDirect::Colls_Left;
	}
	if (normalx == -1 && normaly == 0)
	{
		return ECollisionDirect::Colls_Right;
	}
	return ECollisionDirect::Colls_None;
}

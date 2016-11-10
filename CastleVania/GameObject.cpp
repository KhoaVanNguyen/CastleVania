
#include "GameObject.h"
#include <d3d9.h>

GameObject::GameObject(void)
{
	posX = 0;
	posY = 0;
	width = 0;
	height = 0;
	canMove = false;
}


GameObject::GameObject(float _posX, float _posY, EnumID _id)
{
	posX = _posX;
	posY = _posY;
	vX = 0;
	vY = 0;
	id = _id;
	
	type = ObjectType::None;
	canMove = false;
	
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

		sprite = NULL;
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
void GameObject::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int t) {}
void GameObject::OnKeyDown(int KeyCode) {}
GameObject::~GameObject(void) {}
#include "RewardItem.h"


RewardItem::RewardItem(void) : DynamicObject()
{
}

RewardItem::RewardItem(float x, float y) : DynamicObject(x, y, 0, -0.4f, EnumID::Reward_ID)
{
	deltatime = 0; 
	active = true;
}

void RewardItem::Update(int dt)
{
	if (sprite == NULL)
		return;
	if (id != EnumID::Reward_ID)
	{
		posY += vY * dt;
		deltatime += dt;
		if (deltatime >= 1500)
			this->Remove();
	}


		width = sprite->_texture->FrameWidth;
		height = sprite->_texture->FrameHeight;

}
void RewardItem::Collision(list<GameObject*> obj, int dt)
{

}

RewardItem::~RewardItem(void)
{
}

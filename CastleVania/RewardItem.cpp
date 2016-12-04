#include "RewardItem.h"


RewardItem::RewardItem(void) : DynamicObject()
{
}

RewardItem::RewardItem(float x, float y) : DynamicObject(x, y, 0, -0.4f, EnumID::Reward_ID)
{
	deltatime = 0;
	active = true;
	type = ObjectType::Item;
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
	if ( id == EnumID::Reward_ID)
		sprite->Update(dt);
	if (id == EnumID::Reward_ID && sprite->GetIndex() == 2)
	{
		srand(time(0));
		int stt = rand() % (2);
		// Random 0->1
		if (stt != 0) {
			stt = rand() % (2);
			// random 2 TH:
			if (stt != 0) {
				id = EnumID::Small_Heart;
				hearts = 1;
				sprite = new GSprite(Singleton::getInstance()->getTexture(EnumID::Small_Heart), 1000);
				//vY = vY / 2;
			}
			else {
				id = EnumID::Large_Heart;
				hearts = 3;
				sprite = new GSprite(Singleton::getInstance()->getTexture(EnumID::Small_Heart), 1000);
			}
			
		}
		else {
			stt = rand() % (2);
		}

	}
	//chưa va chạm
	vY = 0;
	sprite->Update(dt);

	width = sprite->_texture->FrameWidth;
	height = sprite->_texture->FrameHeight;

}
void RewardItem::Collision(list<GameObject*> obj, int dt)
{

}

RewardItem::~RewardItem(void)
{
}

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
	if (id == EnumID::Reward_ID)
		sprite->Update(dt);
	if (id == EnumID::Reward_ID && sprite->GetIndex() == 2)
	{
		srand(time(0));
		int random = rand() % (2);
		// Random 0->1
		// Reward item là hearts
		if (random != 0) {
			random = rand() % (2);
			// random 2 TH:
			if (random != 0) {
				id = EnumID::Small_Heart;
				hearts = 1;
				sprite = new GSprite(Singleton::getInstance()->getTexture(EnumID::Small_Heart), 1000);
				//vY = vY / 2;
			}
			else {
				id = EnumID::Large_Heart;
				hearts = 3;
				sprite = new GSprite(Singleton::getInstance()->getTexture(EnumID::Large_Heart), 1000);
			}

		}
		else {
			random = rand() % (11);
			switch (random)
			{
				
			case 0:
				id = EnumID::Whip_Upgrade;
				sprite = new GSprite(Singleton::getInstance()->getTexture(EnumID::Whip_Upgrade), 1000);
				break;
			case 1:
				id = EnumID::Dagger;
				sprite = new GSprite(Singleton::getInstance()->getTexture(EnumID::Dagger), 1000);
				break;
			case 2:
				id = EnumID::Throw_Axe;
				sprite = new GSprite(Singleton::getInstance()->getTexture(EnumID::Throw_Axe), 1000);
				break;
			case 7:
				id = EnumID::Holy_Watter;
				sprite = new GSprite(Singleton::getInstance()->getTexture(EnumID::Holy_Watter), 1000);
				break;
			case 8:
				id = EnumID::Boomerang;
				sprite = new GSprite(Singleton::getInstance()->getTexture(EnumID::Boomerang), 1000);
				break;
			case 9:
				id = EnumID::Stop_Watch;
				sprite = new GSprite(Singleton::getInstance()->getTexture(EnumID::Stop_Watch), 1000);
				break;
			case 10:
				id = EnumID::White_Money_Bag;
				sprite = new GSprite(Singleton::getInstance()->getTexture(EnumID::White_Money_Bag), 150);
				sprite->SelectIndex(1);
				point = 100;
				break;
			case 11:
				id = EnumID::Purple_Money_Bag;
				sprite = new GSprite(Singleton::getInstance()->getTexture(EnumID::Purple_Money_Bag), 150);
				sprite->SelectIndex(2);
				point = 200;
				break;
			default:
				sprite = new GSprite(Singleton::getInstance()->getTexture(EnumID::Red_Money_Bag), 150);
				id = EnumID::Red_Money_Bag;
				point = 700;
				sprite->SelectIndex(0);
				break;
			}

		}

	}
	//chưa va chạm
	vY = 0;
	//sprite->Update(dt);

	width = sprite->_texture->FrameWidth;
	height = sprite->_texture->FrameHeight;

}
void RewardItem::Collision(list<GameObject*> obj, int dt)
{

}

RewardItem::~RewardItem(void)
{
}

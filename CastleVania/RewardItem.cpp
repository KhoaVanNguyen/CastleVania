#include "RewardItem.h"


RewardItem::RewardItem(void) : DynamicObject()
{
}

RewardItem::RewardItem(float x, float y) : DynamicObject(x, y, 0, -0.4f, EnumID::RewardedItem_ID)
{
	deltatime = 0;
	active = true;
	type = ObjectType::Item;
	_isCrown = false;
}
RewardItem::RewardItem(float x, float y, bool isCrown) : DynamicObject(x, y, 0, -0.4f, EnumID::RewardedItem_ID)
{
	deltatime = 0;
	active = true;
	type = ObjectType::Item;
	_isCrown = isCrown;
}
void RewardItem::Update(int dt)
{
	if (sprite == NULL)
		return;
	if (id != EnumID::RewardedItem_ID)
	{
		posY += vY * dt;
		deltatime += dt;
		if (deltatime >= 1500)
			this->Remove();
	}
	if (id == EnumID::RewardedItem_ID)
		sprite->Update(dt);


	if (id == EnumID::RewardedItem_ID && sprite->GetIndex() == 2)
	{
		
		if (_isCrown) {
			id = EnumID::Crown_ID;
			sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Crown_ID), 150);
		}
		else {
			srand(time(0));
			int random = rand() % (2);
			// Random 0->1
			// Reward item là hearts

			random = 0;
			if (random != 0) {
				random = rand() % (2);
				// random 2 TH:
				if (random != 0) {
					id = EnumID::Small_Heart;
					hearts = 1;
					sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Small_Heart), 1000);
					vY = vY / 2;
				}
				else {
					id = EnumID::Large_Heart;
					hearts = 3;
					sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Large_Heart), 1000);
				}

			}
			else {
				random = rand() % (14);

				//random = 13;
				switch (random)
				{

				case 0:
					id = EnumID::Whip_Upgrade;
					sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Whip_Upgrade), 1000);
					break;
				case 1:
					id = EnumID::Dagger_ID;
					sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Dagger_ID), 1000);
					break;
				case 2:
					id = EnumID::Throw_Axe_ID;
					sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Throw_Axe_ID), 1000);
					break;
				case 7:
					id = EnumID::HolyWater_ID;
					sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::HolyWater_ID), 1000);
					break;
				case 8:
					id = EnumID::Boomerang_ID;
					sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Boomerang_ID), 1000);
					break;
					/*case 9:
					id = EnumID::StopWatch_ID;
					sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::StopWatch_ID), 1000);
					break;*/
				case 10:
					id = EnumID::White_Money_Bag;
					sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::White_Money_Bag), 150);
					sprite->SelectIndex(1);
					point = 100;
					break;
				case 11:
					id = EnumID::Purple_Money_Bag;
					sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Purple_Money_Bag), 150);
					sprite->SelectIndex(2);
					point = 200;
					break;
				case 12:
					id = EnumID::CrossItem_ID;
					sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::CrossItem_ID), 1000);
					break;
				case 13:
					id = EnumID::PorkChop_ID;
					sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::PorkChop_ID), 1000);
					break;
				case 14:
					id = EnumID::StopWatch_ID;
					sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::StopWatch_ID), 1000);
					break;
				default:
					sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::MoneyBagItem_ID), 150);
					switch (random)
					{
					case 3:
						id = EnumID::RedMoneyBag_ID;
						point = 100;
						break;
					case 4:
						id = EnumID::PurpleMoneyBag_ID;
						point = 400;
						sprite->SelectIndex(2);
						break;
					case 5:
						id = EnumID::WhiteMoneyBag_ID;
						point = 700;
						sprite->SelectIndex(1);
						break;
					default:
						id = EnumID::MoneyBagItem_ID;
						point = 100;
						break;
					}
					break;
				}

			}
		}
		
		

	}
	//chưa va chạm
//	vY = 0;
	//sprite->Update(dt);

	width = sprite->_texture->FrameWidth;
	height = sprite->_texture->FrameHeight;

}
void RewardItem::Collision(list<GameObject*> obj, int dt)
{
	if (id != EnumID::RewardedItem_ID)
	{
		list<GameObject*>::iterator _itBegin;
		for (_itBegin = obj.begin(); _itBegin != obj.end(); _itBegin++)
		{
			GameObject* other = (*_itBegin);

			if (other->id == EnumID::Brick_ID)
			{
				float moveX;
				float moveY;
				float normalx;
				float normaly;
				Box box = this->GetBox();
				Box boxOther = other->GetBox();

				if (AABB(box, boxOther, moveX, moveY) == true)
				{
					if (posY > other->posY)
					{
						posY += moveY;
						vY = 0;
						return;
					}
				}
				else
				{
					// review
					Box broadphasebox = GetSweptBroadphaseBox(box, dt);
					if (AABBCheck(GetSweptBroadphaseBox(box, dt), boxOther) == true)
					{
						float collisiontime = SweptAABB(box, boxOther, normalx, normaly, dt);
						if (collisiontime > 0.0f && collisiontime < 1.0f)
						{
							posY += vY * collisiontime;
							vY = 0;
						}
					}
				}
			}
		}
	}
}

RewardItem::~RewardItem(void)
{
}

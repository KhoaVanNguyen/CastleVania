#include "FireBossDie.h"


FireBossDie::FireBossDie(void) : GameObject()
{
}

FireBossDie::FireBossDie(float _posX, float _posY, int _width, int _height) :
GameObject(_posX, _posY, EnumID::FireBossDie_ID)
{
	width = _width;
	height = _height;
}
//FireBossDie::FireBossDie(float x, float y) : GameObject(x, y, 0, -0.4f, EnumID::FireBossDie_ID)
//{
//	deltatime = 0;
//	type = ObjectType::Item;
//	active = true;
//}

//void FireBossDie::Update(int dt)
//{
//	if (sprite == NULL)
//		return;
//	if (id != EnumID::Fire_ID)
//	{
//		posY += vY * dt;
//		deltatime += dt;
//		if (deltatime >= 1500)
//			this->Remove();
//	}
//	if (id == EnumID::MoneyBagItem_ID || id == EnumID::Fire_ID)
//		sprite->Update(dt);
//	if (id == EnumID::Fire_ID && sprite->GetIndex() == 2)
//	{
//		srand(time(0));
//		int stt = rand() % (2);
//		if (stt != 0)
//		{
//			id = EnumID::SmallHeartItem_ID;
//			hearts = 1;
//			sprite = new CSprite(TextureManager::getInstance()->getTexture(EnumID::SmallHeartItem_ID), 1000);
//			vY = vY / 2;
//		}
//		else
//		{
//			stt = rand() % (3);
//			if (stt != 0)
//			{
//				id = EnumID::LargeHeartItem_ID;
//				hearts = 3;
//				sprite = new CSprite(TextureManager::getInstance()->getTexture(EnumID::LargeHeartItem_ID), 1000);
//			}
//			else
//			{
//				stt = rand() % (11);
//				switch (stt)
//				{
//				case 0:
//					id = EnumID::FireBombItem_ID;
//					sprite = new CSprite(TextureManager::getInstance()->getTexture(EnumID::FireBombItem_ID), 1000);
//					break;
//				case 1:
//					id = EnumID::WatchItem_ID;
//					sprite = new CSprite(TextureManager::getInstance()->getTexture(EnumID::WatchItem_ID), 1000);
//					break;
//				case 2:
//					id = EnumID::CrossItem_ID;
//					sprite = new CSprite(TextureManager::getInstance()->getTexture(EnumID::CrossItem_ID), 1000);
//					break;
//				case 7:
//					id = EnumID::MorningStarItem_ID;
//					sprite = new CSprite(TextureManager::getInstance()->getTexture(EnumID::MorningStarItem_ID), 1000);
//					break;
//				case 8:
//					id = EnumID::DaggerItem_ID;
//					sprite = new CSprite(TextureManager::getInstance()->getTexture(EnumID::DaggerItem_ID), 1000);
//					break;
//				case 9:
//					id = EnumID::AxeItem_ID;
//					sprite = new CSprite(TextureManager::getInstance()->getTexture(EnumID::AxeItem_ID), 1000);
//					break;
//				case 10:
//					id = EnumID::BoomerangItem_ID;
//					sprite = new CSprite(TextureManager::getInstance()->getTexture(EnumID::BoomerangItem_ID), 1000);
//					break;
//				default:
//					sprite = new CSprite(TextureManager::getInstance()->getTexture(EnumID::MoneyBagItem_ID), 150);
//					switch (stt)
//					{
//					case 3:
//						id = EnumID::RedMoneyBag_ID;
//						point = 100;
//						break;
//					case 4:
//						id = EnumID::PurpleMoneyBag_ID;
//						point = 400;
//						sprite->SelectIndex(2);
//						break;
//					case 5:
//						id = EnumID::WhiteMoneyBag_ID;
//						point = 700;
//						sprite->SelectIndex(1);
//						break;
//					default:
//						id = EnumID::MoneyBagItem_ID;
//						point = 1000;
//						break;
//					}
//					break;
//				}
//			}
//		}
//		width = sprite->_texture->FrameWidth;
//		height = sprite->_texture->FrameHeight;
//	}
//}
//
//void FireBossDie::Collision(list<GameObject*> obj, int dt)
//{
//	if (id != EnumID::Fire_ID)
//	{
//		list<GameObject*>::iterator _itBegin;
//		for (_itBegin = obj.begin(); _itBegin != obj.end(); _itBegin++)
//		{
//			GameObject* other = (*_itBegin);
//
//			if (other->id == EnumID::Brick_ID)
//			{
//				float moveX;
//				float moveY;
//				float normalx;
//				float normaly;
//				Box box = this->GetBox();
//				Box boxOther = other->GetBox();
//
//				if (AABB(box, boxOther, moveX, moveY) == true)
//				{
//					if (posY > other->posY)
//					{
//						posY += moveY;
//						vY = 0;
//						return;
//					}
//				}
//				else
//				{
//					Box broadphasebox = GetSweptBroadphaseBox(box, dt);
//					if (AABBCheck(GetSweptBroadphaseBox(box, dt), boxOther) == true)
//					{
//						float collisiontime = SweptAABB(box, boxOther, normalx, normaly, dt);
//						if (collisiontime > 0.0f && collisiontime < 1.0f)
//						{
//							posY += vY * collisiontime;
//							vY = 0;
//						}
//					}
//				}
//			}
//		}
//	}
//}

FireBossDie::~FireBossDie(void)
{
}

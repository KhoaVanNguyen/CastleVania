#include "MorningStar.h"

MorningStar::MorningStar(void) :GameObject()
{
	
}

MorningStar::MorningStar(int posX_, int posY_, float vx_, float vy_, EnumID id_, int timeAnimation_) : GameObject(posX_, posY_, id_)
{
	abc = true;
	vX = vx_;
	vY = vy_;
	damage = 1;
	_morningStarSprite = new MorningStarSprite(TextureManager::getInstance()->getTexture(EnumID::MorningStar_ID), 0, 2, timeAnimation_);
}

void MorningStar::reset()
{
	_morningStarSprite->Reset();
}

void MorningStar::Update(int deltaTime_)
{
	_morningStarSprite->Update(deltaTime_);
}

void MorningStar::Draw(GCamera* camera_)
{
	D3DXVECTOR2 center = camera_->Transform(posX, posY);
	if (vX > 0)
	{
		_morningStarSprite->DrawFlipX(center.x, center.y);
	}
	else
	{
		_morningStarSprite->Draw(center.x, center.y);
	}
}

Box MorningStar::GetBox()
{
	int currentState = _morningStarSprite->GetIndex();
	if (currentState < 0 || currentState > 8)
		return Box(0, 0, 0, 0);
	CustomRect* morningStarSize = this->_morningStarSprite->getMorningStarSize().at(currentState);
	return Box(posX - morningStarSize->width / 2, posY + morningStarSize->height / 2, morningStarSize->width, morningStarSize->height);
}

void MorningStar::updateXY(int _posX, int _posY)
{
	float morningStarX = 0;
	float morningStarY = 0;
	int morningState = this->_morningStarSprite->GetIndex();
	posX = _posX;
	posY = _posY;
	switch (morningState % 3)
	{
	case 0:
		morningStarX = posX - 30;
		morningStarY = posY - 5;
		break;
	case 1:
		morningStarX = posX - 30;
		morningStarY = posY + 2;
		break;
	case 2:
		morningStarX = posX + 50; // morningStar's width = 56
		morningStarY = posY + 8;
		break;
	default:
		int i = 0;
		break;
	}

	if (vX <= 0)
	{
		// làm ngược lại, đưa roi ra phía sau Player
		// player's width = 60
		switch (morningState % 3)
		{
		case 0:

			//							                       - W  - 
			morningStarX = (posX + 60) + (posX - morningStarX - 16 - 30); // 40
			break;
		case 1:
			morningStarX = (posX + 60)  + (posX - morningStarX - 32 - 25); // 30
			break;
		case 2:
			morningStarX = (posX + 60) + (posX - morningStarX - 56 - 0); //5
			break;
		default:
			break;
		}
	}
	this->posX = morningStarX;
	this->posY = morningStarY;

	// if not handle position
	/*this->posX = _posX;
	this->posY = _posY;*/

}

void MorningStar::updateVx(float vx)
{
	vX = vx;
}
void MorningStar::updateLevel()
{
	this->_morningStarSprite->updateLevel();
}

void MorningStar::Collision(list<GameObject*> &obj, int dt){
	list<GameObject*>::reverse_iterator _itBegin;
	for (_itBegin = obj.rbegin(); _itBegin != obj.rend(); _itBegin++)
	{
		GameObject* other = (*_itBegin);
	
			float moveX = 0;
			float moveY = 0;

			Box box = this->GetBox();
			Box boxOther = other->GetBox();


			// edit AABB later
			if (AABB(box, boxOther, moveX, moveY) == true)
			{
				abc = other->canBeKilled;
					if ( other->canBeKilled )
					{
						if (other->id == EnumID::Medusa_ID)
						{
							Medusa* qm = (Medusa*)other;
							if (qm->HasGetUp)
							{
								other->ReceiveDamage(damage);
								if (other->hp <= 0)
								{
									point += other->point;
								}
							}
							else
								qm->getUp();
						}
						else if (other->id == EnumID::BreakableBrick_ID) {
							point += other->point;
							(*_itBegin) = new RewardItem(3822, 94,true);
						}
						else
						{
							other->ReceiveDamage(damage);
							if (other->hp <= 0)
							{
								point += other->point;
								(*_itBegin) = new RewardItem(other->posX, other->posY);
							}
							
						}
						
					}
				return;
			}
		}
}

MorningStar::~MorningStar(void)
{
}

MorningStarSprite* MorningStar::getSprite()
{
	return this->_morningStarSprite;
}
bool MorningStar::getdata()
{
	return abc;
}

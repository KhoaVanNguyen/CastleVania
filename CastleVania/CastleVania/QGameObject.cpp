#include "QGameObject.h"


QGameObject::QGameObject(void)
{
}

int QGameObject::RemoveAllObjectInCamera(D3DXVECTOR2 viewport)
{
	int score = 0;
	list<GameObject*>::iterator it = _dynamicObject->begin();
	while (it != _dynamicObject->end())
	{
		GameObject* other = (*it);
		if(other->active && !(other->posX + other->width / 2 <= viewport.x 
			|| other->posX - other->width/2 >=  viewport.x + G_ScreenWidth
			|| other->posY + other->height/2 <= viewport.y - G_ScreenHeight
			|| other->posY - other->height/2 >= viewport.y))
		{
			if(other->type == ObjectType::Enemy_Type)
			{
				switch(other->id)
				{
				case EnumID::PhantomBat_ID:
				case EnumID::QueenMedusa_ID:
					if(other->sprite->GetIndex() != 0)
						other->point -= 4;
					++it;
					break;
				default:					
					score += other->point;
					_dynamicObject->erase(it++);
					break;
				}
			} else ++it;
		}
		else ++it;
	}
	return score;
}


QGameObject::QGameObject(string fileName)
{
	ifstream map (fileName);

	_staticObject = new list<GameObject*>();
	_dynamicObject = new list<GameObject*>();

	if(map.is_open())
	{		
		float posX, posY; int width, height, value;
		int count;
		map>> count >> width >> height;
		int id; 
		int x = 0;
		for (int i = 0; i < count; i++)
		{
			//so thu tu dong - idObj -...
			map>> id >> value >> posX >> posY >> width >> height;		

			switch(value)
			{
			case 0:
				_staticObject->push_back(new Brick(posX, posY, width, height));
				break;
			case 1:
				_staticObject->push_back(new Stair(posX, posY, width + 32, height, EnumID::StairUpLeft_ID));
				break;
			case 2:
				_staticObject->push_back(new Stair(posX, posY, width + 32, height, EnumID::StairUpRight_ID));
				break;
			case 3:
				_staticObject->push_back(new Stair(posX, posY, width + 32, height, EnumID::StairDownRight_ID));
				break;
			case 4:
				_staticObject->push_back(new Stair(posX, posY, width + 32, height, EnumID::StairDownLeft_ID));
				break;
			case 5:
				_staticObject->push_back(new LargeCandle(posX, posY));
				break;
			case 6:
				_staticObject->push_back(new Candle(posX, posY));
				break;
			case 7:
				_dynamicObject->push_back(new BlackLeopard(posX, posY));
				break;
			case 8:
				_dynamicObject->push_back(new FishMan(posX, posY));
				break;
			case 9: 
				_dynamicObject->push_back(new VampireBat(posX, posY));
				break;
			case 10:
				_dynamicObject->push_back(new Zombie(posX, posY));
				break;
			case 11:				
				_phantomBat = new PhantomBat(posX, posY, EnumID::PhantomBat_ID);
				_dynamicObject->push_back(_phantomBat);
				break;
			case 12:
				_dynamicObject->push_back(new Medusa(posX, posY));
				break;
			case 13:
				_dynamicObject->push_back(new BlackKnight(posX, posY));
				break;
			case 14:
				_dynamicObject->push_back(new DragonSkullCannon(posX, posY));
				break;
			case 15:
				_queenMedusa = new QueenMedusa(posX, posY,EnumID::QueenMedusa_ID);
				_dynamicObject->push_back(_queenMedusa);
				break;
			case 16:
				_dynamicObject->push_back(new MovingPlatform(posX, posY));
				break;
			case 17:
				{
				_staticObject->push_back(new StupidDoor(posX, posY, 1040, 900 + (x % 3)*8));
				x++;
				}
				break;
			case 20:
				_staticObject->push_back(new CastleGate(posX, posY, width, height));
				break;
			case 21:
				_staticObject->push_back(new Door(posX, posY, width, height, EnumID::DoorLeft_ID));
				break;
			case 22:
				_staticObject->push_back(new Door(posX, posY, width, height, EnumID::DoorRight_ID));
				break;
			case 23:
				_staticObject->push_back(new Door(posX, posY,  width, height, EnumID::DoorUp_ID));
				break;
			case 24:
				_staticObject->push_back(new Door(posX, posY,  width, height, EnumID::DoorDown_ID));
				break;
			case 25:
				posDoor.x = posX;
				posDoor.y = posY;
				break;
			case 26:
				G_MinSize = posX;
				break;
			case 27:
				G_MaxSize = posX;
				break;
			default:
				break;
			}
		}
	}
	Initialize();
}

D3DXVECTOR2 QGameObject::GetPosDoor()
{
	return posDoor;
}

void QGameObject::Draw(CCamera *camera)
{
	for (list<GameObject*>::iterator i = _staticObject->begin(); i != _staticObject->end(); i++)
	{
		GameObject* obj = (*i);
		if(obj->active)
		{
			obj->Draw(camera);
		}
	}

	for (list<GameObject*>::iterator i = _dynamicObject->begin(); i != _dynamicObject->end(); i++)
	{
		GameObject* obj = (*i);
		if(obj->active)
		{
			obj->Draw(camera);
		}
	}
}
void QGameObject::Update(int deltaTime)
{
	list<GameObject*>::iterator it = _staticObject->begin();
	while (it != _staticObject->end())
	{
		if((*it)->death)
		{
			_staticObject->erase(it++);
		}
		else
		{
			(*it)->Update(deltaTime);
			++it;
		}
	}

	it = _dynamicObject->begin();
	while (it != _dynamicObject->end())
	{
		if(!IsHurt() || (IsHurt() && (*it)->type != ObjectType::Enemy_Type))
		{
			if((*it)->id == EnumID::QueenMedusa_ID)
			{
				if(((QueenMedusa*)*it)->GetState())
				{
				_dynamicObject->push_back(new MagicalCrystal((*it)->posX, (*it)->posY));
				_dynamicObject->erase(it++);
				}
				else ++it;
			}
			else 
				if((*it)->id == EnumID::PhantomBat_ID)
				{
					if(((PhantomBat*)*it)->GetState())
					{
						_dynamicObject->push_back(new MagicalCrystal((*it)->posX, (*it)->posY));
						_dynamicObject->erase(it++);
					}
					else ++it;
				}
				else
				{
					if((*it)->death)
					{
						_dynamicObject->erase(it++);
					}
					else
					{
						if((*it)->active)
						{
							(*it)->Update(deltaTime);
						}
						++it;
					}
				}
		}
		else ++it;
	}
}

void QGameObject::Collision(int dt)
{
	for (list<GameObject*>::reverse_iterator i = _staticObject->rbegin(); i != _staticObject->rend(); i++)
	{
		if((*i)->canMove)
		{
			(*i)->Collision((*_staticObject), dt);
		}
	}

	//for (list<GameObject*>::iterator i = _dynamicObject->begin(); i != _dynamicObject->end(); i++)
	//{
	//	if((*i)->active && (*i)->id != EnumID::PhantomBat_ID && (*i)->id != EnumID::QueenMedusa_ID)
	//	{
	//		if(!IsHurt() || (IsHurt() && (*i)->type != ObjectType::Enemy_Type))
	//			(*i)->Collision((*_staticObject), dt);
	//	}
	//}

	for (list<GameObject*>::iterator i = _dynamicObject->begin(); i != _dynamicObject->end(); i++)
	{
		if((*i)->active)
		{
			(*i)->Collision((*_staticObject), dt);
		}
	}
}

QueenMedusa* QGameObject::getQueenMedusa()
{
	return _queenMedusa;
}

PhantomBat* QGameObject::getPhantomBat()
{
	return _phantomBat;
}

void QGameObject::Initialize()
{
	bActiveHurt = false;
	_localHurtTime = 0;
}

bool QGameObject::IsHurt()
{
	if(!bActiveHurt)
		return false;
	DWORD now = GetTickCount();
	DWORD deltaTime = now - _localHurtTime;
	if(deltaTime >= 1500)
	{
		bActiveHurt = false;
		return false;
	}
	return true;
}

void QGameObject::PauseUpdate()
{
	bActiveHurt = true;
	_localHurtTime = GetTickCount();
}

void QGameObject::RemoveAllObject()
{
	_dynamicObject->clear();
}
QGameObject::~QGameObject(void)
{
}

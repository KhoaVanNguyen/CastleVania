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
		if (other->active && !(other->posX + other->width / 2 <= viewport.x
			|| other->posX - other->width / 2 >= viewport.x + G_ScreenWidth
			|| other->posY + other->height / 2 <= viewport.y - G_ScreenHeight
			|| other->posY - other->height / 2 >= viewport.y))
		{
			if (other->type == ObjectType::Enemy_Type)
			{
				switch (other->id)
				{
				
					
					_dynamicObject->erase(it++);
					break;
				}
			}
			else ++it;
		}
		else ++it;
	}
	return score;
}

//Được gọi khi load Stage
//Filename là tên file Stage
QGameObject::QGameObject(string fileName)
{
	ifstream map(fileName);

	// GameObject :_staticObject,_dynamicObject
	_staticObject = new list<GameObject*>();
	_dynamicObject = new list<GameObject*>();

	if (map.is_open())
	{
		float posX, posY; int width, height, value;
		int count;
		map >> count >> width >> height;
		int id;
		int x = 0;
		// duyệt từng dòng của file Stage
		for (int i = 0; i < count; i++)
		{
			map >> id >> value >> posX >> posY >> width >> height;

			// ứng với giá trị value tương ứng để khởi tạo các object tương tứng
			switch (value)
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
				_dynamicObject->push_back(new Panthers(posX, posY));
				break;
			case 8:
				_dynamicObject->push_back(new Fishmen(posX, posY));
				break;
			case 9:
				_dynamicObject->push_back(new Bats(posX, posY));
				break;
			case 10:
				_dynamicObject->push_back(new Ghouls(posX, posY));
				break;
			case 11:
				_phantomBat = new PhantomBat(posX, posY, EnumID::PhantomBat_ID);
				_dynamicObject->push_back(_phantomBat);
				break;
			case 12:
				_dynamicObject->push_back(new MedusaHeads(posX, posY));
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

}

PhantomBat* QGameObject::getPhantomBat()
{
	return _phantomBat;


}
D3DXVECTOR2 QGameObject::GetPosDoor()
{
	return posDoor;
}

void QGameObject::Draw(GCamera *camera)
{
	for (list<GameObject*>::iterator i = _staticObject->begin(); i != _staticObject->end(); i++)
	{
		GameObject* obj = (*i);
	
		if (obj->active)
		{
			obj->Draw(camera);
		}
	}

	for (list<GameObject*>::iterator i = _dynamicObject->begin(); i != _dynamicObject->end(); i++)
	{
		GameObject* obj = (*i);
	
		if (obj->active)
		{
			obj->Draw(camera);
		}
	}
}
void QGameObject::Collision(int dt)
{
	for (list<GameObject*>::reverse_iterator i = _staticObject->rbegin(); i != _staticObject->rend(); i++)
	{
		if ((*i)->canMove)
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
		if ((*i)->active)
		{
			(*i)->Collision((*_staticObject), dt);
		}
	}
}

void QGameObject::Update(int deltaTime)
{
	list<GameObject*>::iterator it = _staticObject->begin();
	while (it != _staticObject->end())
	{
		
		{
			(*it)->Update(deltaTime);
			++it;
		}
	}

	it = _dynamicObject->begin();
	while (it != _dynamicObject->end())
	{
		if ((*it)->active)
		{
			(*it)->Update(deltaTime);
		}
		++it;
	}
}



QGameObject::~QGameObject(void)
{
}

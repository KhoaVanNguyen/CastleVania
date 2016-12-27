#include "QGameObject.h"

#define STOP_WATCH_TIME = 1200.0
QGameObject::QGameObject(void)
{
	
}

void QGameObject::RemoveAllObject()
{
	_dynamicObject->clear();
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
				
				default:
					score += other->point;
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
				_dynamicObject->push_back(new Ghosts(posX, posY));
				break;
			case 12:
				_dynamicObject->push_back(new MedusaHeads(posX, posY));
				break;
			case 13:
				_dynamicObject->push_back(new AxeKnights(posX, posY));
				break;
			case 14:
				_dynamicObject->push_back(new BoneTowers(posX, posY));
				break;
			case 15:
				_medusa = new Medusa(posX, posY, EnumID::Medusa_ID);
				_dynamicObject->push_back(_medusa);
				break;
			case 16:
			_dynamicObject->push_back(new MovingPlatform(posX, posY));
				break;
			case 17:
			{
	          _staticObject->push_back(new TrapDoor(posX, posY, 1040, 900 + (x % 3) * 8));
				x++;
			}
			break;
			case 18:
				G_LeftCamera = posX;
				break;
			case 19:
				G_RightCamera = posX;
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
				_staticObject->push_back(new Door(posX, posY, width, height, EnumID::TeleUp_ID));
				break;
			case 24:
				_staticObject->push_back(new Door(posX, posY, width, height, EnumID::TeleDown_ID));
				break;
			case 25:
				posDoor.x = posX;
				posDoor.y = posY;
				break;
		

			case 30:
				_staticObject->push_back(new Barrier(posX, posY, width, height));
				break;


			case 31:
				_dynamicObject->push_back(new Fleaman(posX, posY));
				break;
			default:
				break;
			}
		}
	}
	_pausing = false;
	_startToPauseTime = 0;
}

Medusa* QGameObject::getMedusa()
{
	return _medusa;
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

// Gọi về hàm va chạm của lớp con
void QGameObject::Collision(int dt)
{
	for (list<GameObject*>::reverse_iterator i = _staticObject->rbegin(); i != _staticObject->rend(); i++)
	{
		if ((*i)->canMove)
		{
			(*i)->Collision((*_staticObject), dt);
		}
	}
	for (list<GameObject*>::iterator i = _dynamicObject->begin(); i != _dynamicObject->end(); i++)
	{
		if ((*i)->active)
		{
			(*i)->Collision((*_staticObject), dt);
		}
	}
}
// Gọi về hàm update của từng game object để vẽ hình
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
		if  (!IsPausing() || (IsPausing() && (*it)->type != ObjectType::Enemy_Type)) {
			if ((*it)->id == EnumID::Medusa_ID)
			{
				if (((Medusa*)*it)->StateCancel())
				{
					_dynamicObject->push_back(new MagicalBall((*it)->posX, (*it)->posY));
					_dynamicObject->erase(it++);
				}
				else ++it;
			}
			else {

				if ((*it)->active)
				{
					(*it)->Update(deltaTime);

				}
				it++;

			}
		}
		else 
		++it;
	}
}

// Neu IsPausing == false -> Game chay binh thuong
bool QGameObject::IsPausing()
{
	if (!_pausing)
		return false;
	DWORD now = GetTickCount();
	DWORD deltaTime = now - _startToPauseTime;
	if (deltaTime >= 1200)
	{
		_pausing = false;
		return false;
	}
	return true;
}
void QGameObject::PauseUpdate() {
	_pausing = true;
	_startToPauseTime = GetTickCount();
}

QGameObject::~QGameObject(void)
{
}

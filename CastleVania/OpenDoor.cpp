#include "OpenDoor.h"
#include "CEnum.h"

OpenDoor::OpenDoor(void) : GameObject()
{
}

OpenDoor::OpenDoor(float _x, float _y) : GameObject(_x, _y, EnumID::OpenDoor_ID)
{
	_timeCount = 0;
	_openDoor = true;
	_closeDoor = false;
	sprite->SelectIndex(0);
	_playedClose = false;
	_playedOpen = false;
}

OpenDoor::~OpenDoor(void)
{
}
void OpenDoor::RenderOpen()
{
	if (_openDoor)
	{
		if (!_playedOpen)
		{
			//SoundManager::GetInst()->PlaySoundEffect(ESoundEffect::ES_OpenDoor);
			_playedOpen = true;
		}
		_timeCount += 1;
		if (_timeCount <= 40)
		{

			if (_timeCount > 10 && _timeCount < 20)
				sprite->SelectIndex(1);
			else if (_timeCount >= 20 && _timeCount < 40)
			{
				sprite->SelectIndex(2);
			}
		}
		if (_timeCount == 40)
		{
			_timeCount = 0;
			_openDoor = false;
			_closeDoor = true;
		}
	}
}

void OpenDoor::RenderClose()
{
	if (_closeDoor)
	{
		if (!_playedClose)
		{
			//SoundManager::GetInst()->PlaySoundEffect(ESoundEffect::ES_OpenDoor);
			_playedClose = true;
		}
		_timeCount += 1;
		if (_timeCount <= 40)
		{
			if (_timeCount > 10 && _timeCount < 20)
			{
				sprite->SelectIndex(3);
			}
			if (_timeCount >= 20 && _timeCount < 40)
			{
				sprite->SelectIndex(0);
			}
		}
		if (_timeCount == 40)
		{
			_timeCount = 0;
			_openDoor = false;
			_closeDoor = false;
		}
	}
}

bool OpenDoor::GetOpenDoor()
{
	return _openDoor;
}

bool OpenDoor::GetCloseDoor()
{
	return _closeDoor;
}

void OpenDoor::ResetDoor()
{
	_openDoor = true;
	_closeDoor = false;
}

void OpenDoor::Draw(GCamera* camera, int vX)
{

	D3DXVECTOR2 center = camera->Transform(posX, posY);
	if (vX < 0)
	{
		sprite->DrawFlipX(center.x, center.y);
	}
	else
	{
		sprite->Draw(center.x, center.y);
	}
}

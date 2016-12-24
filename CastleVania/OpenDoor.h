#ifndef _OPENDOOR_H_
#define _OPENDOOR_H_

#include "GameObject.h"

class OpenDoor : public GameObject
{
private:
	bool _openDoor;
	bool _closeDoor;
	bool _playedOpen;
	bool _playedClose;
public:
	int _timeCount;
	OpenDoor(void);
	OpenDoor(float _x, float _y);
	~OpenDoor(void);
	void RenderOpen();
	void RenderClose();
	bool GetOpenDoor();
	bool GetCloseDoor();
	void ResetDoor();
	void Draw(GCamera*, int vX, int stage);
};

#endif

#include "Ghosts.h"



Ghosts::Ghosts(void) : DynamicObject()
{
}

Ghosts::Ghosts(float x, float y) : DynamicObject(x, y, 0.08f, 0, EnumID::Ghosts_ID)
{
	type = ObjectType::Enemy_Type;
	point = 300;
	hp = 2;
	damage = 2;
	canBeKilled = true;
	_posY0 = posY;
    _deltaPhi=0;
}

Ghosts::~Ghosts(void)
{
}


void Ghosts::Update(int deltaTime)
{
	int random = rand() % 10;
	if (sprite == NULL || !active)
		return;
	if (random % 2 == 0)
	{
		
		posX += vX*deltaTime;
		if (posX <= width / 2 + 2 || posX >= G_MapWidth - (width / 2 - 2))
			vX = -vX;
		posY += vY*deltaTime;

	}
	else
	{
		
		posX += vX*deltaTime;
		posY = _posY0 + A*cos(2 * PI*deltaTime / T + _deltaPhi); // Phuong trinh chuyen dong duong hinh sin x = 2pi. t/ lamda
		_deltaPhi += 2 * PI*deltaTime / T;
	}
	

	sprite->Update(deltaTime);
}

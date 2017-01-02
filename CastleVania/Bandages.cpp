#include "Bandages.h"


Bandages::Bandages(void)
{
}

Bandages::Bandages(float _posX, float _posY, float _vX, float _vY, EnumID _id)
	: DynamicObject(_posX, _posY, _vX, _vY, _id)
{
	type = ObjectType::Enemy_Type;
	point = 200;
	hp = 0;
	damage = 2;
	canBeKilled = true;
}

//void Bandages::Draw(GCamera* camera)
//{
//	if (sprite == NULL || !active)
//		return;
//	if (posX + width / 2 <= camera->viewport.x || posX - width / 2 >= camera->viewport.x + G_ScreenWidth)
//	{
//		active = false;
//		return;
//	}
//	D3DXVECTOR2 center = camera->Transform(posX, posY);
//	if (vX > 0)
//		sprite->DrawFlipX(center.x, center.y);
//	else
//		sprite->Draw(center.x, center.y);
//}


Bandages::~Bandages(void)
{
}


#include "MorningStarSprite.h"


void MorningStarSprite::_initializeMorningStarState()
{
	_vMorningStarSize = vector<CustomRect*>();
	
	// morningStar.png size = 640x204 
	// using Paint to calculate the size!!
	_vMorningStarSize.push_back(new CustomRect(137, 18, 16, 48));
	_vMorningStarSize.push_back(new CustomRect(280, 12, 32, 38));
	_vMorningStarSize.push_back(new CustomRect(352, 16, 56, 18));
	_vMorningStarSize.push_back(new CustomRect(136, 86, 16, 48));
	_vMorningStarSize.push_back(new CustomRect(280, 80, 32, 38));
	_vMorningStarSize.push_back(new CustomRect(352, 90, 56, 12));
	_vMorningStarSize.push_back(new CustomRect(136, 154, 16, 48));
	_vMorningStarSize.push_back(new CustomRect(280, 148, 32, 38));
	_vMorningStarSize.push_back(new CustomRect(320, 158, 88, 12));
}

MorningStarSprite::MorningStarSprite() :GSprite()
{
}

MorningStarSprite::MorningStarSprite(const MorningStarSprite &morning) : GSprite(morning)
{
}

MorningStarSprite::MorningStarSprite(GTexture* texture, int start, int end, int timeAnimation) : GSprite(texture, start, end, timeAnimation)
{
	_initializeMorningStarState();
}

void MorningStarSprite::updateLevel()
{
	// there are 9 sprites 
	int currentLevel = _start / 3;
	if (currentLevel == 2)
		return;
	_start += 3;
	_end += 3;
	_index = _start;
}


void MorningStarSprite::Draw(int x_, int y_)
{
	if (_index>8)
		return;
	CustomRect* rect = _vMorningStarSize.at(_index);
	RECT* srect = rect->toRect();

	
	D3DXVECTOR3 center(0, 0, 0);
	D3DXVECTOR3 position(0, 0, 0);
	position.x = x_ - rect->width / 2;
	position.y = y_ - rect->height / 2;

	G_SpriteHandler->Draw(
		_texture->Texture,
		srect,
		&center,
		&position,
		D3DCOLOR_XRGB(225, 255, 255)
		);
	delete srect;
}


void MorningStarSprite::DrawFlipX(int x, int y)
{
	D3DXMATRIX oldMt;
	G_SpriteHandler->GetTransform(&oldMt);

	D3DXMATRIX newMt;
	D3DXVECTOR2 center = D3DXVECTOR2(x + _texture->FrameWidth / 2, y + _texture->FrameHeight / 2);
	D3DXVECTOR2 rotate = D3DXVECTOR2(-1, 1);

	D3DXMatrixTransformation2D(&newMt, &center, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt;
	G_SpriteHandler->SetTransform(&finalMt);

	x += _texture->FrameWidth;
	this->Draw(x, y);

	G_SpriteHandler->SetTransform(&oldMt);
}

vector<CustomRect*> MorningStarSprite::getMorningStarSize()
{
	return _vMorningStarSize;
}





MorningStarSprite::~MorningStarSprite(void)
{
}

#ifndef _MORNINGSTARSPRITE_H_
#define _MORNINGSTARSPRITE_H_

#include "GSprite.h"
#include "CustomRect.h"
#include "GTexture.h"
#include <vector>
using namespace std;

class MorningStarSprite :
	public GSprite
{
protected:
	vector<CustomRect*> _vMorningStarSize;
	int _MorningStarLevel;
	void _initializeMorningStarState();

public:

	MorningStarSprite(const MorningStarSprite &morning);
	MorningStarSprite();
	MorningStarSprite(GTexture* texture, int start, int end, int timeAnimation);
	void updateLevel();
	void Draw(int x_, int y_);
	void DrawFlipX(int x_, int y_);
	vector<CustomRect*> getMorningStarSize();
	~MorningStarSprite(void);
};

#endif
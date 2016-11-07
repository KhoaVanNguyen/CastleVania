#ifndef CSPRITE_H
#define CSPRITE_H

#include <d3d9.h>
#include <d3dx9.h>

#include "GTexture.h"

class GSprite {
public: 
	GTexture* _texture;

	int _start;		//chạy từ frame đầu tiên (chỉ số)
	int _end;		//chạy đến frame cuối cùng (chỉ số)
	int _index;		//frame hiện tại
	int _timeAni;	//thời gian chuyển frame
	int _timeLocal;	//biến hỗ trợ đếm thời gian

	GSprite();
	GSprite(const GSprite &sprite);
	GSprite(GTexture* texture, int timeAnimation);
	GSprite(GTexture* texture, int start, int end, int timeAnimation);

	//sang frame tiếp theo
	void Next();

	//trở về frame đầu tiên
	void Reset();

	//chọn 1 frame nào đó
	void SelectIndex(int index);

	//update animation
	void Update(int ellapseTime);

	// Render current sprite at location (X,Y) at the target surface
	void Draw(int x, int y);
	
	//Render with scale (-1, 1)
	void DrawFlipX(int x, int y);

	//render with scale (1, -1)
	void DrawFlipY(int x, int y);

	//Render Rect of texture at (x,y)
	void DrawRect(int X, int Y, RECT SrcRect);

	void DrawIndex(int index, int X, int Y);

	int GetIndex();

	~GSprite();
};

#endif
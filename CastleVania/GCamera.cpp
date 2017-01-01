#include "GCamera.h"
GCamera::GCamera()
{
	viewport.x = 1;
	viewport.y = G_ScreenHeight;
}

void GCamera::SetSizeMap(int _max, int _min)
{
	right = _max;
	left = _min;
}
D3DXVECTOR2 GCamera::Transform(int x, int y)
{
	D3DXMATRIX matrix;
	D3DXMatrixIdentity (&matrix);
	matrix._22 = -1;
	matrix._41 = -viewport.x;
	matrix._42 = viewport.y;

	D3DXVECTOR3 pos3(x ,y ,1);	
	D3DXVECTOR4 MatrixResult;
	D3DXVec3Transform (&MatrixResult,&pos3,&matrix);

	D3DXVECTOR2 result = D3DXVECTOR2 (MatrixResult.x,MatrixResult.y);
	return result;
}



// REVIEW
void GCamera::UpdateCamera(int x)
{
	// camera ko vẽ ra ngoài
	// luôn để player nằm giữa màn hình
	if (x > viewport.x + G_ScreenWidth || x < viewport.x)
	{
		viewport.x = x - G_ScreenWidth / 2;
	}
	if (x  < right - G_ScreenWidth / 2)
		viewport.x = x - G_ScreenWidth / 2;


	// viewport left == left
	if (viewport.x < left)
		viewport.x = left;

	// viewport right = right
	if (viewport.x + G_ScreenWidth > right)
		viewport.x = right - G_ScreenWidth;
}

#ifndef _TILE_H_
#define _TILE_H_

class Tile
{
public:
	int idTile;
	int posX, posY;
	Tile(void);
	Tile(int id, int x, int y);
	~Tile(void);
};

#endif
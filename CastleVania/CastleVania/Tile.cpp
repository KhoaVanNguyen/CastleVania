
#include "Tile.h"


Tile::Tile(void)
{
	idTile = -1;
	posX = 0;
	posY = 0;
}

Tile::Tile(int id, int x, int y)
{
	idTile = id;
	posX = x;
	posY = y;
}

Tile::~Tile(void)
{
}

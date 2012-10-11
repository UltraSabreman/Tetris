#include "Cell.h"
#include "Tetramino.h"
#include "Game.h"

Cell::Cell(Tetramino *tet, TileColors col, int posX, int posY)
{
	_color = col;
	_tetramino = tet;
	_isAlive = true;

	_posX = posX;
	_posY = posY;
}
Cell::~Cell()
{
	return;
}

void Cell::draw()
{
	if(_isAlive)
	{
		al_draw_bitmap(_tetramino->_game->_tiles[_color], _posX, _posY, NULL);
	}
}

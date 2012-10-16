#include "Cell.h"
#include "Tetramino.h"
#include "Game.h"

Cell::Cell(Tetramino *tet, ALLEGRO_BITMAP *tile, int posX, int posY)
{
	_tile = tile;
	_tetramino = tet;

	_posX = posX;
	_posY = posY;

	_tetramino->_game->_grid[_posX + _tetramino->_offsetX][_posY + _tetramino->_offsetY] = this;
	_visited = false;
}
Cell::~Cell()
{
	return;
}

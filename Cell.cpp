#include "Cell.h"
#include "Tetramino.h"
#include "Game.h"

Cell::Cell(Tetramino *tet, ALLEGRO_BITMAP *tile, int posX, int posY)
{
	_tile = tile;
	_tetramino = tet;

	_posX = posX;
	_posY = posY;

	_tetramino->_game->_grid[_posX][_posY] = this;
}
Cell::~Cell()
{
	return;
}

void Cell::draw()
{
	al_draw_bitmap(_tile, (_posX + _tetramino->_offsetX) * PNG_OFFSET, (_posY + _tetramino->_offsetY) * PNG_OFFSET, NULL);
}

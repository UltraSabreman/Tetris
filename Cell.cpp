#include "Cell.h"
#include "Tetramino.h"
#include "Game.h"

Cell::Cell(Tetramino *tet, ALLEGRO_BITMAP *tile, int posX, int posY)
{
	_tile = tile;
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
		al_draw_bitmap(_tile, _posX, _posY, NULL);
	}
}

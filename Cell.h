#ifndef _CELL_H_
#define _CELL_H_
#include "Includes.h"

class Tetramino;
class Game;

class Cell
{
	public:
		Cell(Tetramino *tet, ALLEGRO_BITMAP *tile, int posX, int posY);
		~Cell();

		void draw();

		ALLEGRO_BITMAP *_tile;
		Tetramino *_tetramino;
		int _posX;
		int _posY;
	private:

};

#endif
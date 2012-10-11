#ifndef _CELL_H_
#define _CELL_H_
#include "Includes.h"

class Tetramino;
class Game;

class Cell
{
	public:
		Cell(Tetramino *tet, TileColors col, int posX, int posY);
		~Cell();

		void draw();

		bool _isAlive;

		TileColors _color;
		Tetramino *_tetramino;
		int _posX;
		int _posY;
	private:

};

#endif
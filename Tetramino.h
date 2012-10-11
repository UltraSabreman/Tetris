#ifndef _TETRAMINO_H_
#define _TETRAMINO_H_
#include "Includes.h"

class Game;
class Cell;

class Tetramino
{
	public:
		Tetramino(Game *game);
		~Tetramino();

		void draw();

		Game *_game;
		vector<Cell*> _cells;
};

#endif

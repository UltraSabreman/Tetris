#ifndef _TETRAMINO_H_
#define _TETRAMINO_H_
#include "Includes.h"
#include "TetraTypes.h"

class Game;
class Cell;

class Tetramino
{
	public:
		Tetramino(Game *game, TetraTypes *type, int x, int y);
		~Tetramino();

		void draw();

		Game *_game;
		vector<Cell*> _cells;
		TetraTypes *_type;
};

#endif

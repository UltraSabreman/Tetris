#ifndef _TETRAMINO_H_
#define _TETRAMINO_H_
#include "Includes.h"
#include "TetraTypes.h"


class Game;
class Cell;

class Tetramino
{
	public:
		Tetramino(Game *game, TetraTypes *type, int offX, int offY, int rotation = 0);
		Tetramino(Game *game, vector<Cell*> *newCells, int offx, int offY);
		~Tetramino();

		void makeCells();
		void updateCellRotation();
		bool tryTurn(Direction dir);
		bool isColliding();
		bool tryMove(Direction dir);

		Game *_game;
		vector<Cell*> _cells;
		TetraTypes *_type;
		int _rotation, _realrot;
		int _offsetX;
		int _offsetY;

		bool getAdjacentCells(Tetramino *tet, Cell *cell, vector<Cell*> *testing);
		Cell* getFirstCell();
};

#endif

#include "Tetramino.h"
#include "Cell.h"
#include "Game.h"
#include <time.h>

Tetramino::Tetramino(Game *game)
{
	int w = al_get_display_width(game->_display)/PNG_OFFSET;
	int h = al_get_display_height(game->_display)/PNG_OFFSET;
	
	srand(time(NULL));

	_game = game;
	//		_cells.push_back(new Cell(this, (TileColors) (8 % 7), 1*PNG_OFFSET, 1*PNG_OFFSET));

	for (int x = 0; x < w; x++)
		for (int y = 0; y < h; y++)
		{
			_cells.push_back(new Cell(this, (TileColors) (rand() % 7), x*PNG_OFFSET, y*PNG_OFFSET));
		}
 cout << "lol";
}

void Tetramino::draw()
{
	for (int i = 0; i < _cells.size(); i++)
		_cells[i]->draw();
}	
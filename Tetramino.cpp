#include "Tetramino.h"
#include "Cell.h"
#include "Game.h"
#include <time.h>

Tetramino::Tetramino(Game *game, TetraTypes *type, int ix, int iy)
{
	int w = al_get_display_width(game->_display)/PNG_OFFSET;
	int h = al_get_display_height(game->_display)/PNG_OFFSET;

	_type = type;
	
	srand(time(NULL));

	_game = game;

	//for (int x = 0; x < 4; x++)
	int y = 0;
	for (int x = 0; x < 8; x++)
	{
		y = (x % 4 == 0 ? y + 1 : y);
		if (_type->pattern[x] == '1')
		{
			_cells.push_back(new Cell(this, _type->tile, ix+(x%4)*(PNG_OFFSET), iy+y*(PNG_OFFSET)));
		}
	}
}

void Tetramino::draw()
{
	for (int i = 0; i < _cells.size(); i++)
		_cells[i]->draw();
}	
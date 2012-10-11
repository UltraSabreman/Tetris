#ifndef _GAME_H_
#define _GAME_H_

#include "Includes.h"
#include "Cell.h"
#include "Tetramino.h"

class Game
{
	public:
		Game(ALLEGRO_DISPLAY *disp);
		~Game();
		
		void draw();

		vector<ALLEGRO_BITMAP*> _tiles;
		ALLEGRO_DISPLAY *_display;

		vector<vector<Cell*>> _grid;
		vector<Tetramino*> _tets;
};

#endif
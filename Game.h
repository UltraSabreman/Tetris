#ifndef _GAME_H_
#define _GAME_H_

#include "Includes.h"
#include "Cell.h"
#include "Tetramino.h"
#include "TetraTypes.h"

class Game
{
	public:
		Game(ALLEGRO_DISPLAY *disp);
		~Game();
		
		void draw();

		ALLEGRO_DISPLAY *_display;

		vector<vector<Cell*>> _grid;
		vector<Tetramino*> _tets;
		vector<TetraTypes*> _types;
};

#endif
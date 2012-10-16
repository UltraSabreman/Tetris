#ifndef _GAME_H_
#define _GAME_H_

#include "Includes.h"
#include "Cell.h"
#include "Tetramino.h"
#include "TetraTypes.h"
#include "UI.h"
#include "Input.h"

class Game
{
	public:
		Game(ALLEGRO_DISPLAY *disp);
		~Game();

		void mainRun();
		void doTickLogic();
		void doGravity(Tetramino *Tet);
		void resetTetVisits(Tetramino *Tet);
		void updateGrid();

		Tetramino *_currentTet;
		int _speedMod;
		int _oldMod;
		int _tick;
		bool _lineDeleted;

		vector<vector<Cell*>> _grid;
		vector<Tetramino*> _tets;
		vector<TetraTypes*> _types;

		UI *_ui;
		Input *_iHandler;
};

#endif
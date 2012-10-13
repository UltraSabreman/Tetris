#ifndef _UI_H_
#define _UI_H_

#include "Includes.h"

class Game;

class UI
{
	public:
		UI(Game *game);
		~UI();

		void draw();

		Game *_game;
};

#endif
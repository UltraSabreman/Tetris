#ifndef _UI_H_
#define _UI_H_

#include "Includes.h"

class Game;

class UI
{
	public:
		UI(Game *game, ALLEGRO_DISPLAY *display, int offsetX, int offsetY);
		~UI();

		void mainDraw();
		void drawGrid();
		void drawCells();

		Game *_game;

		ALLEGRO_BITMAP *_drawMap;
		ALLEGRO_BITMAP *_gridMap;
		ALLEGRO_DISPLAY *_display;

		int _gridOffsetX;
		int _gridOffsetY;
		int _scrW;
		int _scrH;
};

#endif
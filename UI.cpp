#include "UI.h"
#include "Game.h"

UI::UI(Game *game)
{
	_game = game;
}

void UI::draw()
{
	for (int x = 0; x < GRID_WIDTH; x++)
		al_draw_line(PNG_OFFSET * x, 0, PNG_OFFSET * x, GRID_HEIGHT * PNG_OFFSET, al_map_rgb(50,50,50), 1);

	for (int y = 0; y < GRID_HEIGHT; y++)
		al_draw_line(0, y * PNG_OFFSET, PNG_OFFSET * GRID_WIDTH, y * PNG_OFFSET, al_map_rgb(50,50,50), 1);

	al_draw_line(PNG_OFFSET * GRID_WIDTH, 0, PNG_OFFSET * GRID_WIDTH, PNG_OFFSET * GRID_HEIGHT, al_map_rgb(255,255,255), 1);
	al_draw_line(0, PNG_OFFSET * GRID_HEIGHT, PNG_OFFSET * GRID_WIDTH, PNG_OFFSET * GRID_HEIGHT, al_map_rgb(255,255,255), 1);
}
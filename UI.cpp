#include "UI.h"
#include "Game.h"

UI::UI(Game *game, ALLEGRO_DISPLAY *display,  int x, int y)
{
	_game = game;
	_display = display;
	_gridOffsetX = x;
	_gridOffsetY = y;	

	_drawMap = al_create_bitmap(al_get_display_width(_display), al_get_display_height(_display));
	_gridMap = al_create_bitmap(GRID_WIDTH * PNG_OFFSET + 2, GRID_HEIGHT * PNG_OFFSET + 1);
}

void UI::drawCells()
{
	for (unsigned int x = 0; x < _game->_grid.size(); x++)
		for (unsigned int y = 0; y < _game->_grid[x].size(); y++)
		{
			Cell *tCell =  _game->_grid[x][y];

			if(tCell != NULL)
			{
				int X = (tCell->_posX + tCell->_tetramino->_offsetX) * PNG_OFFSET + 1;
				int Y = (tCell->_posY + tCell->_tetramino->_offsetY) * PNG_OFFSET;
				al_draw_bitmap(tCell->_tile, X, Y, NULL);
			}
		}

	unsigned int max = _game->_tets.size();
	for (unsigned int i = 0; i < max; i++)
	{
		if (_game->_tets[i] == NULL) continue;
		for (unsigned int l = 0; l < _game->_tets[i]->_cells.size(); l++)
		{
			if (_game->_tets[i] == NULL) continue;
			Cell *cell = _game->_tets[i]->_cells[l];
			
			float r = 0;
			float g = 0;
			float b = 0;

			al_color_hsv_to_rgb(((float) (i+1)/ (float)max) * 360, 1, 1, &r, &g, &b);
			ALLEGRO_COLOR col = al_map_rgb_f(r,g,b);
			if(cell != NULL && cell->_tetramino == _game->_tets[i])
			{
				int x = (cell->_posX + cell->_tetramino->_offsetX) * PNG_OFFSET;
				int y = (cell->_posY + cell->_tetramino->_offsetY) * PNG_OFFSET;
				al_draw_line(x,y,x + ((float)(i+1)/(float)max)*(float)PNG_OFFSET, y + PNG_OFFSET, col, 3);
			}
		}
	}

}

void UI::mainDraw()
{
	_scrW = al_get_display_width(_display);
	_scrH = al_get_display_height(_display);

	al_clear_to_color(al_map_rgb(0,0,0));
	al_set_target_bitmap(_gridMap);
		al_clear_to_color(al_map_rgba(0,0,0,0));
		al_set_clipping_rectangle(0, 4 * PNG_OFFSET + 1, PNG_OFFSET * GRID_WIDTH + 2, PNG_OFFSET * GRID_HEIGHT + 2);

		drawGrid();
		drawCells();

	al_set_target_bitmap(al_get_backbuffer(_display));
	al_draw_bitmap(_gridMap, _gridOffsetX, _gridOffsetY - (4 * PNG_OFFSET), NULL); //the (4 * PNG_OFFSET) compensats for the 4 buffer rows.
	al_flip_display();
}

void UI::drawGrid()
{
	ALLEGRO_COLOR secCol = al_map_rgb(35,35,35);
	ALLEGRO_COLOR primCol = al_map_rgb(255,255,255);

	for (int x = 1; x < GRID_WIDTH; x++)
	{
		int sX = PNG_OFFSET * x;
		int sY = 4 * PNG_OFFSET;
		int eX = sX;
		int eY = GRID_HEIGHT * PNG_OFFSET;

		al_draw_line(sX + 1, sY, eX + 1, eY, secCol, 2);
	}

	for (int y = 4; y < GRID_HEIGHT; y++)
	{
		int sX = 0;
		int sY = PNG_OFFSET * y;
		int eX = PNG_OFFSET * GRID_WIDTH;
		int eY = sY;

		al_draw_line(sX + 1, sY, eX + 1, eY, secCol, 2);
	}

	al_draw_rectangle(1, 4 * PNG_OFFSET, PNG_OFFSET * GRID_WIDTH + 2, PNG_OFFSET * GRID_HEIGHT + 1, primCol, 1);

}
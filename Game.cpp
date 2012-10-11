#include "Game.h"

Game::Game(ALLEGRO_DISPLAY *disp)
{
	
	_display = disp;

	string paths[] = {"Images/RedTile.png","Images/OrangeTile.png","Images/YellowTile.png","Images/GreenTile.png",
		"Images/CyanTile.png","Images/BlueTile.png","Images/PurpleTile.png"};

	for (int i = 0; i < 7; i++)
		_tiles.push_back(al_load_bitmap(paths[i].c_str()));


	/*_grid.resize(11);

	for (int x = 0; x < 10; x++)
		for (int y = 0; y < 10; y++)
			_grid[x].push_back(new Cell();*/

	_tets.push_back(new Tetramino(this));
}

void Game::draw()
{
	for (int i = 0; i < _tets.size(); i++)
		_tets[i]->draw();

/*	for (int x = 0; x < 10; x++)
		for (int y = 0; y < 10; y++)
			_grid[x][y]->draw();*/

}
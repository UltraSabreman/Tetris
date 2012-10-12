#include "Game.h"

Game::Game(ALLEGRO_DISPLAY *disp)
{
	_display = disp;

	//Init tile Images and Patterns
	//both the tiles and paterns, are sorted according to the Color enums
	// That way you can use a color enum to get the pattern and color of
	// a tetramino in one go.

	string paths[] = {"Images/RedTile.png","Images/OrangeTile.png","Images/YellowTile.png","Images/GreenTile.png",
		"Images/CyanTile.png","Images/BlueTile.png","Images/PurpleTile.png"};

	for (int i = 0; i < 7; i++)
	{
		TetraTypes *newType = new TetraTypes();
		newType->tile = al_load_bitmap(paths[i].c_str());
		_types.push_back(newType);
	}

	_types[0]->type = "Z";
	_types[0]->pattern = "11000110";
	_types[1]->type = "L";
	_types[1]->pattern = "11101000";
	_types[2]->type = "O";
	_types[2]->pattern = "11001100";
	_types[3]->type = "S";
	_types[3]->pattern = "01101100";
	_types[4]->type = "I";
	_types[4]->pattern = "11110000";
	_types[5]->type = "J";
	_types[5]->pattern = "11100010";
	_types[6]->type = "T";
	_types[6]->pattern = "11100100";

	for (int i = 0; i < 6; i++)
	{
		_tets.push_back(new Tetramino(this, _types[i], 0, i * PNG_OFFSET * 2));
	}
}

void Game::draw()
{
	for (int i = 0; i < _tets.size(); i++)
		_tets[i]->draw();

/*	for (int x = 0; x < 10; x++)
		for (int y = 0; y < 10; y++)
			_grid[x][y]->draw();*/

}
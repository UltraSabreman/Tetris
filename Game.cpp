#include "Game.h"

Game::Game(ALLEGRO_DISPLAY *disp)
{
	_display = disp;

	_ui = new UI(this);

		_grid.resize(10);
	for (int x = 0; x < 10; x++)
		for (int y = 0; y < 18; y++)
			_grid[x].push_back(NULL);

	//Init tile Images and Patterns
	//both the tiles and paterns, are sorted according to the Color enums
	// That way you can use a color enum to get the pattern and color of
	// a tetramino in one go.

	//images
	string paths[] = {"Images/RedTile.png","Images/OrangeTile.png","Images/YellowTile.png","Images/GreenTile.png",
		"Images/CyanTile.png","Images/BlueTile.png","Images/PurpleTile.png"};

	for (int i = 0; i < 7; i++)
	{
		TetraTypes *newType = new TetraTypes();
		newType->tile = al_load_bitmap(paths[i].c_str());
		_types.push_back(newType);
	}

	//paterns
	string tempPatterns[7][4] = {
		{"0000,1100,0110","001,011,010,000","0000,1100,0110","001,011,010,000"},	//Z
		{"0000,1110,1000","11,01,01,00","0010,1110","010,010,011,000"},				//L
		{"0000,1100,1100","0000,1100,1100","0000,1100,1100","0000,1100,1100"},		//O
		{"0000,1110,0010","01,01,11,00","1000,1110","011,010,010,000"},				//J
		{"0000,1111,0000","01,01,01,01","0000,1111,0000","01,01,01,01"},			//I
		{"0000,0110,1100","010,011,001,000","0000,0110,1100","010,011,001,000"},	//S
		{"0000,1110,0100","01,11,01,00","0100,1110,0000","010,011,010,000"},		//T
	};

	for (int i = 0; i < 7; i++)
		for (int l = 0; l < 4; l++)
			_types[(TetraminoTypes)i]->patterns.push_back(tempPatterns[i][l]);

	for (int i = 0; i < 1; i++)
		_tets.push_back(new Tetramino(this, _types[T], i*4, -1 , 0));
}

void Game::rot()
{
	for (unsigned int i = 0; i < _tets.size(); i++)
	{
		//_tets[i]->tryTurn(LEFT);		
		_tets[i]->tryMove(DOWN);
			//cout << "fail";
	}
}

void Game::updateGrid()
{
	_grid.clear();

	_grid.resize(10);
	for (int x = 0; x < 10; x++)
		for (int y = 0; y < 18; y++)
			_grid[x].push_back(NULL);

	for (unsigned int i = 0; i < _tets.size(); i++)
		for (int c = 0; c < _tets[i]->_cells.size(); c++)
		{
			int x = _tets[i]->_cells[c]->_posX;
			int y = _tets[i]->_cells[c]->_posY;

			_grid[x][y] = _tets[i]->_cells[c];
		}
}

void Game::draw()
{
	_ui->draw();

	for (unsigned int i = 0; i < _tets.size(); i++)
		_tets[i]->draw();

/*	for (int x = 0; x < 10; x++)
		for (int y = 0; y < 10; y++)
			_grid[x][y]->draw();*/

}
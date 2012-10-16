#include "Game.h"
#include <time.h>
#include "Utiltities.h"

Game::Game(ALLEGRO_DISPLAY *disp)
{
	_tick = 0;
	_speedMod = 5;
	_oldMod = _speedMod;
	_lineDeleted = false;

	_ui = new UI(this, disp, PNG_OFFSET, PNG_OFFSET);
	_iHandler = new Input(this);

	_grid.resize(10);
	for (int x = 0; x < GRID_WIDTH; x++)
		for (int y = -3; y < GRID_HEIGHT; y++)
			_grid[x].push_back(NULL);


	//Init tile Images and Patterns
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
		{"0000,1100,0110","001,011,010,000","0000,1100,0110","001,011,010,000"},	//TETRIS_TYPE_Z
		{"0000,1110,1000","11,01,01,00","0010,1110","010,010,011,000"},				//TETRIS_TYPE_L
		{"0000,1100,1100","0000,1100,1100","0000,1100,1100","0000,1100,1100"},		//TETRIS_TYPE_O
		{"0000,1110,0010","01,01,11,00","1000,1110","011,010,010,000"},				//TETRIS_TYPE_J
		{"0000,0000,1111","01,01,01,01","0000,0000,1111","01,01,01,01"},			//TETRIS_TYPE_I
		{"0000,0110,1100","010,011,001,000","0000,0110,1100","010,011,001,000"},	//TETRIS_TYPE_S
		{"0000,1110,0100","01,11,01,00","0100,1110,0000","010,011,010,000"},		//TETRIS_TYPE_T
	};

	for (int i = 0; i < 7; i++)
		for (int l = 0; l < 4; l++)
			_types[(TetraminoTypes)i]->patterns.push_back(tempPatterns[i][l]);

	srand(time(NULL));
	_currentTet = NULL;
}

void Game::doGravity(Tetramino *tet)
{	
	if (tet == _currentTet && !tet->tryMove(TETRIS_DIR_DOWN))
	{
		_currentTet = NULL;
		Tetramino *newTetra = new Tetramino(this, _types[rand() % 7], GRID_WIDTH/2- 2, 0);
		_tets.push_back(newTetra);
		_currentTet = newTetra;
	}
	else if(tet != _currentTet)
		tet->tryMove(TETRIS_DIR_DOWN);
}

void Game::resetTetVisits(Tetramino *tet)
{
	if (tet == NULL) return;

	for (unsigned int i = 0; i < tet->_cells.size(); i++)
		if (tet->_cells[i] != NULL)
			tet->_cells[i]->_visited = false;
}

void Game::doTickLogic()
{
	//splitting tetraminos and deleting empty ones.
	bool tet = false;
	vector<Cell*> *adjCells = new vector<Cell*>;

	for (unsigned int i = 0; i < _tets.size(); i++)
	{	
		Tetramino *curTet = _tets[i];
		if (curTet == NULL) continue;
		if (curTet != _currentTet)
		{
			if (curTet->_cells.size() == 0)
			{
				delete curTet;
				_tets[i] = NULL;
				continue;
			}

			adjCells->clear();
			if(!curTet->getAdjacentCells(curTet, curTet->getFirstCell(), adjCells)) continue;

			while (adjCells->size() != curTet->_cells.size() && adjCells->size() != 0)
			{
				tet = true;
				/*
					1) make new tetramino out of the adjCell vec
					2) NULL all cells in the tet->cells vector that are aslo in the adjCell vec.
					3) Clear adjCells vec and repeat procces with the next non-null cell in teramino->cell vec.
				*/

				resetTetVisits(curTet);

				_tets.push_back(new Tetramino(this, adjCells, curTet->_offsetX, curTet->_offsetY));
				curTet->_cells = Utilities::subtractVectors<vector<Cell*>>(adjCells, &curTet->_cells);

				adjCells->clear();

				if(!curTet->getAdjacentCells(curTet, curTet->getFirstCell(), adjCells)) break;
			} 
			resetTetVisits(curTet);
		}
		if(!tet)
		doGravity(curTet);
	}
}

void Game::mainRun()
{
	int numOfCellsInLine;
	for (int y = 0; y < GRID_HEIGHT; y++)
	{
		numOfCellsInLine = 0;
		for (int x = 0; x < GRID_WIDTH; x++)
			if (_grid[x][y] != NULL && _grid[x][y]->_tetramino != _currentTet)
				numOfCellsInLine++;

		if (numOfCellsInLine == GRID_WIDTH)
		{
			_lineDeleted = true;
			for (int i = 0; i < numOfCellsInLine; i++)
			{
				Cell *tempCell = _grid[i][y];
				Tetramino *tempTet = tempCell->_tetramino;

				for (unsigned int l = 0; l < tempTet->_cells.size(); l++)
					if (tempTet->_cells[l] == tempCell)
					{
						tempTet->_cells[l] = NULL;
						break;
					}

				delete tempCell;
				_grid[i][y] = NULL;
			}
		}
	}

	if(_currentTet == NULL)
	{
		Tetramino *newTetra = new Tetramino(this, _types[rand() % 7], GRID_WIDTH/2 - 2, 0);
		_tets.push_back(newTetra);
		_currentTet = newTetra;
	}

	_iHandler->ioProcess();
}

void Game::updateGrid()
{
	_grid.clear();

	_grid.resize(GRID_WIDTH);
	for (int x = 0; x < GRID_WIDTH; x++)
		for (int y = -3; y < GRID_HEIGHT; y++)
			_grid[x].push_back(NULL);

	for (unsigned int i = 0; i < _tets.size(); i++)
	{
		if (_tets[i] == NULL) continue;
		for (unsigned int c = 0; c < _tets[i]->_cells.size(); c++)
		{
			if (_tets[i] != NULL && _tets[i]->_cells[c] != NULL)
			{
				int x = _tets[i]->_cells[c]->_posX + _tets[i]->_offsetX;
				int y = _tets[i]->_cells[c]->_posY + _tets[i]->_offsetY;

				_grid[x][y] = _tets[i]->_cells[c];
			}
		}
	}
}

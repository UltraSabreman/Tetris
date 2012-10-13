#include "Tetramino.h"
#include "Cell.h"
#include "Game.h"
#include "Utiltities.h"
//#include <time.h>

Tetramino::Tetramino(Game *game, TetraTypes *type, int offsetX, int offsetY, int rotation)
{
	//int w = al_get_display_width(game->_display)/PNG_OFFSET;
	//int h = al_get_display_height(game->_display)/PNG_OFFSET;

	_type = type;
	_game = game;
	_rotation = rotation;
	_offsetX = offsetX;
	_offsetY = offsetY;

	makeCells();
	_realrot = 0;
	_rotation = 0;
}

bool Tetramino::isColliding()
{
	bool flag = false;

	for (int i = 0; i < _cells.size(); i++)
	{
		int cellPosX = _cells[i]->_posX;
		int cellPosY = _cells[i]->_posY;

		if (!flag && _game->_grid[cellPosX][cellPosX] != NULL && _game->_grid[cellPosX][cellPosY]->_tetramino != this)
			flag = true;

		cellPosX += _offsetX;
		cellPosY += _offsetY;

		if (!flag && (cellPosX < 0 || cellPosX >= GRID_WIDTH || cellPosY < 0 || cellPosY >= GRID_HEIGHT))
			flag = true;
	}
	//cout << "---" << endl;
	return flag;
}

bool Tetramino::tryTurn(Direction dir)
{
	if (dir == UP || dir == DOWN) return false;

	int oldreal = _realrot;
	int oldrot = _rotation;
	if (dir == LEFT)
		_realrot = --_realrot;
	else
		_realrot = ++_realrot;

	_rotation = abs(_realrot) % 4;

	updateCells();
	if(isColliding())
	{
		_rotation = oldrot;
		_realrot = oldreal;
		updateCells();
		return false;
	}
	_game->updateGrid();
	return true;
}

bool Tetramino::tryMove(Direction dir)
{
	if (dir == UP) return false;

	int oldX = _offsetX;
	int oldY = _offsetY;

	if (dir == DOWN) 
		_offsetY++;
	else if (dir == LEFT) 
		_offsetX--;
	else 
		_offsetX++;

	updateCells();
	if(isColliding())
	{
		_offsetX = oldX;
		_offsetY = oldY;
		updateCells();
		return false;
	}
	_game->updateGrid();
	return true;

}

void Tetramino::updateCells()
{
	vector<string> tempPatterns;
	stringExplode(_type->patterns[_rotation], ',', tempPatterns);

	int cellind = 0;
	for (int y = 0; y < tempPatterns.size(); y++)
		for (int x = 0; x < tempPatterns[0].length(); x++)
		{
			if (tempPatterns[y][x] == '1')
			{ 
				_cells[cellind]->_posX = x;
				_cells[cellind]->_posY = y;
				cellind++;
			}
		}
}

void Tetramino::makeCells()
{
	for (int i = 0; i < _cells.size(); i++)
		delete _cells[i];

	_cells.clear();

	vector<string> tempPatterns;
	stringExplode(_type->patterns[_rotation], ',', tempPatterns);

	for (int y = 0; y < tempPatterns.size(); y++)
		for (int x = 0; x < tempPatterns[0].length(); x++)
			if (tempPatterns[y][x] == '1')
			{
				Cell *newCell = new Cell(this, _type->tile, x, y);
				_cells.push_back(newCell);
			}
}

void Tetramino::draw()
{
	for (unsigned int i = 0; i < _cells.size(); i++)
		_cells[i]->draw();
}	
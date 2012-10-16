#include "Tetramino.h"
#include "Cell.h"
#include "Game.h"
#include "Utiltities.h"

Tetramino::Tetramino(Game *game, TetraTypes *type, int offsetX, int offsetY, int rotation)
{
	_type = type;
	_game = game;
	_rotation = rotation;
	_offsetX = offsetX;
	_offsetY = offsetY;

	makeCells();
	_realrot = 0;
	_rotation = 0;
}

Tetramino::Tetramino(Game *game, vector<Cell*> *newCells, int offX, int offY)
{
	_game = game;
	_cells = *newCells;
	_offsetX = offX;
	_offsetY = offY;
}

Tetramino::~Tetramino()
{
	return;
}

Cell* Tetramino::getFirstCell()
{
	for (unsigned int i = 0; i < _cells.size(); i++)
		if (_cells[i] != NULL)
				return _cells[i];
	
	return NULL;
}
// Still wrong ffs
bool Tetramino::getAdjacentCells(Tetramino *tet, Cell *cell, vector<Cell*> *connectedCells)
{
	if (cell == NULL || cell->_visited || cell->_tetramino != tet) return false;

	cell->_visited = true;
	connectedCells->push_back(cell);

	int posX = cell->_posX + cell->_tetramino->_offsetX;
	int posY = cell->_posY + cell->_tetramino->_offsetY;

	for (int x = posX - 1; x < posX + 1; x += 2)
		if (x >= 0 && x < GRID_WIDTH)
			getAdjacentCells(tet, _game->_grid[x][posY], connectedCells);

	for (int y = posY - 1; y < posY + 1; y += 2)
		if (y >= 0 && y < GRID_HEIGHT)
			getAdjacentCells(tet, _game->_grid[posX][y], connectedCells);

	return true;
}

bool Tetramino::isColliding()
{
	bool flag = false;

	for (unsigned int i = 0; i < _cells.size(); i++)
	{
		if (_cells[i] != NULL)
		{
			int cellPosX = _cells[i]->_posX + _offsetX;
			int cellPosY = _cells[i]->_posY + _offsetY;

			if (!flag && (cellPosX < 0 || cellPosX >= GRID_WIDTH || cellPosY < 0 || cellPosY >= GRID_HEIGHT))
				flag = true;

			if (!flag && _game->_grid[cellPosX][cellPosY] != NULL && _game->_grid[cellPosX][cellPosY]->_tetramino != this)
				flag = true;
		}
	}
	return flag;
}

bool Tetramino::tryTurn(Direction dir)
{
	if (dir == TETRIS_DIR_UP || dir == TETRIS_DIR_DOWN) return false;

	int oldreal = _realrot;
	int oldrot = _rotation;
	if (dir == TETRIS_DIR_LEFT)
		_realrot = --_realrot;
	else
		_realrot = ++_realrot;

	_rotation = abs(_realrot) % 4;

	updateCellRotation();
	if(isColliding())
	{
		_rotation = oldrot;
		_realrot = oldreal;
		updateCellRotation();
		return false;
	}
	_game->updateGrid();
	return true;
}

bool Tetramino::tryMove(Direction dir)
{
	if (dir == TETRIS_DIR_UP) return false;

	int oldX = _offsetX;
	int oldY = _offsetY;

	if (dir == TETRIS_DIR_DOWN) 
		_offsetY++;
	else if (dir == TETRIS_DIR_LEFT) 
		_offsetX--;
	else 
		_offsetX++;

	int size = _game->_tets.size();
	int pos = _offsetY;

	if(isColliding())
	{
		_offsetX = oldX;
		_offsetY = oldY;
		return false;
	}

	_game->updateGrid();
	return true;

}

void Tetramino::updateCellRotation()
{
	vector<string> tempPatterns;
	Utilities::stringExplode(_type->patterns[_rotation], ',', tempPatterns);

	int cellind = 0;
	for (unsigned int y = 0; y < tempPatterns.size(); y++)
		for (unsigned int x = 0; x < tempPatterns[0].length(); x++)
		{
			if (tempPatterns[y][x] == '1' && _cells[cellind] != NULL)
			{ 
				_cells[cellind]->_posX = x;
				_cells[cellind]->_posY = y;
				cellind++;
			}
		}
}

void Tetramino::makeCells()
{
	for (unsigned int i = 0; i < _cells.size(); i++)
		delete _cells[i];

	_cells.clear();

	vector<string> tempPatterns;
	Utilities::stringExplode(_type->patterns[_rotation], ',', tempPatterns);

	for (unsigned int y = 0; y < tempPatterns.size(); y++)
		for (unsigned int x = 0; x < tempPatterns[0].length(); x++)
			if (tempPatterns[y][x] == '1')
			{
				Cell *newCell = new Cell(this, _type->tile, x, y);
				_cells.push_back(newCell);
			}
}

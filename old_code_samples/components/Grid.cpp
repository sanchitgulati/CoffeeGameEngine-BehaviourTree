#include "Grid.hpp"

std::shared_ptr<Grid> Grid::createWithSizeAndType(int i, int j, int totalGemsType, int rseed)
{
	auto grid = std::make_shared<Grid>();
	grid->_gridHeight = i;
	grid->_gridWidth = j;
	grid->_totalGemsTypes = totalGemsType;
	grid->_eng = std::mt19937(rseed);
	grid->init();
	while (!grid->isPossibleMoves()) {
		grid->init();
	}
	return grid;
}

void Grid::init()
{
	_gameBoard.resize(_gridHeight);
	for (int i = 0; i < _gridHeight; i++) {
		_gameBoard[i].resize(_gridWidth, -1); //-1 is invalid gem
	}
	_dice = std::uniform_int_distribution<int>(1, _totalGemsTypes);


	for (int i = 0; i < _gridHeight; i++) {
		for (int j = 0; j < _gridWidth; j++) {
			do {
				_gameBoard[i][j] = _dice(_eng);
			} while (!checkTileFromTopLeft(i, j));
		}
	}
}

bool Grid::checkGrid(GameBoard gameboard)
{
	for (int i = 0; i < gameboard.size(); i++) {
		for (int j = 0; j < gameboard[0].size(); j++) {
			if (isValidMoveOn(i, j, gameboard)) {
				return true;
			}
		}
	}
	return false;
}

bool Grid::checkTileFromTopLeft(int i, int j)
{
	if (i >= 2) {
		if (_gameBoard[i - 2][j] == _gameBoard[i - 1][j] && _gameBoard[i - 1][j] == _gameBoard[i][j]) {
			return false;
		}
	}
	if (j >= 2) {
		if (_gameBoard[i][j - 2] == _gameBoard[i][j - 1] && _gameBoard[i][j - 1] == _gameBoard[i][j]) {
			return false;
		}
	}
	return true;
}

void Grid::printGrid(GameBoard board)
{
	printf("\n");
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[0].size(); j++) {
			printf("(%d)", board[i][j]);
		}
		printf("\n");
	}
}

bool Grid::isValidMoveOn(int i, int j, std::vector< std::vector <int>>& grid)
{
	if (i >= 2) {
		if (grid[i - 2][j] == grid[i - 1][j] && grid[i - 1][j] == grid[i][j]) {
			return true;
		}
	}
	if (j >= 2) {
		if (grid[i][j - 2] == grid[i][j - 1] && grid[i][j - 1] == grid[i][j]) {
			return true;
		}
	}

	if ( i > 0 && i < grid.size() - 1) {
		if (grid[i - 1][j] == grid[i+1][j] && grid[i+1][j] == grid[i][j]) {
			return true;
		}
	}
	if (j > 0 && j < grid[0].size() - 1) {
		if (grid[i][j - 1] == grid[i][j + 1] && grid[i][j + 1] == grid[i][j]) {
			return true;
		}
	}

	if (i < grid.size() - 2) {
		if (grid[i + 2][j] == grid[i + 1][j] && grid[i + 1][j] == grid[i][j]) {
			return true;
		}
	}
	if (j < grid[0].size() - 2) {
		if (grid[i][j + 2] == grid[i][j + 1] && grid[i][j + 1] == grid[i][j]) {
			return true;
		}
	}

	return false;
}

bool Grid::isValidMove(int i, int j)
{
	return isValidMoveOn(i, j, _gameBoard);
}

bool Grid::checkGameGrid()
{
	return checkGrid(_gameBoard);
}


int Grid::getWidth()
{
	return _gridWidth;
}

int Grid::getHeight()
{
	return _gridHeight;
}

int Grid::getGemAt(int i, int j)
{
	return _gameBoard[i][j];
}

ivector2 Grid::getNextMatch()
{
	for (int i = 0; i < _gridHeight; i++) {
		for (int j = 0; j < _gridWidth; j++) {
			if (isValidMove(i, j)) { return ivector2(i, j); }
		}
	}
	return ivector2(-1, -1);
}

bool Grid::isValidIndex(ivector2 gemIndex)
{
	if (gemIndex.x < 0 || gemIndex.x >= _gridHeight || gemIndex.y < 0 || gemIndex.y >= _gridWidth)
		return false;
	return true;
}
bool Grid::canSwap(ivector2 gem1, ivector2 gem2)
{
	//Make a copy of game board so we don't manipulate the original board
	auto tempGameBoard = _gameBoard;


	auto temp = tempGameBoard[gem1.x][gem1.y];
	tempGameBoard[gem1.x][gem1.y] = tempGameBoard[gem2.x][gem2.y];
	tempGameBoard[gem2.x][gem2.y] = temp;
	return isValidMoveOn(gem2.x, gem2.y,tempGameBoard);
}

bool Grid::isPossibleMoves()
{
	for (int i = 0; i < _gridHeight; i++) {
		for (int j = 0; j < _gridWidth; j++) {
			auto newboard = _gameBoard;
			if (i != 0) {
				newboard[i - 1][j] = newboard[i - 1][j] ^ newboard[i][j];
				newboard[i][j] = newboard[i - 1][j] ^ newboard[i][j];
				newboard[i - 1][j] = newboard[i - 1][j] ^ newboard[i][j];
				if (checkGrid(newboard)) return true;
				newboard = _gameBoard;
			}
			if (i != _gameBoard.size() - 1) {
				newboard[i + 1][j] = newboard[i + 1][j] ^ newboard[i][j];
				newboard[i][j] = newboard[i + 1][j] ^ newboard[i][j];
				newboard[i + 1][j] = newboard[i + 1][j] ^ newboard[i][j];
				if (checkGrid(newboard)) return true;
				newboard = _gameBoard;
			}
			if (j != 0) {
				newboard[i][j - 1] = newboard[i][j - 1] ^ newboard[i][j];
				newboard[i][j] = newboard[i][j - 1] ^ newboard[i][j];
				newboard[i][j - 1] = newboard[i][j - 1] ^ newboard[i][j];
				if (checkGrid(newboard)) return true;
				newboard = _gameBoard;
			}
			if (j != _gameBoard[i].size() - 1) {
				newboard[i][j + 1] = newboard[i][j + 1] ^ newboard[i][j];
				newboard[i][j] = newboard[i][j + 1] ^ newboard[i][j];
				newboard[i][j + 1] = newboard[i][j + 1] ^ newboard[i][j];
				if (checkGrid(newboard)) return true;
				newboard = _gameBoard;
			}
		}
	}
	return false;

}

GameBoard  Grid::swap(ivector2 gem1, ivector2 gem2)
{
	auto temp = _gameBoard[gem1.x][gem1.y];
	_gameBoard[gem1.x][gem1.y] = _gameBoard[gem2.x][gem2.y];
	_gameBoard[gem2.x][gem2.y] = temp;
	return processBoard(gem2);
}


GameBoard  Grid::processBoard(ivector2 gem)
{
	GameBoard deltaMovement;
	deltaMovement.resize(_gridHeight);
	for (int i = 0; i < _gridHeight; i++) {
		deltaMovement[i].resize(_gridWidth, 0);
	}

	GameBoard tempboard = _gameBoard;
	int type = tempboard[gem.x][gem.y];
	tempboard[gem.x][gem.y] = -1;

	//remove adjacent gems
	for (int i = gem.y - 1; i >= 0; i--) {
		if (tempboard[gem.x][i] == type) {
			tempboard[gem.x][i] = -1;
		}
		else break;
	}
	for (int i = gem.y + 1; i < _gridWidth; i++) {
		if (tempboard[gem.x][i] == type) {
			tempboard[gem.x][i] = -1;
		}
		else break;

	}
	for (int i = gem.x - 1; i >= 0; i--) {
		if (tempboard[i][gem.y] == type) {
			tempboard[i][gem.y] = -1;
		}
		else break;
	}
	for (int i = gem.x + 1; i < _gridHeight; i++) {
		if (tempboard[i][gem.y] == type) {
			tempboard[i][gem.y] = -1;
		}
		else break;

	}

	//figure out deltamovement per gem
	for (int j = 0; j < _gridWidth; j++) {
		int movement = 0;
		for (int i = _gridHeight - 1; i >= 0; i--) {
			if (tempboard[i][j] == -1) {
				movement++;
				deltaMovement[i][j] = -1;
			}
			else {
				deltaMovement[i][j] = movement;
			}
		}
	}


	//change gameboard
	for (int j = 0; j < _gridWidth; j++) {
		for (int i = _gridHeight - 1; i >= 0; i--) {
			int move = deltaMovement[i][j];
			if(move != -1)
				tempboard[i + move][j] = tempboard[i][j];
			if (move > 0)
				tempboard[i][j] = -1;
		}
	}

	//initiate new gems
	for (int i = 0; i < _gridHeight; i++) {
		for (int j = 0; j < _gridWidth; j++) {
			if (tempboard[i][j] == -1)
				tempboard[i][j] = _dice(_eng);
		}
	}

	//replacing the board with the new board
	_gameBoard = tempboard;
	return deltaMovement;

}

void Grid::setGridManually(GameBoard board)
{
	_gameBoard = board;
}

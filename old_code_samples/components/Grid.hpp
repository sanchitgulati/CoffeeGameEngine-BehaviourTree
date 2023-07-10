#pragma once
#include <random>
#include <memory>
#include "../../Coffee/include/Vector.hpp"
using namespace Coffee;
using GameBoard = std::vector<std::vector<int>>;
class Grid
{
public:
	static std::shared_ptr<Grid> createWithSizeAndType(int i,int j,int totalCandiesType,int rseed = 42);
	void init();
	bool isValidMoveOn(int i, int j, std::vector< std::vector <int>>& grid);
	bool isValidMove(int i, int j);
	bool checkGameGrid();
	int getWidth();
	int getHeight();
	int getGemAt(int i,int j);
	//Returns the next possible match or -1,-1 if there is none
	ivector2 getNextMatch();
	//checks if 2 gems can be swapped
	bool canSwap(ivector2 gem1, ivector2 gem2);
	//Checks the entire board for any possible matches after 1 move
	bool isPossibleMoves();
	//Swaps the gems and internally calls processboard func
	GameBoard swap(ivector2 gem1, ivector2 gem2);
	GameBoard  processBoard(ivector2 gem);
	// To make relevant Google Test cases
	void setGridManually(GameBoard board);
	//checks if iterator index are inside the vector limit or not
	bool isValidIndex(ivector2 gemIndex);
private:
	bool checkGrid(GameBoard gameboard);
	//Search for possible matches only from top-left direction. Used while setting board as it's faster than normal
	bool checkTileFromTopLeft(int i, int j);
	//Print to console, for debugging reasons
	void printGrid(GameBoard board);
	GameBoard _gameBoard;
	std::mt19937 _eng;
	std::uniform_int_distribution<int> _dice;
	int _gridWidth, _gridHeight,_totalGemsTypes;
};

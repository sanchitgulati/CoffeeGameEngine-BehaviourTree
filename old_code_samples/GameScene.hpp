#pragma once
#include "../Coffee/Coffee.hpp"
#include "components/Gem.hpp"
#include "components/Grid.hpp"
#include "Direction.hpp"

using namespace Coffee;


class GameScene : public Scene
{
private:
	enum class GameState {
		IDLE,
		SELECTED,
		ANIMATION,
		GAME_OVER
	} _state;
public:
	static std::shared_ptr<GameScene> create(int rows, int column, int gemsType);
	void init(int row, int column, int gemsType);
	void cleanup() override;
private:
	int _mouseDownEventId;
	int _mouseUpEventId;

	int _mouseSwipeUpEventId;
	int _mouseSwipeDownEventId;
	int _mouseSwipeLeftEventId;
	int _mouseSwipeRightEventId;

	std::vector<std::string> _gemTypes;
	std::shared_ptr<Grid> _grid;
	std::shared_ptr<GameObject> _gridParent;
	std::shared_ptr<GameObject> _tileParent;

	std::vector<std::vector<std::shared_ptr<Gem>>> _gems;
	std::vector<std::vector<std::shared_ptr<GameObject>>> _tiles;
	std::vector<std::vector<int>> _movementMap;
	vector2 _spacer;
	ivector2 _currentGem;
	std::shared_ptr<Gem> _currentGemGO;
	Color _defaultColor;
	Color _highlightColor;

	//GameState _state;

	std::vector<std::shared_ptr<GameObject>> _validMoves;


	void onMouseDown(vector2 position);
	void onMouseUp(vector2 position);

	void onSwipeUp();
	void onSwipeDown();
	void onSwipeRight();
	void onSwipeLeft();

	void SwipeLogic(Direction direction);
	void initGem(int i, int j, float delay);


	void swap(ivector2 gem1, ivector2 gem2);

	void RemoveGemsFromBoard();
	void MoveGemsToNewPosition();
	void SpawnNewGems();
	void CheckForNewMatch();
	void checkForGemClick(vector2& position);
	void checkForMoreMatches();

};


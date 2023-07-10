#include "GameScene.hpp"
#include "GameOverScene.hpp"
#include "GameValues.hpp"


void GameScene::init(int row, int column, int gemsType)
{
	Scene::init();
	auto background = Sprite::createWithFile(GameValues::BG);
	background->setColor(255, 255, 255);
	background->setPosition(WIN_WIDTH / 2, WIN_HEIGHT / 2);
	background->setScale(1.f);
	addChild(background);

	_currentGem = { -1,-1 };
	_currentGemGO = nullptr;
	_state = GameState::IDLE;

	_defaultColor = { 30,30,30 };
	_highlightColor = { 30,255,30 };
	_validMoves = std::vector<std::shared_ptr<GameObject>>();


	// Manual data entry 
	// to optimize
	_spacer = { 64.f,72.f };
	auto grid_posx = (WIN_WIDTH / 2.f) - ((column - 1) * _spacer.x) / 2.f;
	auto grid_posy = (WIN_HEIGHT / 2.f) - ((row - 1) * _spacer.y) / 2.f;

	_tileParent = GameObject::create();
	_tileParent->setPosition(grid_posx, grid_posy);
	addChild(_tileParent);



	srand(static_cast<unsigned int>(time(NULL)));
	_gridParent = GameObject::create();
	_gridParent->setPosition(grid_posx, grid_posy);
	addChild(_gridParent);
	_grid = Grid::createWithSizeAndType(row, column, gemsType, rand());

	auto h = _grid->getHeight();
	auto w = _grid->getWidth();

	_gems.resize(h);
	for (int i = 0; i < h; i++) {
		_gems[i].resize(w, nullptr);
	}
	_tiles.resize(h);
	for (int i = 0; i < h; i++) {
		_tiles[i].resize(w, nullptr);
	}
	_gemTypes = GameValues::GEMS_FILE_PATH;



	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			auto tile = Sprite::createWithFile(GameValues::TILE_BG);
			tile->setColor(255, 255, 255);
			tile->setPosition(j * _spacer.x, i * _spacer.y);
			tile->setColor(_defaultColor);
			_tiles[i][j] = tile;
			_tileParent->addChild(tile);
		}
	}

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {

			float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			//r = r / 2.0f;

			r = (_grid->getHeight() - i) * 0.1f + r * 0.09f;
			initGem(i, j, r);
		}
	}


	_mouseDownEventId = Event.subscribe<void(vector2)>(SystemEvents::ON_MOUSE_DOWN, std::bind(&GameScene::onMouseDown, this, std::placeholders::_1));
	_mouseUpEventId = Event.subscribe<void(vector2)>(SystemEvents::ON_MOUSE_UP, std::bind(&GameScene::onMouseUp, this, std::placeholders::_1));

	_mouseSwipeUpEventId = Event.subscribe<void()>(SystemEvents::ON_MOUSE_SWIPE_UP, std::bind(&GameScene::onSwipeUp, this));
	_mouseSwipeDownEventId = Event.subscribe<void()>(SystemEvents::ON_MOUSE_SWIPE_DOWN, std::bind(&GameScene::onSwipeDown, this));
	_mouseSwipeLeftEventId = Event.subscribe<void()>(SystemEvents::ON_MOUSE_SWIPE_LEFT, std::bind(&GameScene::onSwipeLeft, this));
	_mouseSwipeRightEventId = Event.subscribe<void()>(SystemEvents::ON_MOUSE_SWIPE_RIGHT, std::bind(&GameScene::onSwipeRight, this));

}

std::shared_ptr<GameScene> GameScene::create(int rows, int column, int gemsType)
{
	auto scene = std::make_shared<GameScene>();
	scene->init(rows, column, gemsType);
	return scene;
}

void GameScene::cleanup()
{
	Event.unsubscribe<void(vector2)>(SystemEvents::ON_MOUSE_DOWN, _mouseDownEventId);
	Event.unsubscribe<void(vector2)>(SystemEvents::ON_MOUSE_UP, _mouseUpEventId);


	Event.unsubscribe<void()>(SystemEvents::ON_MOUSE_SWIPE_UP, _mouseSwipeUpEventId);
	Event.unsubscribe<void()>(SystemEvents::ON_MOUSE_SWIPE_DOWN, _mouseSwipeDownEventId);
	Event.unsubscribe<void()>(SystemEvents::ON_MOUSE_SWIPE_LEFT, _mouseSwipeLeftEventId);
	Event.unsubscribe<void()>(SystemEvents::ON_MOUSE_SWIPE_RIGHT, _mouseSwipeRightEventId);
}

void GameScene::onMouseDown(vector2 position)
{
	switch (_state)
	{
	case GameScene::GameState::IDLE:
		checkForGemClick(position);
		break;
	default:
		break;
	}
}

void GameScene::onMouseUp(vector2 position)
{
	if (_state != GameState::ANIMATION)
		_state = GameState::IDLE;
	if (_currentGemGO == nullptr)
		return;
	_currentGemGO->normal();
	_currentGemGO = nullptr;
}

void GameScene::onSwipeUp()
{
	SwipeLogic(Direction::UP);
}

void GameScene::onSwipeDown()
{
	SwipeLogic(Direction::DOWN);
}

void GameScene::onSwipeRight()
{
	SwipeLogic(Direction::RIGHT);
}

void GameScene::onSwipeLeft()
{
	SwipeLogic(Direction::LEFT);
}

void GameScene::SwipeLogic(Direction direction)
{
	ivector2 swapgem{ 0,0 };
	switch (direction)
	{
	case Direction::UP:
		swapgem.x = -1;
		break;
	case Direction::DOWN:
		swapgem.x = 1;
		break;
	case Direction::RIGHT:
		swapgem.y = 1;
		break;
	case Direction::LEFT:
		swapgem.y = -1;
		break;
	default:
		break;
	}
	auto gem2 = _currentGem + swapgem;
	switch (_state)
	{
	case GameScene::GameState::SELECTED:
		if (_grid->isValidIndex(gem2))
			if (_grid->canSwap(_currentGem, gem2))
				swap(_currentGem, gem2);
			else
				_currentGemGO->shake(Direction::UP);
		break;
	default:
		break;
	}
}


void GameScene::swap(ivector2 gem1, ivector2 gem2)
{
	_state = GameState::ANIMATION;
	AudioManager.playAudio(GameValues::sfxSLIDE);
	_movementMap = _grid->swap(gem1, gem2);

	auto pos1 = vector2(_gems[gem1.x][gem1.y]->getPosition());
	auto pos2 = vector2(_gems[gem2.x][gem2.y]->getPosition());
	_gems[gem1.x][gem1.y]->moveTo(pos1, pos2);
	_gems[gem2.x][gem2.y]->moveTo(pos2, pos1, [this]() {RemoveGemsFromBoard(); });

	auto temp = _gems[gem1.x][gem1.y];
	_gems[gem1.x][gem1.y] = _gems[gem2.x][gem2.y];
	_gems[gem2.x][gem2.y] = temp;

}

void GameScene::RemoveGemsFromBoard()
{
	for (int i = 0; i < _grid->getHeight(); i++) {
		for (int j = 0; j < _grid->getWidth(); j++) {
			if (_movementMap[i][j] == -1) { // to be removed from the grid
				_gems[i][j]->removeWithAnim(_gridParent);
				_gems[i][j] = nullptr;
			}
		}
	}
	_gridParent->makeSequence()->add(std::make_shared<Delay>(0.21f))->add(std::make_shared<FuncCall>([this]() {MoveGemsToNewPosition(); }));
}


void GameScene::MoveGemsToNewPosition()
{

	for (int j = 0; j < _grid->getWidth(); j++) {
		for (int i = _grid->getHeight() - 1; i >= 0; i--) {
			if (_movementMap[i][j] > 0) {

				auto g = _gems[i][j];
				_gems[i][j] = nullptr;
				_gems[i + _movementMap[i][j]][j] = g;

				auto pos1 = g->getPosition();
				auto pos2 = vector2(pos1.x, pos1.y + _spacer.y * _movementMap[i][j]);

				g->moveTo(pos1, pos2);

			}
		}
	}
	_gridParent->makeSequence()->add(std::make_shared<FuncCall>([this]() {SpawnNewGems(); }));
}

void GameScene::SpawnNewGems()
{
	for (int i = 0; i < _grid->getHeight(); i++) {
		for (int j = 0; j < _grid->getWidth(); j++) {
			if (_gems[i][j] == nullptr) {
				float r = (_grid->getHeight() - i) * 0.10f + j * 0.05f;

				initGem(i, j, r);
			}
		}
	}
	_gridParent->makeSequence()->add(std::make_shared<Delay>(.75f))->add(std::make_shared<FuncCall>([this]() {CheckForNewMatch(); }));
}

void GameScene::CheckForNewMatch()
{
	if (!_grid->isPossibleMoves()) {
		_state = GameState::GAME_OVER;

		_gridParent->makeSequence()->add(DELAY(3.0f))->add(FUNC_CALL([]() {
			Event.dispatch<void(std::shared_ptr<Scene>)>(SystemEvents::CHANGE_SCENE, GameOverScene::create());
		}));
	}
	else {
		checkForMoreMatches();
	}
}


void GameScene::checkForGemClick(vector2& position)
{
	for (int i = 0; i < _grid->getHeight(); i++) {
		for (int j = 0; j < _grid->getWidth(); j++) {
			if (_gems[i][j]->isIntersecting(position))
			{
				_currentGemGO = _gems[i][j];
				_currentGemGO->selected();
				_currentGem = { i,j };
				_state = GameState::SELECTED;
				return;
			}
		}
	}

}



void GameScene::initGem(int i, int j, float delay = 0.0f) {
	auto gem = Gem::createWithFile(_gemTypes[_grid->getGemAt(i, j)]);
	gem->setType(_grid->getGemAt(i, j));
	gem->setPosition(j * _spacer.x, i * _spacer.y);
	_gems[i][j] = gem;
	_gridParent->addChild(gem);
	gem->pop(delay);
}

void GameScene::checkForMoreMatches()
{
	ivector2 index = _grid->getNextMatch();
	if (index.x > -1 && index.y > -1) {
		_movementMap = _grid->processBoard(index);
		_gridParent->makeSequence()->add(std::make_shared<Delay>(0.1f))->add(std::make_shared<FuncCall>([this]() {RemoveGemsFromBoard(); _state = GameState::IDLE; }));
	}
	else {
		_state = GameState::IDLE;
	}
	return;
}

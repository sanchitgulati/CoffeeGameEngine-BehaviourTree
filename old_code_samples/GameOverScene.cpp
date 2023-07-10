#include "GameOverScene.hpp"
#include "MainMenu.hpp"
#include "GameValues.hpp"

void GameOverScene::init()
{
	Scene::init();
	AudioManager.stopMusic(2.f);
	auto background = Sprite::createWithFile(GameValues::BG);
	background->setColor(255, 255, 255);
	background->setPosition(WIN_WIDTH / 2, WIN_HEIGHT / 2);
	background->setScale(1.f);
	addChild(background);

	auto gameOver = Sprite::createWithFile(GameValues::GAME_OVER_OVERLAY);
	gameOver->setPosition(WIN_WIDTH / 2, -1 * WIN_HEIGHT / 2);
	gameOver->makeSequence()
		->add(MOVE_TO(gameOver, gameOver->getPosition(), vector2(WIN_WIDTH / 2, WIN_HEIGHT / 2), 0.7f, std::vector<float>({ 0.22f, 1.f, 0.36f, 1.f })));
	addChild(gameOver);

	auto button = Button::createWithFile(GameValues::BTN,GameValues::BTN_PRESSED);
	button->setCallback([]() {
		Event.dispatch<void(std::shared_ptr<Scene>)>(SystemEvents::CHANGE_SCENE, std::make_shared<MainMenu>());
		});
	button->setPosition(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.7f);
	button->setScale(1.f);
	addChild(button);

	auto label = Label::createWithText("Restart", GameValues::FONT, 24);
	button->addChild(label);

}

std::shared_ptr<GameOverScene> GameOverScene::create()
{
	auto scene = std::make_shared<GameOverScene>();
	scene->init();
	return scene;
}

void GameOverScene::cleanup()
{
}

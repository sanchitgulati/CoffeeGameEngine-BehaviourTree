#include "MainMenu.hpp"
#include "GameScene.hpp"
#include "GameValues.hpp"

void MainMenu::init()
{
	Scene::init();
	AudioManager.playMusic(GameValues::MUSIC);
	auto background = Sprite::createWithFile(GameValues::BG);
	background->setPosition(WIN_WIDTH *0.5f, WIN_HEIGHT * 0.5f);
	addChild(background);


	{
		auto button = Button::createWithFile(GameValues::BTN,GameValues::BTN_PRESSED);
		button->setCallback([]() {
			Event.dispatch<void(std::shared_ptr<Scene>)>(SystemEvents::CHANGE_SCENE, GameScene::create(4,7,4));
			});
		button->setPosition(WIN_WIDTH * 0.58f, WIN_HEIGHT * 0.60f);
		button->setScale(1.f);
		addChild(button);

		auto label = Label::createWithText("Play - Easy", GameValues::FONT, 24);
		button->addChild(label);
	}
	{
		auto button = Button::createWithFile(GameValues::BTN, GameValues::BTN_PRESSED);
		button->setCallback([]() {
			Event.dispatch<void(std::shared_ptr<Scene>)>(SystemEvents::CHANGE_SCENE, GameScene::create(5, 8, 7));
			});
		button->setPosition(WIN_WIDTH * 0.58f, WIN_HEIGHT * 0.75f);
		button->setScale(1.f);
		addChild(button);

		auto label = Label::createWithText("Play - Medium", GameValues::FONT, 24);
		button->addChild(label);
	}
	{
		auto button = Button::createWithFile(GameValues::BTN, GameValues::BTN_PRESSED);
		button->setCallback([]() {
			Event.dispatch<void(std::shared_ptr<Scene>)>(SystemEvents::CHANGE_SCENE, GameScene::create(7, 10, 10));
			});
		button->setPosition(WIN_WIDTH * 0.58f, WIN_HEIGHT * 0.90f);
		button->setScale(1.f);
		addChild(button);

		auto label = Label::createWithText("Play - Hard",GameValues::FONT, 24);
		button->addChild(label);
	}

}

std::shared_ptr<MainMenu> MainMenu::create()
{
	auto scene = std::make_shared<MainMenu>();
	scene->init();
	return scene;
}

void MainMenu::cleanup()
{
}

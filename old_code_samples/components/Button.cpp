#include "Button.hpp"
#include "../GameValues.hpp"

namespace Coffee {
	std::shared_ptr<Button> Button::createWithFile(const std::string& filePath, const std::string& filepathPressed)
	{
		auto button = std::make_shared<Button>();
		button->initButton(filePath, filepathPressed);
		button->GameObject::init();
		return button;
	}

	void Button::setCallback(std::function<void()> func)
	{
		_callback = func;
	}

	void Button::initButton(const std::string& filepath, const std::string& filepathPressed)
	{
		_normalState = Sprite::createWithFile(filepath);
		_pressedState = Sprite::createWithFile(filepathPressed);
		_pressedState->setVisible(false);
		addChild(_normalState);
		addChild(_pressedState);
		auto _mouseDownEventId = Event.subscribe<void(vector2)>(SystemEvents::ON_MOUSE_DOWN, std::bind(&Button::onMouseDown, this, std::placeholders::_1));
	}

	void Button::onMouseDown(vector2 position) {
		auto hit = _normalState->isIntersecting(position);
		if (hit) {
			makeSequence()
				->add(SCALE_TO(shared_from_this(), 1.f, 0.9f, 0.1f))
				->add(FUNC_CALL([this]() {
				AudioManager.playAudio(GameValues::sfxCLICK);
				_pressedState->setVisible(true); }))
				->add(SCALE_TO(shared_from_this(), 0.9f, 1.1f, 0.1f))
					->add(SCALE_TO(shared_from_this(), 1.1f, 1.f, 0.1f))
					->add(DELAY(.5f))
					->add(FUNC_CALL([this]() {
					std::invoke(_callback);
				}));
		}
	}


}
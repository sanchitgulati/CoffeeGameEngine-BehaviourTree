#pragma once

#include <functional>
#include <memory>
#include "../../Coffee/Coffee.hpp"

namespace Coffee {
	class Button : public GameObject
	{
	public:
		static std::shared_ptr<Button> createWithFile(const std::string& filePathDefault, const std::string& filepathPressed);
		void setCallback(std::function<void()> func);

	private:
		std::function<void()> _callback;
		std::shared_ptr<Sprite> _normalState;
		std::shared_ptr<Sprite> _pressedState;
		void initButton(const std::string &filepath, const std::string& filepathPressed);
		void onMouseDown(vector2 position);
	};
}


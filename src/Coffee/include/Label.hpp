#pragma once
#include "Sprite.hpp"
#include <string>
#include <SDL.h>
#include <SDL_opengl.h>

namespace Coffee {

	class Label : public Sprite
	{
	public:
		void setText(const std::string& text);
		void initWithText(const std::string& text, const std::string& fontFilePath, const int& fontSize);
		static std::shared_ptr<Label> createWithText(const std::string& text, const std::string& fontFilePath, const int& fontSize);
	private:
		void createTexture();
		std::string _text;
		std::string _fontFilePath;
		int _fontSize;
	};
}
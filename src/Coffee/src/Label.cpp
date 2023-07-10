#include "../include/TextureManager.hpp"
#include "../include/Label.hpp"

namespace Coffee {

	void Label::initWithText(const std::string& text, const std::string& fontFilePath, const int& fontSize) {
		_shader = std::make_unique<Shader>(_defaultVertexShaderFileName, _defaultFragmentShaderFileName, true);
		_text = text;
		_fontFilePath = fontFilePath;
		_fontSize = fontSize;
		createTexture();
	}


	void Label::createTexture() {
		int w, h;
		_glTexture = TextureManager.getFontTexture(_text, _fontFilePath, _fontSize, w, h);
		_size = vector2(w, h);
	}


	std::shared_ptr<Label> Label::createWithText(const std::string& text, const std::string& fontFilePath, const int& fontSize) {

		auto label = std::make_shared<Label>();
		label->initWithText(text, fontFilePath, fontSize);
		label->init();
		return label;
	}

	void Label::setText(const std::string& text) {
		_text = text;
		createTexture();
	}
}
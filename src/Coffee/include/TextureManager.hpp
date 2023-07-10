#pragma once
#define GL_GLEXT_PROTOTYPES
#include "GL/glew.h"
#include "../preprocessor/Common.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_opengl_glext.h>
#include <map>
#include <string>
#include <SDL_image.h>
#include "Vector.hpp"

namespace Coffee {
	struct texInfo { int gl; int width; int height; };
	class TextureManager_
	{
	private:
		std::map<std::string, texInfo> _map;
		int surfaceToGLTexture(SDL_Surface* surface, int& width, int& height);
		texInfo checkMap(std::string key);
	public:
		int getTexture(const std::string& filepath, int& width, int& height);
		int getFontTexture(const std::string& text, const std::string& filepath, int& fontSize, int& width, int& height);
	private:
		COFFEE_MAKE_SINGLETON(TextureManager_);
	};
}

#define TextureManager TextureManager_::getInstance()


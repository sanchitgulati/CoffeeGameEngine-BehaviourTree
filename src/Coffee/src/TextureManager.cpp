#include "../include/TextureManager.hpp"
#include <SDL_ttf.h>

namespace Coffee {
	int TextureManager_::surfaceToGLTexture(SDL_Surface* surface, int& width, int& height)
	{
		GLuint glTexture = 0;
		if (surface == NULL)
		{
			printf("Unable to load image ! SDL_image Error: %s\n", IMG_GetError());
		}
		else
		{
			int Mode = GL_RGB;
			if (surface->format->BytesPerPixel == 4) {
				Mode = GL_RGBA;
			}
			glGenTextures(1, &glTexture);
			glBindTexture(GL_TEXTURE_2D, glTexture);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, Mode, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
			glGenerateMipmap(GL_TEXTURE_2D);

			width = surface->w;
			height = surface->h;

		}
		return glTexture;
	}

	texInfo TextureManager_::checkMap(std::string key)
	{
		if (_map.find(key) != _map.end()) {
			return _map[key];
		}
		return texInfo { 0, 1, 1 };
	}

	int TextureManager_::getTexture(const std::string& filepath, int& width, int& height)
	{
		auto data = checkMap(filepath);
		if (data.gl > 0) {
			width = data.width;
			height = data.height;
			return data.gl;
		}


		SDL_Texture* newTexture = NULL;
		SDL_Surface* surface = IMG_Load(filepath.c_str());
		//SDL_InvertSurface(loadedSurface);
		int glTexture = surfaceToGLTexture(surface, width, height);
		_map[filepath] = texInfo{ glTexture,width,height };
		SDL_FreeSurface(surface);
		return glTexture;
	}

	int TextureManager_::getFontTexture(const std::string& text, const std::string& filepath, int& fontSize, int& width, int& height)
	{

		auto data = checkMap(filepath + text);
		if (data.gl > 0) {
			width = data.width;
			height = data.height;
			return data.gl;
		}


		auto font = TTF_OpenFont(filepath.c_str(), fontSize);
		auto surface = TTF_RenderText_Blended(font, text.c_str(), { 255,255,255 });
		int glTexture = surfaceToGLTexture(surface, width, height);
		if(glTexture > 0)
			_map[filepath + text] = texInfo{ glTexture,width,height };
		SDL_FreeSurface(surface);
		return glTexture;
	}



}
#pragma once
#include <SDL.h>
#include <memory>

namespace Coffee {
	int invert_image(int pitch, int height, void* image_pixels);
	int SDL_InvertSurface(SDL_Surface* image);

}

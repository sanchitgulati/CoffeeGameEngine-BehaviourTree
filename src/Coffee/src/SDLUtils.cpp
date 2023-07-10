#include "../include/SDLUtils.hpp"

namespace Coffee {
	int invert_image(int pitch, int height, void* image_pixels)
	{
		int index;
		void* temp_row;
		int height_div_2;

		temp_row = (void*)malloc(pitch);
		if (NULL == temp_row)
		{
			SDL_SetError("Not enough memory for image inversion");
			return -1;
		}
		//if height is odd, don't need to swap middle row
		height_div_2 = (int)(height * .5);
		for (index = 0; index < height_div_2; index++) {
			//uses string.h
			memcpy((Uint8*)temp_row,
				(Uint8*)(image_pixels)+
				pitch * index,
				pitch);

			memcpy(
				(Uint8*)(image_pixels)+
				pitch * index,
				(Uint8*)(image_pixels)+
				pitch * (height - index - 1),
				pitch);
			memcpy(
				(Uint8*)(image_pixels)+
				pitch * (height - index - 1),
				temp_row,
				pitch);
		}
		free(temp_row);
		return 0;
	}

	//This is the function you want to call!
	int SDL_InvertSurface(SDL_Surface* image)
	{
		if (NULL == image)
		{
			SDL_SetError("Surface is NULL");
			return -1;
		}
		return(invert_image(image->pitch, image->h,
			image->pixels));
	}

}

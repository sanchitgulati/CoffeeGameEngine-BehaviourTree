#pragma once
#include <SDL_timer.h>

namespace Coffee {
	class Time
	{
	public:
		static int32_t GetTicks() { return SDL_GetTicks(); }
		
	private:

	};
}

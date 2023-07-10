#pragma once

#include<GL/glew.h>
#include<SDL.h>
#include<SDL_opengl.h>
#include<string>
#include<memory>
#include<SDL_image.h>

namespace Coffee {
	class Window {
	public:
		int init(const std::string& title, const int& width, const int& height);
		int getWindowId();
		void setDisplayWindow(int windowId);
		void preRender();
		void postRender();
	private:
		void gl_init();
		int _width = 0, _height = 0;
		SDL_Window* _window;
		SDL_GLContext _glContext;
	};
}

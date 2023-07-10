#include "../include/Window.hpp"
#include <SDL_ttf.h>

namespace Coffee {
	int Window::init(const std::string& title, const int& width, const int& height) {

        this->_width = width;
        this->_height = height;
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
			SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		}
        bool success = true;
		_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
		_glContext = SDL_GL_CreateContext(_window);

        if (_window == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }

		//Initialize PNG loading
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
			success = false;
		}

        GLenum err = glewInit();
        if (GLEW_OK != err)
        {
            printf("Failed to initialize GLEW\n");
        }
        printf("Using GLEW Version: %s",glewGetString(GLEW_VERSION));

        if (TTF_Init() < 0) {
            printf("Failed to initialize TTF (%s)\n",TTF_GetError());
        }
        gl_init();
        return success;
	}

	int Window::getWindowId()
	{
		return SDL_GetWindowDisplayIndex(_window);
	}

    void Window::setDisplayWindow(int windowId)
    {
        //Get number of displays
        auto gTotalDisplays = SDL_GetNumVideoDisplays();
        if (gTotalDisplays < 2)
        {
            printf("\nWarning: Only one display connected!\n");
            windowId = 0;
        }
        //Get bounds of each display
        auto gDisplayBounds = new SDL_Rect[gTotalDisplays];
        for (int i = 0; i < gTotalDisplays; ++i)
        {
            SDL_GetDisplayBounds(i, &gDisplayBounds[i]);
        }
        auto w = gDisplayBounds[windowId].x + (gDisplayBounds[windowId].w - _width) / 2;
        auto h = gDisplayBounds[windowId].y + (gDisplayBounds[windowId].h - _height) / 2;

        SDL_SetWindowPosition(_window, gDisplayBounds[windowId].x + (gDisplayBounds[windowId].w - _width) / 2, gDisplayBounds[windowId].y + (gDisplayBounds[windowId].h - _height) / 2);
    }

    void Window::gl_init() {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void Window::preRender()
    {
        glClearColor(0.2f, 0.25f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT); // Clean the screen
        glLoadIdentity();
    }


    void Window::postRender()
    {
        SDL_GL_SwapWindow(_window);
    }

}
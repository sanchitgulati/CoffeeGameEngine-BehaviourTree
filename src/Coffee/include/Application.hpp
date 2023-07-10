#pragma once
#include <SDL.h>
#include <memory>
#include "Window.hpp"
#include "SceneManager.hpp"
#include "Scene.hpp"
#include "Event.hpp"
#include "Camera.hpp"
#include "PlayerPrefs.hpp"
#include <string>
#include "../include/AudioManager.hpp"
#include "Vector.hpp"


#define DEFAULT_SAVE_FILE "save.txt"
#define DEAFULT_TOTAL_CHANNELS 8
#define DEFAULT_SWIPE_THRESHOLD 50


namespace Coffee {

	class Application
	{
	public:
		void Init(const std::string& company_name, const std::string& app_name, const int& width, const int& height);
		void GameLoop();
		void GameCleanup();
		std::shared_ptr<SceneManager> GetSceneManager();
		~Application();
		bool running;

	private:
		std::string _company_name;

		bool _isPressed;
		vector2 _mouseDownPosition; // optimize this //maybe a class

		int _swipeThreshold;
		std::string _app_name;
		Window _window;
		int mWindowID;
		int _WindowDisplayID;
		std::shared_ptr<SceneManager> _sceneManager;
		void handleWindowEvent(SDL_Event& e);
		std::unique_ptr<Camera> _2DCamera;
	};

}
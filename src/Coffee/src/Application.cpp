#include "../include/Application.hpp"
#include <math.h>

namespace Coffee {

	void Application::Init(const std::string& company_name, const std::string& title, const int& width, const int& height)
	{
        _company_name = company_name;
        _app_name = _app_name;
		char* base_path = SDL_GetPrefPath(company_name.c_str(), _app_name.c_str());
		PlayerPrefs.read(std::string(base_path) + DEFAULT_SAVE_FILE);
        auto screenId = PlayerPrefs.getValue("mWindowDisplayID", "0");

		_window = Window();
		_window.init(title, width, height);
        _window.setDisplayWindow(std::stoi(screenId));
		_sceneManager = std::shared_ptr<SceneManager>();
        _sceneManager->init();
		running = true;
		_2DCamera = std::make_unique<Camera>();
		_2DCamera->setCamera(glm::ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 10.0f));
        AudioManager.init(DEAFULT_TOTAL_CHANNELS);
        _swipeThreshold = DEFAULT_SWIPE_THRESHOLD;
	}

	void Application::GameLoop() {
		while (running) {

			SDL_Event event;
			while (SDL_PollEvent(&event)) {
                handleWindowEvent(event);
				switch (event.type)
				{
				case SDL_QUIT:
					running = false;
					break;
                case SDL_MOUSEBUTTONDOWN:
                    _isPressed = true;
                    _mouseDownPosition = vector2(event.button.x, event.button.y);
                    Event.dispatch<void(vector2)>(SystemEvents::ON_MOUSE_DOWN, vector2(event.button.x, event.button.y));
                    break;
                case SDL_MOUSEBUTTONUP:
                    _isPressed = false;
                    Event.dispatch<void(vector2)>(SystemEvents::ON_MOUSE_UP, vector2(event.button.x, event.button.y));
                    break;
                case SDL_MOUSEMOTION:
                    if (_isPressed) {
                        if (_mouseDownPosition.x - event.button.x > _swipeThreshold&& std::fabs(_mouseDownPosition.y - event.button.y) < _swipeThreshold)
                        {
                            Event.dispatch<void()>(SystemEvents::ON_MOUSE_SWIPE_LEFT);
                            _isPressed = false;
                        }
                        if (_mouseDownPosition.x - event.button.x < -_swipeThreshold && std::fabs(_mouseDownPosition.y - event.button.y) < _swipeThreshold)
                        {
                            Event.dispatch<void()>(SystemEvents::ON_MOUSE_SWIPE_RIGHT);
                            _isPressed = false;
                        }
                        if (_mouseDownPosition.y - event.button.y > _swipeThreshold&& std::fabs(_mouseDownPosition.x - event.button.x) < _swipeThreshold)
                        {
                            Event.dispatch<void()>(SystemEvents::ON_MOUSE_SWIPE_UP);
                            _isPressed = false;
                        }
                        if (_mouseDownPosition.y - event.button.y < -_swipeThreshold && std::fabs(_mouseDownPosition.x - event.button.x) < _swipeThreshold)
                        {
                            Event.dispatch<void()>(SystemEvents::ON_MOUSE_SWIPE_DOWN);
                            _isPressed = false;
                        }

                    }
                    Event.dispatch<void(vector2)>(SystemEvents::ON_MOUSE_MOVE, vector2(event.button.x, event.button.y));
                    break;
				default:
					break;
				}
			}
			_window.preRender();
            _sceneManager->getScene()->draw(_2DCamera->getCamera());
            _sceneManager->getScene()->update(static_cast<float>(Time::GetTicks()));
			_window.postRender();
		}
	}

    void Application::GameCleanup()
    {
        char* base_path = SDL_GetPrefPath(_company_name.c_str(), _app_name.c_str());
        PlayerPrefs.write(std::string(base_path) + DEFAULT_SAVE_FILE);
        _sceneManager->getScene()->cleanup();
        AudioManager.cleanup();
    }

    void Application::handleWindowEvent(SDL_Event& e)
    {
        //Caption update flag
        bool updateCaption = false;

        //If an event was detected for this window
        if (e.type == SDL_WINDOWEVENT )
        {
            switch (e.window.event)
            {
                //Window moved
            case SDL_WINDOWEVENT_MOVED:
                _WindowDisplayID = _window.getWindowId();
                PlayerPrefs.setValue("mWindowDisplayID", std::to_string(_WindowDisplayID));
                break;

                //Window appeared
            case SDL_WINDOWEVENT_SHOWN:
                break;

                //Window disappeared
            case SDL_WINDOWEVENT_HIDDEN:
                break;

                //Get new dimensions and repaint
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                break;

                //Repaint on expose
            case SDL_WINDOWEVENT_EXPOSED:
                break;

                //Mouse enter
            case SDL_WINDOWEVENT_ENTER:
                break;

                //Mouse exit
            case SDL_WINDOWEVENT_LEAVE:
                break;

                //Keyboard focus gained
            case SDL_WINDOWEVENT_FOCUS_GAINED:
                break;

                //Keyboard focus lost
            case SDL_WINDOWEVENT_FOCUS_LOST:
                break;

                //Window minimized
            case SDL_WINDOWEVENT_MINIMIZED:
                break;

                //Window maxized
            case SDL_WINDOWEVENT_MAXIMIZED:
                break;

                //Window restored
            case SDL_WINDOWEVENT_RESTORED:
                break;

                //Hide on close
            case SDL_WINDOWEVENT_CLOSE:
                break;
            }
        }
    }

	std::shared_ptr<SceneManager> Application::GetSceneManager()
	{
		return _sceneManager;
	}

	Application::~Application()
	{
		SDL_Quit();
		exit(0);
	}

}

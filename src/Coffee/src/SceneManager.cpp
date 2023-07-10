#include "../include/SceneManager.hpp"

namespace Coffee {
	std::shared_ptr<Scene> SceneManager::_currentScene;

	void SceneManager::init()
	{
		auto _sceneEvent = Event.subscribe<void(std::shared_ptr<Scene>)>(SystemEvents::CHANGE_SCENE, std::bind(&SceneManager::setScene, this, std::placeholders::_1));
	}

	void SceneManager::setScene(std::shared_ptr<Scene> scene)
	{
		if(_currentScene != nullptr)
			_currentScene->cleanup();
		_currentScene = scene;
	}

	std::shared_ptr<Scene> SceneManager::getScene()
	{
		return _currentScene;
	}

	void SceneManager::update(float dt)
	{
		if (_currentScene != nullptr)
			_currentScene->update(dt);
	}
}
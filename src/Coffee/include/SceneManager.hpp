#pragma once
#include "Scene.hpp"
#include <memory>
#include "Event.hpp"

namespace Coffee {
	class SceneManager
	{
	public:
		void init();
		void setScene(std::shared_ptr<Scene> scene);
		std::shared_ptr<Scene> getScene();
		void update(float dt);
	private:
		static std::shared_ptr<Scene> _currentScene;
		void ChangeSceneEventListener(std::unique_ptr<Scene> scene);
	};
}
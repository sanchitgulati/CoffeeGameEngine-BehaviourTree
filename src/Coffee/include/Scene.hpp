#pragma once
#include <string>
#include <vector>
#include "GameObject.hpp"
#include "Sprite.hpp"

namespace Coffee {
	class Scene
	{
	public:
		static std::shared_ptr<Scene> create();
		void virtual update(float dt);
		void virtual init();
		void virtual draw(matrix4 projection);
		void addChild(std::shared_ptr<GameObject> gameObject);
		void virtual cleanup();
	private:
		std::string _sceneName;
		std::shared_ptr<GameObject> _parent;
	};
}
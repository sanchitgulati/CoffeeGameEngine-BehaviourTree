#include "../include/Scene.hpp"


namespace Coffee {
	void Scene::init()
	{
		_sceneName = "Scene";
		_parent = GameObject::create();
	}

	std::shared_ptr<Scene> Scene::create()
	{
		return std::shared_ptr<Scene>();
	}

	void Scene::update(float dt)
	{
		for (auto c : _parent->getChildren()) {
			c->update(dt);
		}
	}

	void Scene::draw(glm::mat4 projection)
	{
		for (auto c : _parent->getChildren()) {
			c->draw(projection);
		}
	}

	void Scene::addChild(std::shared_ptr<GameObject> gameObject)
	{
		_parent->addChild(gameObject);
	}

	void Scene::cleanup() {
		_parent->removeChildren();
	}
}
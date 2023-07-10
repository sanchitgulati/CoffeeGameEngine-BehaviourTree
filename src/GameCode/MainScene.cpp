#include "MainScene.hpp"
#include "Resources.hpp"
#include "systems/World.hpp"
#include "entities/Genus.hpp"
#include <iostream>
#include <random>

void MainScene::init()
{
	Scene::init();

	auto world = World::create();
	addChild(world);
	float birth = .8f;
	float death = .02f;
	float replication = .00f;
	world->setup(birth, death, replication);
}

std::shared_ptr<MainScene> MainScene::create()
{
	auto scene = std::make_shared<MainScene>();
	scene->init();
	return scene;
}
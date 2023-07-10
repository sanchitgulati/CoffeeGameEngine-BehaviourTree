#pragma once
#include "../MainScene.hpp"
#include "../../Coffee/Coffee.hpp"

using namespace Coffee;

class Genus : public Coffee::Sprite
{
public:
	static std::shared_ptr<Genus> createWithFile(const std::string &filePath, float replicationRate, float deathRate);
	void init(const std::string &filepath,float replicationRate, float deathRate);
	void update(float dt) override;
	bool _markedToDelete = false;
private:
	// Create the behavior tree
	std::shared_ptr<BehaviourTree::Root> _root;
	std::unique_ptr<Coffee::Random> _random;
	float _replicationRate;
	float _deathRate;

	void initBehaviourTree();

	bool replicate();
	bool eat();
	bool sleep();
	bool wander();
	bool idle();
	bool die();
	bool conditionDie();
	bool conditionReplication();
};

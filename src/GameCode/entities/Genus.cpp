#include "Genus.hpp"
using namespace Coffee;

std::shared_ptr<Genus> Genus::createWithFile(const std::string &filePath, float replicationRate, float deathRate)
{
	auto candy = std::make_shared<Genus>();
	candy->init(filePath, replicationRate, deathRate);
	candy->Sprite::init();
	return candy;
}

void Genus::init(const std::string &filepath, float replicationRate, float deathRate)
{
	_root = nullptr;
	_replicationRate = replicationRate;
	_deathRate = deathRate;
	_random = std::make_unique<Coffee::Random>();
	initWithFile(filepath);
	initBehaviourTree();
}

void Genus::update(float dt)
{
	if (_root != nullptr)
	{
		if (_root->execute() == BehaviourTree::Status::SUCCESS)
		{
			_root = nullptr;
		}
	}
}

bool Genus::replicate()
{
	Event.dispatch<void()>(SystemEvents::GENUS_REPLICATION);
	// Event.dispatch<void()>((SystemEvents)SystemEvents::GENUS_REPLICATION, shared_from_this());
	return true;
}

bool Genus::die()
{;
	Event.dispatch<void(std::shared_ptr<GameObject>)>(SystemEvents::GENUS_DIE,shared_from_this());
	return true;
}

bool Genus::eat()
{
	return true;
}

bool Genus::sleep()
{
	return true;
}

bool Genus::wander()
{
	return true;
}

bool Genus::idle()
{
	return true;
}

bool Genus::conditionDie()
{
	// Generate a random number between 0 and 1
	double randomNum = _random->rand();
	if (randomNum < _deathRate)
		return true;
	return false;
}

bool Genus::conditionReplication()
{
	// Generate a random number between 0 and 1
	double randomNum = _random->rand();
	if (randomNum < _replicationRate)
		return true;
	return false;
}

void Genus::initBehaviourTree()
{

	// Create the behavior tree
	_root = std::make_shared<BehaviourTree::Root>();

	// Create nodes for the behavior tree
	auto wait = std::make_shared<BehaviourTree::Wait>(.1);
	auto replicationAction = std::make_shared<BehaviourTree::Action>(std::bind(&Genus::replicate, this));
	auto dieAction = std::make_shared<BehaviourTree::Action>(std::bind(&Genus::die, this));

	auto conditionReplication = std::make_shared<BehaviourTree::Condition>(std::bind(&Genus::conditionReplication, this));
	conditionReplication->onTrue(replicationAction);

	auto conditionDie = std::make_shared<BehaviourTree::Condition>(std::bind(&Genus::conditionDie, this));
	conditionDie->onTrue(dieAction);

	auto sequenceConditional = std::make_shared<BehaviourTree::Sequence>();
	sequenceConditional->addChild(conditionDie);
	sequenceConditional->addChild(conditionReplication);

	auto sequence = std::make_shared<BehaviourTree::Sequence>();
	sequence->addChild(wait);
	sequence->addChild(sequenceConditional);

	auto repeater = std::make_shared<BehaviourTree::Repeater>(-1);
	repeater->setChild(sequence);
	_root->addChild(repeater);
}
#include "World.hpp"
#include "../entities/Genus.hpp"

using namespace Coffee;

std::shared_ptr<World> World::create()
{
    auto world = std::make_shared<World>();
    world->init();
    return world;
}

void World::init()
{
    GameObject::init();

    auto replicateId = Event.subscribe<void()>(SystemEvents::GENUS_REPLICATION, std::bind(&World::replicate, this));
    auto dieId = Event.subscribe<void(std::shared_ptr<GameObject>)>(SystemEvents::GENUS_DIE, std::bind(&World::die, this, std::placeholders::_1));

    _root = nullptr;
	_random = std::make_unique<Coffee::Random>();
    initBehaviourTree();
}

void World::setup(float birth, float death, float replication)
{
    _birth = birth;
    _death = death;
    _replication = replication;
    auto startingGenus = 10;
    for (size_t i = 0; i < startingGenus; i++)
    {
        replicate();
    }
    
}

void World::replicate()
{
    _count++;
    runningAverage();
    auto unit = Genus::createWithFile(Resources::GEMS_FILE_PATH[0], _replication,_death);
    unit->setPosition((float)(rand() % WIN_WIDTH), (float)(rand() % WIN_HEIGHT));
    unit->setScale(0.2f);
    getParent()->addChild(unit);
}

void World::die(std::shared_ptr<GameObject> genus)
{
    _count--;
    runningAverage();
    getParent()->removeChild(genus);
}

bool World::birth()
{
    replicate();
    return true;
}

bool World::conditionBirth()
{
	// Generate a random number between 0 and 1
	double randomNum = _random->rand();
	if (randomNum < _birth)
		return true;
	return false;
}

void World::initBehaviourTree()
{
    _root = std::make_shared<BehaviourTree::Root>();
    
	auto wait = std::make_shared<BehaviourTree::Wait>(.1f);
    
	auto conditionBirth = std::make_shared<BehaviourTree::Condition>(std::bind(&World::conditionBirth, this));
	auto birthAction = std::make_shared<BehaviourTree::Action>(std::bind(&World::birth, this));
	conditionBirth->onTrue(birthAction);

	auto sequence = std::make_shared<BehaviourTree::Sequence>();
	sequence->addChild(wait);
	sequence->addChild(conditionBirth);

	auto repeater = std::make_shared<BehaviourTree::Repeater>(-1);
	repeater->setChild(sequence);
	_root->addChild(repeater);
}

void World::runningAverage()
{
    _runningAverageTotal += _count;
    _runningAverageCount++;
    if (_runningAverageCount == 1000)
    {
        std::cout << "Running Average : " << _runningAverageTotal / _runningAverageCount << std::endl;
        _runningAverageTotal = 0;
        _runningAverageCount = 0;
    }
}

void World::update(float dt)
{
    GameObject::update(dt);
	if (_root != nullptr)
	{
		if (_root->execute() == BehaviourTree::Status::SUCCESS)
		{
			_root = nullptr;
		}
	}
}

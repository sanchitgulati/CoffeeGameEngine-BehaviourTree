#include "../../Coffee/Coffee.hpp"
#include "../Resources.hpp"
#include <memory>

using namespace Coffee;
class World : public Coffee::GameObject
{
public:
	static std::shared_ptr<World> create();
	void init();
	void setup(float birth, float death, float replication);
	void update(float dt) override;

private:
	int _count;
	std::unique_ptr<Coffee::Random> _random;
	std::shared_ptr<BehaviourTree::Root> _root;
	size_t _runningAverageTotal;
	size_t _runningAverageCount;
	float _birth;
	float _death;
	float _replication;
	std::shared_ptr<Label> _label;
	void replicate();
	void die(std::shared_ptr<GameObject> genus);
	bool birth();
	void initBehaviourTree();
	bool conditionBirth();
	
	void runningAverage();
};

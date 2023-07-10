#include "../include/Sequence.hpp"

namespace Coffee {
	void Sequence::init()
	{
		_actions = std::queue<std::shared_ptr<Action>>();
	}
	std::shared_ptr<Sequence> Sequence::add(std::shared_ptr<Action> action) {
		_actions.push(action);
		return shared_from_this();
	}

	void Sequence::execute() {
		if (!_actions.empty()) {
			if (_actions.front()->_isDone) {
				_actions.pop();
			}
			else {
				_actions.front()->execute();
			}
		}
	}

}
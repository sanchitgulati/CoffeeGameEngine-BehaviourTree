#pragma once
#include <memory>
#include <queue>
#include "../include/ActionSystem.hpp"

namespace Coffee {

	class Sequence : public std::enable_shared_from_this<Sequence>
	{
	public:
		void init();
		void execute();
		std::shared_ptr<Sequence> add(std::shared_ptr<Action> action);
	private:
		std::queue<std::shared_ptr<Action>> _actions;
	};
}

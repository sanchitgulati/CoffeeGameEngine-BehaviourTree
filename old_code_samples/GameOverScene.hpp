#pragma once
#include "../Coffee/Coffee.hpp"
#include "components/Button.hpp"

using namespace Coffee;
class GameOverScene : public Scene
{
public:
	static std::shared_ptr<GameOverScene> create();
	void init();
	void cleanup() override;
};


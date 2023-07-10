#pragma once
#include "../Coffee/Coffee.hpp"

using namespace Coffee;
class MainScene : public Scene
{
public:
	static std::shared_ptr<MainScene> create();
	void init();
};


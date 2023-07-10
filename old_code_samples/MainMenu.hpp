#pragma once
#include "../Coffee/Coffee.hpp"
#include "components/Button.hpp"

using namespace Coffee;
class MainMenu : public Scene
{
public:
	static std::shared_ptr<MainMenu> create();
	void init();
	void cleanup() override;
};


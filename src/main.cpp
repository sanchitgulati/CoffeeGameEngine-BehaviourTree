#include <stdio.h>
#include <iostream>
#include "Coffee/Coffee.hpp"
#include "GameCode/MainScene.hpp"


using namespace Coffee;
int main(int argc, char* args[])
{
	Application application;
	application.Init("Caffinism","Evolution", WIN_WIDTH, WIN_HEIGHT);
	application.GetSceneManager()->setScene(MainScene::create());
	application.GameLoop();
	application.GameCleanup();
	return 0;
}
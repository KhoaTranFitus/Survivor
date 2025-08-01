#include "VictoryScene.h"
#include "MenuScene.h"
#include "Button.h"
#include "SwitchSceneCommand.h"

VictoryScene::VictoryScene()
{
	auto button1 = std::make_shared<Button>(
		"Back to Menu", 500, 300, sf::Vector2f(200, 100),
		std::make_shared<SwitchSceneCommand>([]() {
			return std::make_shared<MenuScene>();
		})
	);
	buttons.push_back(button1);
}

VictoryScene::~VictoryScene()
{
}
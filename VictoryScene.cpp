#include "VictoryScene.h"
#include "MenuScene.h"
#include "Button.h"
#include "SwitchSceneCommand.h"
#include "MusicManager.h"
#include <SFML/Window.hpp>
sf::Font VictoryScene::font;
bool VictoryScene::fontLoaded = false;

VictoryScene::VictoryScene()
{
	MusicManager::getInstance().play("./Assets/music/victory_scene.mp3", 40.f, true);
	auto button1 = std::make_shared<Button>(
		"Back to Menu","type1", 500, 300, sf::Vector2f(200, 100),
		std::make_shared<SwitchSceneCommand>([]() {
			return std::make_shared<MenuScene>();
			})
		);
	buttons.push_back(buttonMenu);

	// Button "Quit"
	auto buttonQuit = std::make_shared<Button>(
		"Quit", "type1", 535, 400, sf::Vector2f(200, 50),
		std::make_shared<SwitchSceneCommand>([]() {
			// Thoát game
			std::exit(0);
			return nullptr;
			})
		);
	buttons.push_back(buttonQuit);
}

VictoryScene::~VictoryScene()
{
}

void VictoryScene::render(sf::RenderWindow& window)
{
	Scene::render(window);

	window.draw(title);
}
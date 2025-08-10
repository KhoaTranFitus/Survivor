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
	MusicManager::getInstance().stop();
	if (!fontLoaded) {
		fontLoaded = font.loadFromFile("PixelOperator8-Bold.ttf");
	}
	gameObjects.push_back(GameObjectFactory::createBackground("./Assets/backGround/background.png"));

	title = sf::Text("Victory", font, 40);
	title.setFillColor(sf::Color(107, 85, 74));
	title.setStyle(sf::Text::Italic);
	title.setPosition(490.f, 125.f);

	// Phát nhạc nền nếu chưa phát
	if (!MusicManager::getInstance().isPlaying()) {
		MusicManager::getInstance().play("./Assets/music/music_basic.mp3", 40.f, true);
	}

	//Button "Menu"
	auto buttonMenu = std::make_shared<Button>(
		"Menu", "type1", 535, 300, sf::Vector2f(200, 50),
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
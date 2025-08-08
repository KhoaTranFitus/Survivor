#include "MenuScene.h"
#include "Button.h"
#include "SwitchSceneCommand.h"
#include "SelectLevelScene.h"
#include "SettingScene.h"
#include "MusicManager.h"
sf::Font MenuScene::font;
bool MenuScene::fontLoaded = false;
MenuScene::MenuScene()
{
	MusicManager::getInstance().stop();
	if (!fontLoaded) {
		fontLoaded = font.loadFromFile("PixelOperator8-Bold.ttf");
	}
	gameObjects.push_back(GameObjectFactory::createBackground("./Assets/backGround/background.png"));

	title  =sf::Text("Survivor", font, 40);
	title.setFillColor(sf::Color(107, 85, 74));
	title.setStyle(sf::Text::Italic);
	title.setPosition(490.f, 125.f);

	// Phát nhạc nền nếu chưa phát
	if (!MusicManager::getInstance().isPlaying()) {
		MusicManager::getInstance().play("./Assets/music/music_basic.mp3", 40.f, true);
	}
	auto button1 = std::make_shared<Button>(
		"Play", "type1", 535, 300, sf::Vector2f(210, 50),
		std::make_shared<SwitchSceneCommand>([]() {
			return std::make_shared<SelectLevelScene>();
			})
	);
	buttons.push_back(button1);

	auto settingButton = std::make_shared<Button>(
		"Setting", "type1", 535, 400, sf::Vector2f(210, 50),
		std::make_shared<SwitchSceneCommand>([]() {
			return std::make_shared<SettingScene>();
			})
	);
	buttons.push_back(settingButton);
}

MenuScene::~MenuScene()
{
}

void MenuScene::render(sf::RenderWindow& window) 
{
	Scene::render(window);

	window.draw(title);
}


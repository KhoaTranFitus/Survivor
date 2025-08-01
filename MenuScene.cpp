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
	if (!fontLoaded) {
		fontLoaded = font.loadFromFile("arial.ttf");
	}
	gameObjects.push_back(GameObjectFactory::createBackground("./Assets/backGround/menuScene.png"));
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


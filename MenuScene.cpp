#include "MenuScene.h"
#include "Button.h"
#include "SwitchSceneCommand.h"
#include "SelectLevelScene.h"
#include "SettingScene.h"
MenuScene::MenuScene()
{
    auto button1 = std::make_shared<Button>(
        "Play", 500, 300, sf::Vector2f(200, 100),
        std::make_shared<SwitchSceneCommand>([]() {
            return std::make_shared<SelectLevelScene>();
        })
    );
    buttons.push_back(button1);

    auto settingButton = std::make_shared<Button>(
        "Setting", 500, 400, sf::Vector2f(200, 100),
        std::make_shared<SwitchSceneCommand>([]() {
            return std::make_shared<SettingScene>();
            })
    );
    buttons.push_back(settingButton);
}

MenuScene::~MenuScene()
{
}


#include "SelectLevelScene.h"
#include "Button.h"
#include "SwitchSceneCommand.h"
#include "GamePlayScene.h"
#include "MenuScene.h"

SelectLevelScene::SelectLevelScene()
{
     //Level 1 button
    auto level1Button = std::make_shared<Button>(
        "Level 1", 500, 300, sf::Vector2f(200, 100),
        std::make_shared<SwitchSceneCommand>([]() {
            return std::make_shared<GamePlayScene>();
        })
    );
    buttons.push_back(level1Button);

    // Back button
    auto backButton = std::make_shared<Button>(
        "Back", 100, 650, sf::Vector2f(50, 50),
        std::make_shared<SwitchSceneCommand>([]() {
            return std::make_shared<MenuScene>();
        })
    );
    buttons.push_back(backButton);
}

SelectLevelScene::~SelectLevelScene() {}

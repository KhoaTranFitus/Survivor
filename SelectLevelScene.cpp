#include "SelectLevelScene.h"
#include "Button.h"
#include "SwitchSceneCommand.h"
#include "GamePlayScene.h"
#include "MenuScene.h"

SelectLevelScene::SelectLevelScene()
{

     gameObjects.push_back(GameObjectFactory::createBackground("./Assets/backGround/selectLevel.png"));
    
     //Level 1 button
    auto level1Button = std::make_shared<Button>(
        "Level 1", "type1", 535, 300, sf::Vector2f(210, 50),
        std::make_shared<SwitchSceneCommand>([]() {
            return std::make_shared<GamePlayScene>();
        })
    );
    buttons.push_back(level1Button);

    // Back button
    auto backButton = std::make_shared<Button>(
        "Back", "type2", 50, 650, sf::Vector2f(145, 50),
        std::make_shared<SwitchSceneCommand>([]() {
            return std::make_shared<MenuScene>();
        })
    );
    buttons.push_back(backButton);
}

SelectLevelScene::~SelectLevelScene() {}

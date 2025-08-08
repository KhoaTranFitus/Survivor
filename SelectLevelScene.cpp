#include "SelectLevelScene.h"
#include "Button.h"
#include "SwitchSceneCommand.h"
#include "GamePlayScene.h"
#include "MenuScene.h"

SelectLevelScene::SelectLevelScene()
{

     gameObjects.push_back(GameObjectFactory::createBackground("./Assets/backGround/background.png"));
    

     


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


void SelectLevelScene::render(sf::RenderWindow& window)
{
    Scene::render(window);


    sf::Font font;
    font.loadFromFile("PixelOperator8-Bold.ttf");

    title = sf::Text("Select level", font, 40);
    title.setFillColor(sf::Color(107, 85, 74));
    title.setStyle(sf::Text::Italic);
    title.setPosition(430.f, 125.f);
    window.draw(title);
}
#include "LoseScene.h"
#include <sstream>
#include "Button.h"
#include "SwitchSceneCommand.h"
#include "MenuScene.h"
#include "MusicManager.h"
LoseScene::LoseScene(std::shared_ptr<GamePlayScene> gamePlayScene) :
    gamePlayScene(gamePlayScene)
{
	MusicManager::getInstance().play("./Assets/music/lose_scene.mp3", true);
    int elapsed = 0;
    if (gamePlayScene)
    {
        // Lấy đúng thời gian đã chơi khi vào LoseScene
        elapsed = static_cast<int>(gamePlayScene->getElapsedTime());
    }

    int minutes = elapsed / 60;
    int seconds = elapsed % 60;

    std::ostringstream oss;
    oss << "Time: ";
    if (minutes < 10) oss << '0';
    oss << minutes << ":";
    if (seconds < 10) oss << '0';
    oss << seconds;
    timeString = oss.str();

    auto retryButton = std::make_shared<Button>("Retry", "type1", 535, 300,
        sf::Vector2f(210, 50), std::make_shared<SwitchSceneCommand>([]()
            {
                return std::make_shared<GamePlayScene>();
            }));
    buttons.push_back(retryButton);

    auto menuButton = std::make_shared<Button>("Menu", "type1", 535, 400,
        sf::Vector2f(210, 50), std::make_shared<SwitchSceneCommand>([]()
            {
                return std::make_shared<MenuScene>();
            }));
    buttons.push_back(menuButton);
}

LoseScene::~LoseScene()
{
}

void LoseScene::update(float deltaTime)
{
    for (auto& but : buttons)
    {
        but->update(deltaTime);
    }
}

void LoseScene::render(sf::RenderWindow& window)
{
    //vẽ lại game play scene ở dưới
    if (gamePlayScene) gamePlayScene->render(window);

    sf::RectangleShape overlap(sf::Vector2f(window.getSize()));
    overlap.setFillColor(sf::Color(0, 0, 0, 180));
    window.draw(overlap);

    sf::Font font;
    font.loadFromFile("PixelOperator8-Bold.ttf");
    sf::Text gameover("Game Over", font, 80);
    gameover.setPosition(300, 50);
    gameover.setFillColor(sf::Color::Red);
    gameover.setStyle(sf::Text::Bold);
    window.draw(gameover);

    sf::Text time(timeString, font, 30);
    time.setFillColor(sf::Color::Red);
    time.setPosition(500, 180);
    window.draw(time);

    for (auto but : buttons)
    {
        but->render(window);
    }
}
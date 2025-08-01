#include "LoseScene.h"
#include <sstream>
#include "Button.h"
#include "SwitchSceneCommand.h"
#include "MenuScene.h"
LoseScene::LoseScene(std::shared_ptr<GamePlayScene> gamePlayScene) :
	gamePlayScene(gamePlayScene)
{
	int ecapsed;
	if (gamePlayScene)
	{
		ecapsed = gamePlayScene->getElapsedTime();
	}

	int minutes = ecapsed / 60;
	int seconds = ecapsed & 60;
	std::ostringstream oss;
	oss << "Time: ";
	if (minutes < 10) oss << '0';
	oss<<minutes << ":";
	if (seconds < 10) oss << '0';
	oss << seconds;
	timeString = oss.str();

	auto retryButton = std::make_shared<Button>("Retry","type1",535,300,
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
	font.loadFromFile("arial.ttf");
	sf::Text gameover("Game Over", font, 80);
	gameover.setPosition(430, 50);
	gameover.setFillColor(sf::Color::Red);
	gameover.setStyle(sf::Text::Bold);
	window.draw(gameover);

	sf::Text time(timeString, font, 30);
	time.setFillColor(sf::Color::Red);
	time.setPosition(550, 180);
	window.draw(time);

	for (auto but : buttons)
	{
		but->render(window);
	}

}
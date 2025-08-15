#include "Game.h"
#include "GameManager.h"
#include "MenuScene.h"
#include "SelectLevelScene.h"
#include "GamePlayScene.h"

void Game::updateMousePosition()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);
	mousePosition = sf::Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

Game::Game()
{
	sf::VideoMode videoMode(WINDOW_WIDTH, WINDOW_HEIGHT);
	this->window = new sf::RenderWindow(videoMode, "Survivor", sf::Style::Close);
	this->window->setKeyRepeatEnabled(false);

	GameManager::getInstance().setScene(std::make_shared<MenuScene>());
}

Game::~Game()
{
	delete this->window;
}

void Game::run()
{
	sf::Clock clock;
	while (this->window->isOpen())
	{
		float deltaTime = clock.restart().asSeconds();
		float FPS = 1 / deltaTime;
		if (FPS < 30.f) continue;

		GameManager::getInstance().pollEvent(*this->window);
		this->update(deltaTime);
		this->render(*this->window);
	}
}

void Game::update(float deltaTime)
{
	this->updateMousePosition();

	GameManager::getInstance().update(deltaTime);

	auto scene = GameManager::getInstance().getCurrentScene();
	if (scene)
		scene->update(deltaTime);
}
void Game::render(sf::RenderWindow& window)
{
	window.clear(sf::Color::White);

	auto scene = GameManager::getInstance().getCurrentScene();
	if (scene)
		scene->render(window);
	window.display();
}

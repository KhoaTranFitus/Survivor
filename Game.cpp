#include "Game.h"

void Game::pollEvent()
{
	sf::Event event;
	while (this->window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			this->window->close();
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
			}
		}
	}
}

void Game::updateMousePosition()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);
	mousePosition = sf::Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

Game::Game()
{
	sf::VideoMode videoMode(WINDOW_WIDTH, WINDOW_HEIGHT);
	this->window = new sf::RenderWindow(videoMode, "SFML Game", sf::Style::Close);

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

		this->pollEvent();
		this->update(deltaTime);
		this->render(*this->window);
	}
}

void Game::update(float deltaTime)
{
	this->updateMousePosition();
	GameManager::getInstance().getCurrentScene()->update(deltaTime);
}

void Game::render(sf::RenderWindow& window)
{
	window.clear(sf::Color::White);

	GameManager::getInstance().getCurrentScene()->render(window);

	window.display();
}

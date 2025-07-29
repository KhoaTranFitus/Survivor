// GameManager.cpp
#include "GameManager.h"


GameManager& GameManager::getInstance() {
    static GameManager instance;
    return instance;
}

void GameManager::pollEvent(sf::RenderWindow& window)
{
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				window.close();
			}
		}
	}
}

bool GameManager::isMousePressed(sf::Mouse::Button button)
{
    // Nếu chưa từng được theo dõi thì thêm vào map
    if (mouseHoldings.find(button) == mouseHoldings.end())
    {
        mouseHoldings[button] = false;
        mouseJustPressed[button] = false;
        return sf::Mouse::isButtonPressed(button);
    }
    return mouseJustPressed[button];
}


bool GameManager::isKeyPressed(sf::Keyboard::Key key)
{
    if (keyHoldings.find(key) == keyHoldings.end())
    {
        keyHoldings[key] = false;
        keyJustPressed[key] = false;
        return (sf::Keyboard::isKeyPressed(key));
    }
    return keyJustPressed[key];
}


void GameManager::setScene(std::shared_ptr<Scene> scene) {
    currentScene = std::move(scene);
}

std::shared_ptr<Scene> GameManager::getCurrentScene() {
    return currentScene;
}

void GameManager::update(float deltaTime)
{
    // --- Update keyboard ---
    for (auto& key : keyHoldings)
    {
        if (sf::Keyboard::isKeyPressed(key.first))
        {
            if (!key.second)
            {
                key.second = true;
                keyJustPressed[key.first] = true;
            }
            else
            {
                keyJustPressed[key.first] = false;
            }
        }
        else
        {
            keyJustPressed[key.first] = false;
            key.second = false;
        }
    }

    // --- Update mouse ---
    for (auto& button : mouseHoldings)
    {
        if (sf::Mouse::isButtonPressed(button.first))
        {
            if (!button.second)
            {
                button.second = true;
                mouseJustPressed[button.first] = true;
            }
            else
            {
                mouseJustPressed[button.first] = false;
            }
        }
        else
        {
            mouseJustPressed[button.first] = false;
            button.second = false;
        }
    }
}

sf::RenderWindow& GameManager::getWindow() {
    return *this->window;
}

void GameManager::setCamera(std::shared_ptr<Camera> cam) {
    camera = cam;
}

std::shared_ptr<Camera> GameManager::getCamera() const {
    return camera;
}

sf::FloatRect GameManager::getCameraViewRect() const {
    if (camera)
        return camera->getViewRect();
    return sf::FloatRect();
} 
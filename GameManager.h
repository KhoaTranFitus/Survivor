// GameManager.h
#pragma once

#include <iostream>
#include <memory>
#include <map>
#include "Scene.h"
#include "Camera.h"
class Scene;

class GameManager {
private:
    sf::RenderWindow* window;
    std::shared_ptr<Scene> currentScene;
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;


    std::map<sf::Keyboard::Key, bool> keyHoldings;
    std::map<sf::Keyboard::Key, bool> keyJustPressed;

    std::map<sf::Mouse::Button, bool> mouseHoldings;
    std::map<sf::Mouse::Button, bool> mouseJustPressed;

    std::shared_ptr<Camera> camera;


public:
    GameManager(){};
    ~GameManager() {};
    static GameManager& getInstance();
    std::shared_ptr<Player> currentPlayer = nullptr;

    sf::Event event = sf::Event();
    void pollEvent(sf::RenderWindow& window);

    bool isMousePressed(sf::Mouse::Button button);
    bool isKeyPressed(sf::Keyboard::Key key);

    void setScene(std::shared_ptr<Scene> scene);
    std::shared_ptr<Scene> getCurrentScene();
	sf::RenderWindow& getWindow();

    void setCamera(std::shared_ptr<Camera> cam);
    std::shared_ptr<Camera> getCamera() const;
    sf::FloatRect getCameraViewRect() const;


    void update(float deltaTime);
};
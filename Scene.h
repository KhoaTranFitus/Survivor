#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "Button.h"
#include "Camera.h"
class Button;

class Scene
{
protected:
	std::vector<std::shared_ptr<Button>> buttons;
	std::vector<std::shared_ptr<GameObject>> gameObjects;
	std::vector<std::shared_ptr<GameObject>> gameObjectQueue; // thêm object trong khi "update" thì dùng hàm addGameObject()
	Camera camera;
public: 
	Scene() = default;
	virtual ~Scene() = default;

	Camera& getCamera() { return camera; }
	void addGameObject(std::shared_ptr<GameObject> gameObject);

	virtual void update(float deltaTime);
	std::vector<std::shared_ptr<GameObject>>& getGameObjects() { return gameObjects; }
	virtual void render(sf::RenderWindow& window);
};


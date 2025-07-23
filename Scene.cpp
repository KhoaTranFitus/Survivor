#include "Scene.h"

void Scene::addGameObject(std::shared_ptr<GameObject> gameObject)
{
	this->gameObjectQueue.push_back(gameObject);
}

// Scene.cpp
void Scene::update(float deltaTime)
{
	for (auto& obj : this->gameObjectQueue)
	{
		this->gameObjects.push_back(obj);
	}
	while (!this->gameObjectQueue.empty()) this->gameObjectQueue.pop_back();

	// 1. Xoá thật sự các object cần xoá
	gameObjects.erase(std::remove_if(gameObjects.begin(), gameObjects.end(),
		[](std::shared_ptr<GameObject>& obj) {
			return obj->needDeleted;
		}), gameObjects.end());

	// 2. Cập nhật còn lại
	for (auto& obj : gameObjects)
		obj->update(deltaTime);
	
	if (gameObjects.size() >= 2)
	{
		for (int i = 0; i < gameObjects.size() - 1; i++)
		{
			for (int j = i + 1; j < gameObjects.size(); j++)
			{
				if (gameObjects[i]->getHitbox().getGlobalBounds().intersects(gameObjects[j]->getHitbox().getGlobalBounds()))
				{
					gameObjects[i]->onCollisionEnter(gameObjects[j]);
					gameObjects[j]->onCollisionEnter(gameObjects[i]);
				}
			}
		}
	}

	for (auto& button : buttons)
		button->update(deltaTime);
}

void Scene::render(sf::RenderWindow& window)
{
	//window.setView(window.getDefaultView());
	for (auto& obj : gameObjects) obj->render(window);

	for (auto& button : buttons)
		button->render(window);
}




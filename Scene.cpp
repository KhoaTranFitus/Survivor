#include "Scene.h"

void Scene::addGameObject(std::shared_ptr<GameObject> gameObject)
{
	this->gameObjectQueue.push_back(gameObject);
}

// Scene.cpp
void Scene::update(float deltaTime)
{
    // 1. Thêm gameObject mới từ queue vào danh sách chính
    for (auto& obj : this->gameObjectQueue)
    {
        this->gameObjects.push_back(obj);
    }
    this->gameObjectQueue.clear();

    // 2. Xoá thật sự các object cần xoá: reset + erase
    for (auto it = gameObjects.begin(); it != gameObjects.end(); )
    {
        if ((*it)->needDeleted)
        {
            (*it)->onDestroy();
            it = gameObjects.erase(it); // Xoá khỏi vector
        }
        else
        {
            ++it;
        }
    }
  
    for (auto& obj : gameObjects)
    {
        obj->update(deltaTime);
    }

    // 4. Va chạm
    const size_t size = gameObjects.size();
    for (size_t i = 0; i < size; ++i)
    {
        for (size_t j = i + 1; j < size; ++j)
        {
            if (gameObjects[i]->getHitbox().getGlobalBounds().intersects(
                gameObjects[j]->getHitbox().getGlobalBounds()))
            {
                gameObjects[i]->onCollisionEnter(gameObjects[j]);
                gameObjects[j]->onCollisionEnter(gameObjects[i]);
            }
        }
    }

    // 5. Cập nhật nút
    for (auto& button : buttons)
    {
        button->update(deltaTime);
    }
}

void Scene::render(sf::RenderWindow& window)
{
	//window.setView(window.getDefaultView());
	for (auto& obj : gameObjects) obj->render(window);

	for (auto& button : buttons)
		button->render(window);
}




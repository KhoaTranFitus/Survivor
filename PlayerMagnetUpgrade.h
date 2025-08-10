#pragma once
#include "Component.h"
#include <memory>
#include "GameObject.h"
#include "GameManager.h"

class PlayerMagnetUpgrade : public Component {
    int level = 1;
    const int maxLevel = 5;
    float magnetRadiusPerLevel = 100.f;
public:
    PlayerMagnetUpgrade(std::shared_ptr<GameObject> owner) : Component(owner) {}
    void upgrade() {
        if (level < maxLevel) {
            level++;
        }
    }
    int getLevel() const { return level; }
    float getMagnetRadius() const { return level * magnetRadiusPerLevel; }
    void update(float deltaTime) override {
        // Get player position
        sf::Vector2f playerPos = owner->getHitbox().getPosition();

        // Get all game objects in the current scene
        auto gameObjects = GameManager::getInstance().getCurrentScene()->getGameObjects();

        float radius = getMagnetRadius();
        float magnetSpeed = 400.f; // Speed at which gems move toward player

        for (auto& obj : gameObjects) {
            if (obj->getTag() == "gem_type1" || obj->getTag() == "gem_type2" || obj->getTag() == "gem_type3") {
                sf::Vector2f gemPos = obj->getHitbox().getPosition();
                sf::Vector2f toPlayer = playerPos - gemPos;
                float distance = std::sqrt(toPlayer.x * toPlayer.x + toPlayer.y * toPlayer.y);

                if (distance < radius && distance > 1.f) {
                    // Normalize direction
                    sf::Vector2f dir = toPlayer / distance;
                    // Move gem toward player
                    obj->move(dir * magnetSpeed * deltaTime);
                }
            }
        }
    }
};


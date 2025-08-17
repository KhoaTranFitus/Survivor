#pragma once
#include "Component.h"
#include <vector>
#include <memory>

class NoOverlapComponent : public Component {
private:
    std::vector<std::shared_ptr<GameObject>>* gameObjects;
public:
    NoOverlapComponent(std::shared_ptr<GameObject> owner, 
        std::vector<std::shared_ptr<GameObject>>* gameObjects)

        : Component(owner), gameObjects(gameObjects) {}

    void update(float deltaTime) override;

};

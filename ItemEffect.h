// ItemEffect.h
#pragma once
#include "Component.h"
#include "GameObject.h"
#include <functional>
class ItemEffect : public Component
{
private:
    std::function<std::shared_ptr<Component>(std::shared_ptr<GameObject>)> componentCreator;

public:
    ItemEffect(std::shared_ptr<GameObject> owner,
        std::function<std::shared_ptr<Component>(std::shared_ptr<GameObject>)> creator);

	void update(float deltaTime) override;
    void onCollisionEnter(std::shared_ptr<GameObject> other) override;
};

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
    void upgrade();
    int getLevel() const { return level; }

    float getMagnetRadius() const;

    void update(float deltaTime) override;
};


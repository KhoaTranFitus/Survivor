#pragma once
#include "Component.h"
#include <iostream>

class PlayerStat : public Component {
public:
    int exp;
    int level;
    int expToNextLevel;
public:
    PlayerStat(std::shared_ptr<GameObject> owner);

    void addExp(int amount);
    int getExp() const { return exp; }
    int getLevel() const { return level; }
    int getExpToNextLevel() const { return expToNextLevel; }

    void update(float) override;
    void render(sf::RenderWindow& window, const sf::Font& font);
};

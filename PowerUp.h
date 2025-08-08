#pragma once
#include "GameObject.h"
#include <string>
#include <memory>

class PowerUp : public GameObject
{
public:
    PowerUp(); // default constructor
    ~PowerUp();

    // New: Factory method for creating powerups by name and position
    static std::shared_ptr<PowerUp> Create(const std::string& name, float x, float y);

	void render(sf::RenderWindow& window) override;
};


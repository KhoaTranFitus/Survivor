#include "Gem.h"
#include <iostream>

void Gem::update(float deltaTime) {
    // Có thể thêm hiệu ứng lấp lánh hoặc rơi nếu muốn
}

void Gem::render(sf::RenderWindow& window) {
    window.draw(hitbox);
}

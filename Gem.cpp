#include "Gem.h"
#include <iostream>
#include  "Assets.h"
Gem::Gem(sf::Vector2f position,const std::string tag)
{
    hitbox.setSize(sf::Vector2f(15.f, 15.f));
    hitbox.setFillColor(sf::Color::Yellow);
    hitbox.setPosition(position);
    setTag(tag);
    if(tag == "gem_type2") {
        animation = std::make_shared<Animation>(Assets::GEM_TYPE2, 4, 0.15f, sf::Vector2i(16, 16));
    } else if(tag == "gem_type1") {
        animation = std::make_shared<Animation>(Assets::GEM_TYPE1, 4, 0.15f, sf::Vector2i(16, 16));
    } else if(tag == "gem_type3") {
        animation = std::make_shared<Animation>(Assets::GEM_TYPE3, 4, 0.15f, sf::Vector2i(16, 16));
	}
    animation->setPosition(position);
    animation->setScale(sf::Vector2f(1.5f, 1.5f));
}

void Gem::update(float deltaTime) {
    if (animation) animation->update(deltaTime, false);
}

void Gem::render(sf::RenderWindow& window) {

    if (animation) animation->render(window);
}

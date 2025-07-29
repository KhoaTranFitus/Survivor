#include "Player.h"
#include "Assets.h"
#include "Animation.h"

Player::Player()
{
	hitbox.setSize(sf::Vector2f(50.f, 50.f));
	hitbox.setFillColor(sf::Color::Green);
	hitbox.setPosition(615.f, 335.f);
	this->tag = "player";

	animations.push_back(std::make_shared<Animation>(Assets::PLAYER_TEXTURE, 4, 0.15f, sf::Vector2i(13, 19)));
	animations[INT(PLAYER_STATE::IDLE)]->setScale(sf::Vector2f(3, 3));
	animations.push_back(std::make_shared<Animation>(Assets::PLAYER_RUN, 4, 0.1f, sf::Vector2i(13, 19)));
	animations[INT(PLAYER_STATE::RUN)]->setScale(sf::Vector2f(3, 3));
}

Player::~Player()
{
}

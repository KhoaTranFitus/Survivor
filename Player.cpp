#include "Player.h"
#include "Assets.h"
#include "Animation.h"
#include "GameManager.h"
Player::Player()
{
	hitbox.setSize(sf::Vector2f(50.f, 50.f));
	hitbox.setFillColor(sf::Color::Green);
	hitbox.setPosition(615.f, 335.f);
	this->tag = "player";

	animations.push_back(std::make_shared<Animation>(Assets::PLAYER_TEXTURE, 6, 0.15f, sf::Vector2i(19, 19)));
	animations[INT(PLAYER_STATE::IDLE)]->setScale(sf::Vector2f(3, 3));

	animations.push_back(std::make_shared<Animation>(Assets::PLAYER_RUN, 8, 0.1f, sf::Vector2i(19, 19)));
	animations[INT(PLAYER_STATE::RUN)]->setScale(sf::Vector2f(3, 3));

	animations.push_back(std::make_shared<Animation>(Assets::PLAYER_FIRE, 6, 0.05f, sf::Vector2i(25, 19)));
	animations[INT(PLAYER_STATE::FIRE)]->setScale(sf::Vector2f(3, 3));

	animations.push_back(std::make_shared<Animation>(Assets::PLAYER_HURT, 4, 0.1f, sf::Vector2i(19, 19)));
	animations[INT(PLAYER_STATE::HURT)]->setScale(sf::Vector2f(3, 3));

	animations.push_back(std::make_shared<Animation>(Assets::PLAYER_DIE, 4 , 0.7f, sf::Vector2i(19, 19)));
	animations[INT(PLAYER_STATE::DIE)]->setScale(sf::Vector2f(3, 3));

}

Player::~Player()
{
}

bool Player::isControllable() const {
    // Không cho điều khiển nếu đang ở state DIE (4)
	return GameManager::getInstance().currentPlayer->getCurrentState() != 4;
}

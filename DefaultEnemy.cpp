#include "DefaultEnemy.h"
#include "Assets.h"
DefaultEnemy::DefaultEnemy()
{
	animations.push_back(std::make_shared<Animation>(Assets::ENEMY_RUN, 8, 0.15f, sf::Vector2i(16, 16)));
	animations[INT(ENEMY_STATE::RUN)]->setScale(sf::Vector2f(2.5, 2.5));
}

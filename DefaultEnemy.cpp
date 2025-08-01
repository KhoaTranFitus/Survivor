#include "DefaultEnemy.h"
#include "Assets.h"
DefaultEnemy::DefaultEnemy()
{
	animations.push_back(std::make_shared<Animation>(Assets::ENEMY_RUN, 4, 0.15f, sf::Vector2i(14, 15)));
	animations[INT(ENEMY_STATE::RUN)]->setScale(sf::Vector2f(2, 2));
}

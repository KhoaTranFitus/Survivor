#include "BurstEnemy.h"
#include "Assets.h"
BurstEnemy::BurstEnemy(){
	animations.push_back(std::make_shared<Animation>(Assets::BURST_RUN,
		4, 0.15f, sf::Vector2i(27, 27)));
	animations[int(ENEMY_STATE::RUN)]->setScale(sf::Vector2f(2.5f, 2.5f));
}

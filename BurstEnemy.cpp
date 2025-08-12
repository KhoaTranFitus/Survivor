#include "BurstEnemy.h"
#include "Assets.h"
BurstEnemy::BurstEnemy(){
	animations.push_back(std::make_shared<Animation>(Assets::SHOOT_ENEMY,
		4, 0.15f, sf::Vector2i(14, 14)));
	animations[int(ENEMY_STATE::RUN)]->setScale(sf::Vector2f(3.f, 3.f));
}

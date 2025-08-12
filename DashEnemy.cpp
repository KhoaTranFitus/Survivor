#include "DashEnemy.h"
#include "GameObjectFactory.h"
#include "Assets.h"
DashEnemy::DashEnemy() : Enemies() {
    // Các thuộc tính khác nếu cần
	animations.push_back(std::make_shared<Animation>(Assets::DASH_RUN, 4, 0.15f, sf::Vector2i(15, 15)));
	animations[int(ENEMY_STATE::RUN)]->setScale(sf::Vector2f(3.f, 3.f));
}
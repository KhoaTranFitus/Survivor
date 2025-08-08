#include "TankerEnemy.h"
#include	"Assets.h"

TankerEnemy::TankerEnemy(){

	animations.push_back( std::make_shared<Animation>(Assets::TANKER_RUN,
		5,0.2f,sf::Vector2i(30,30)));
	animations[int(ENEMY_STATE::RUN)]->setScale(sf::Vector2f(2.5f, 2.5f));
}

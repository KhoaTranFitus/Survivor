#include "MoveForward.h"
#include "GameObject.h"

MoveForward::MoveForward(std::shared_ptr<GameObject> owner, sf::Vector2f targetPosition,float speed) :
	Component(owner),
	targetPosition(targetPosition)
{
	direction = targetPosition - this->owner->getOrigin();
	float length = sqrt(direction.x * direction.x + direction.y * direction.y);

	if (length == 0) length = 0.1;
	this->speed = speed; 
	direction =  direction* speed / length;
}
 
void MoveForward::update(float deltaTime)
{
	this->owner->move(direction* deltaTime);
}
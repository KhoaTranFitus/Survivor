#include <iostream>
#include "Bullet.h"
#include "FollowTarget.h"
#include "Enemies.h"

FollowTarget::FollowTarget(std::shared_ptr<GameObject> owner, std::shared_ptr<GameObject> target, float speed) :
	Component(owner), target(target), speed(speed)
{
}

FollowTarget::~FollowTarget()
{
}

void FollowTarget::update(float deltaTime)
{
    // Nếu không có target hoặc target sắp bị xóa, thì đi theo hướng cũ
    if (!target || target->needDeleted)
    {
        owner->move(lastDirection * speed * deltaTime);
        return;
    }

    // Lúc này target còn sống, được phép truy cập hitbox
    sf::Vector2f direction = target->getHitbox().getPosition() - owner->getHitbox().getPosition();
    if (direction.x < 0) {
        owner->setFlipped(true);
    }
    else if (direction.x > 0) {
        owner->setFlipped(false);
    }
    float length = std::hypot(direction.x, direction.y);
    if (length > 0.1f)
    {
        direction /= length;
        lastDirection = direction;
    }

    owner->move(lastDirection * speed * deltaTime);
}

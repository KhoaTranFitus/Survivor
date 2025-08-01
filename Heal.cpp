#include "Heal.h"
#include "GameObject.h"
#include "Stat.h"

Heal::Heal(std::shared_ptr<GameObject> owner, float healAmount)
    : Component(owner), healAmount(healAmount)
{
}

void Heal::onCollisionEnter(std::shared_ptr<GameObject> other)
{
    auto stat = other->getComponent<Stat>();
    if (stat)
    {
        float healValue = stat->getHealth() * 0.2f; // hoặc dùng healAmount nếu muốn cố định
        stat->setHealth(std::min(stat->getHealth() + healValue, stat->getMaxHealth()));
        owner->needDeleted = true;
    }
}

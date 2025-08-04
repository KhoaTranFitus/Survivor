#include "Heal.h"
#include "Stat.h"
#include "GameObject.h"

Heal::Heal(std::shared_ptr<GameObject> owner, float amount)
    : Component(owner), healAmount(amount) 
{
    auto stat = owner->getComponent<Stat>();
    if (stat)
    {
        float newHealth = stat->getHealth() + stat->getMaxHealth() * healAmount;
        stat->setHealth(newHealth);
    }
}

void Heal::onCollisionEnter(std::shared_ptr<GameObject> other)
{
    // Không cần xử lý gì ở đây nữa
}
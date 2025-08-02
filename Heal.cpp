#include "Heal.h"
#include "Stat.h"
#include "GameObject.h"

Heal::Heal(std::shared_ptr<GameObject> owner, float amount)
    : Component(owner), healAmount(amount) {
}

void Heal::onCollisionEnter(std::shared_ptr<GameObject> other)
{
    auto stat = other->getComponent<Stat>();
    if (stat)
    {
        float healAmount = stat->getMaxHealth() * 0.2f; // 20% máu gốc
        stat->heal(healAmount);
    }
    // Có thể xóa powerup sau khi dùng
    owner->needDeleted = true;
}

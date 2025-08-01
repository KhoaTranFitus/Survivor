#include "DamageOnContact.h"
#include "GameObject.h"
#include "Stat.h"

DamageOnContact::DamageOnContact(std::shared_ptr<GameObject> owner, float damage, std::string targetTag, float cooldown)
    : Component(owner), damage(damage), targetTag(targetTag), cooldown(cooldown), timer(0.f)
{
}

void DamageOnContact::update(float deltaTime)
{
    if (timer > 0.0f)
        timer -= deltaTime;
    if (timer < 0.0f)
        timer = 0.0f;
}

void DamageOnContact::onCollisionEnter(std::shared_ptr<GameObject> other)
{
    if (!other) return;
    if (other->getTag() != targetTag) return;

    if (timer <= 0.0f)
    {
        auto stat = other->getComponent<Stat>();
        if (stat)
        {
            stat->takeDamage(damage);
            timer = cooldown;
        }
        // Nếu là bullet thì xóa luôn sau va chạm
        if (owner && owner->getTag() == "bullet")
        {
            owner->needDeleted = true;
        }
    }
}
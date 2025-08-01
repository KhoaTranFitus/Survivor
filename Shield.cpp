#include "Shield.h"
#include "GameObject.h"
#include "Stat.h"

Shield::Shield(std::shared_ptr<GameObject> owner, float shieldAmount)
    : Component(owner), shieldAmount(shieldAmount)
{
}

void Shield::onCollisionEnter(std::shared_ptr<GameObject> other)
{
    auto stat = other->getComponent<Stat>();
    if (stat)
    {
        stat->addShield(shieldAmount, 5.f); // hiệu lực 5s
        owner->needDeleted = true;
    }
}

#include "Speed.h"
#include "GameObject.h"
#include "Stat.h"
Speed::Speed(std::shared_ptr<GameObject> owner, float percent)
    : Component(owner), percent(percent)
{
}

void Speed::onCollisionEnter(std::shared_ptr<GameObject> other)
{
    auto stat = other->getComponent<Stat>();
    if (stat)
    {
        float buffAmount = stat->getSpeed() * percent; // tăng 30% tốc độ hiện tại
        stat->addSpeedBuff(buffAmount, 5.f);           // hiệu lực 5s
        owner->needDeleted = true;
    }
}

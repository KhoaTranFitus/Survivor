#include "Speed.h"
#include "Stat.h"
#include "GameObject.h"

Speed::Speed(std::shared_ptr<GameObject> owner, float percent, float duration)
    : Component(owner), percent(percent), duration(duration), timer(0.f), activated(false) {}

void Speed::onCollisionEnter(std::shared_ptr<GameObject> other) {
    auto stat = other->getComponent<Stat>();
    if (stat && !activated) {
        stat->modifySpeed(stat->getBaseSpeed() * percent); // tăng 30% tốc độ gốc
        activated = true;
        timer = 0.f;
    }
    owner->needDeleted = true;
}

void Speed::update(float deltaTime) {
    if (activated) {
        timer += deltaTime;
        if (timer >= duration) {
            auto stat = owner->getComponent<Stat>();
            if (stat) {
                stat->modifySpeed(-stat->getBaseSpeed() * percent); // trả lại tốc độ gốc
            }
            activated = false;
            owner->removeComponent<Speed>();
        }
    }
}

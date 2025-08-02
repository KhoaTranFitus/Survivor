#include "Shield.h"
#include "Stat.h"
#include "GameObject.h"

Shield::Shield(std::shared_ptr<GameObject> owner, float amount, float duration)
    : Component(owner), shieldAmount(amount), duration(duration), timer(0.f) {}

void Shield::onCollisionEnter(std::shared_ptr<GameObject> other) {
    auto stat = other->getComponent<Stat>();
    if (stat) {
        // Đặt trạng thái bất tử
        stat->modifyShield(shieldAmount); // hoặc set một flag bất tử
    }
    owner->needDeleted = true;
}

void Shield::update(float deltaTime) {
    timer += deltaTime;
    if (timer >= duration) {
        auto stat = owner->getComponent<Stat>();
        if (stat) {
            stat->modifyShield(-shieldAmount); // hoặc unset flag bất tử
        }
        owner->removeComponent<Shield>();
    }
}

#pragma once
#include "Component.h"

class Speed : public Component
{
    float speedAmount = 0.f;     // tốc độ tăng thêm
    float duration = 0.f;        // thời gian hiệu lực
    float timer = 0.f;           // đếm thời gian
    bool activated = false;
    float percent;

public:
    Speed(std::shared_ptr<GameObject> owner, float percent, float duration);

    void onCollisionEnter(std::shared_ptr<GameObject> other) override;
    void update(float deltaTime) override;
    float getBonus() const { return speedAmount; } // nếu bạn cần gọi

};

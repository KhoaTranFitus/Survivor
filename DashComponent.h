#pragma once
#include "Component.h"

class DashComponent : public Component {
protected:
    float moveTime, moveSpeed, dashSpeed, dashDuration;
    float moveElapsed, dashElapsed, waitElapsed;
    float waitTime; // thời gian đứng yên trước khi dash
    bool isDashing, isWaiting;
    sf::Vector2f dashDirection;

public:
    DashComponent(std::shared_ptr<GameObject> owner, float moveTime, float moveSpeed, float dashSpeed, float dashDuration, float waitTime = 1.f);
    void update(float deltaTime) override;
    virtual void onDashStart() {}
    virtual void onDashEnd() {}
    bool getIsDashing() { return this->isDashing; };
    bool getIsWaiting() const { return isWaiting; }
};


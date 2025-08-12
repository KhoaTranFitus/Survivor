#include "DashComponent.h"
#include "GameManager.h"
#include <cmath>

DashComponent::DashComponent(std::shared_ptr<GameObject> owner, float moveTime, float moveSpeed, float dashSpeed, float dashDuration, float waitTime)
    : Component(owner), moveTime(moveTime), moveSpeed(moveSpeed), dashSpeed(dashSpeed), dashDuration(dashDuration),
      moveElapsed(0.f), dashElapsed(0.f), waitElapsed(0.f), waitTime(waitTime),
      isDashing(false), isWaiting(false) {}

void DashComponent::update(float deltaTime) {
    if (isDashing) {
        dashElapsed += deltaTime;
        owner->move(dashDirection * dashSpeed * deltaTime);
        if (dashElapsed >= dashDuration) {
            isDashing = false;
            moveElapsed = 0.f;
            onDashEnd();
        }
        return;
    }

    if (isWaiting) {
        waitElapsed += deltaTime;
        // Đứng yên, không di chuyển
        if (waitElapsed >= waitTime) {
            // Chuẩn bị dash
            auto player = GameManager::getInstance().currentPlayer;
            if (player) {
                dashDirection = player->getOrigin() - owner->getOrigin();
                float len = std::sqrt(dashDirection.x * dashDirection.x + dashDirection.y * dashDirection.y);
                if (len > 0.f) dashDirection /= len;
				//cat nhat huong dash
            }
            isDashing = true;
            dashElapsed = 0.f;
            isWaiting = false;
            onDashStart();
        }
        return;
    }

    // Di chuyển bình thường về phía player
    auto player = GameManager::getInstance().currentPlayer;
    if (player) {
        sf::Vector2f dir = player->getOrigin() - owner->getOrigin();
        float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        if (len > 0.f) dir /= len;

        if (dir.x < 0) {
            owner->setFlipped(true);
        }
        else if (dir.x > 0) {
            owner->setFlipped(false);
        }
        // Chỉ setState(0) nếu không phải FIRE (1) hoặc DIE (2)
        if (owner->getCurrentState() != 1 && owner->getCurrentState() != 2) {
            owner->setState(0);
        }
        owner->move(dir * moveSpeed * deltaTime);
    }
    moveElapsed += deltaTime;
    if (moveElapsed >= moveTime) {
        isWaiting = true;
        waitElapsed = 0.f;
        moveElapsed = 0.f;
    }
}

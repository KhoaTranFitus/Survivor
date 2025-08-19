#include <iostream>
#include "Boss.h"
#include "Assets.h"
#include "BossShoot.h"
#include "DashComponent.h"
Boss::Boss() : Enemies() {
    hitbox.setSize(sf::Vector2f(120.f, 120.f));
    hitbox.setFillColor(sf::Color(255, 128, 0));

    // RUN
    animations.push_back(std::make_shared<Animation>(Assets::BOSS_RUN,
        8, 0.15f, sf::Vector2i(52, 52)));
    animations[0]->setScale(sf::Vector2f(2.5f, 2.5f));

    // FIRE (use a real FIRE animation if you have, else reuse RUN)
    animations.push_back(std::make_shared<Animation>(Assets::BOSS_FIRE,
        5, 0.1f, sf::Vector2i(52, 52)));
    animations[1]->setScale(sf::Vector2f(2.5f, 2.5f));

    // DIE
    animations.push_back(std::make_shared<Animation>(Assets::BOSS_DIE,
        9, 0.4f, sf::Vector2i(63, 63)));
    animations[2]->setScale(sf::Vector2f(2.5f, 2.5f));
}

void Boss::update(float deltaTime)
{
    // Nếu boss đang ở trạng thái DIE thì chỉ update animation DIE, không di chuyển, không bắn
    if (getCurrentState() == 2) {
        if (!animations.empty()) {
            animations[2]->update(deltaTime, flipped); // Chạy animation DIE
            animations[2]->setCenter();
            animations[2]->setPosition(
                hitbox.getPosition() + hitbox.getSize() / 2.f
            );
        }
        return;
    }

    Enemies::update(deltaTime);

    if (!animations.empty()) {
        int state = getCurrentState();
        if (state >= 0 && state < animations.size()) {
            animations[state]->update(deltaTime, flipped);
            animations[state]->setCenter();
            animations[state]->setPosition(
                hitbox.getPosition() + hitbox.getSize() / 2.f
            );
        }
    }
}
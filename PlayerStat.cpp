#include "PlayerStat.h"

PlayerStat::PlayerStat(std::shared_ptr<GameObject> owner) :Component(owner)
{
    this->owner = owner;
    level = 1;
    exp = 0;
    expToNextLevel = 100; // Giả sử cần 100 exp để lên level đầu tiên
}

void PlayerStat::addExp(int amount)
{
    exp += amount;
    while (exp >= expToNextLevel) {
        exp -= expToNextLevel;
        level++;
        std::cout << "Level up! New level: " << level << std::endl;
        expToNextLevel *= 1.2f; // t?ng exp c?n cho level ti?p theo
    }
}

void PlayerStat::update(float deltaTime)
{
}
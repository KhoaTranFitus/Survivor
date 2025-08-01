// Shoot.cpp
#include "Shoot.h"
#include "GameManager.h"
#include "MoveForward.h"
#include "DamageOnContact.h"
Shoot::Shoot(std::shared_ptr<GameObject> owner, float cooldown) :
	Component(owner),
	cooldown(cooldown)
{
	elapsed = 0.f;
}

void Shoot::update(float deltaTime)
{
	if (owner->getTag() == "player")
	{
		if (GameManager::getInstance().isKeyPressed(sf::Keyboard::Space))
		{
			auto gameObjects = GameManager::getInstance().getCurrentScene()->getGameObjects();
			std::shared_ptr <GameObject> closestEnemy = nullptr;
			float minDis = 1e9;

			for (auto& obj : gameObjects)
			{
				if (obj->getTag() == "enemies")
				{
					float dx = owner->getHitbox().getPosition().x - obj->getHitbox().getPosition().x;
					float dy = owner->getHitbox().getPosition().y - obj->getHitbox().getPosition().y;
					float curDis = std::sqrt(dx * dx + dy * dy);
					if (curDis < minDis)
					{
						minDis = curDis;
						closestEnemy = obj;
					}
				}
			}

			if (closestEnemy)
			{
				sf::Vector2f size(20.f, 5.f);

				// Tính hướng từ player đến enemy
				sf::Vector2f dir = closestEnemy->getOrigin() - owner->getOrigin();
				float angle = std::atan2(dir.y, dir.x) * 180.f / 3.14159265f; // Đổi sang độ

				// Lật player về phía enemy gần nhất
				float playerX = owner->getOrigin().x;
				float enemyX = closestEnemy->getOrigin().x;
				bool flipped = (enemyX < playerX);// true nếu enemy bên trái, false nếu bên phải
				owner->setFlipped(flipped);

				auto bullet = GameObjectFactory::createBullet(owner->getOrigin(), size);
				bullet->getHitbox().setFillColor(sf::Color::Green);
				bullet->getHitbox().setRotation(angle); // Xoay viên đạn theo hướng bắn
				bullet->addComponent(std::make_shared<MoveForward>(bullet, closestEnemy->getOrigin(), 700.f)); // Thêm speed
				bullet->addComponent(std::make_shared<DamageOnContact>(bullet, owner->getComponent<Stat>()->getDamage(), closestEnemy->getTag())); // Thêm damage
				GameManager::getInstance().getCurrentScene()->addGameObject(bullet);
			}
		}
	}
	else if (owner->getTag() == "enemies")
	{
		elapsed += deltaTime;
		if (elapsed >= cooldown)
		{
			elapsed = 0.f;
			sf::Vector2f size(10.f, 10.f);
			auto bullet = GameObjectFactory::createBullet(owner->getOrigin(),size);
			bullet->getHitbox().setFillColor(sf::Color::Red);
			bullet->addComponent(std::make_shared<MoveForward>(bullet, GameManager::getInstance().currentPlayer->getOrigin(), 300.f)); // Thêm speed
			bullet->addComponent(std::make_shared<DamageOnContact>(bullet, owner->getComponent<Stat>()->getDamage(), "player")); // Thêm damage
			GameManager::getInstance().getCurrentScene()->addGameObject(bullet);
		}
	}
}
	//nếu là player thì bắn khi nhấn space, nếu là enemy thì bắn theo cooldown


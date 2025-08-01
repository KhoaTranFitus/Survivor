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
				if (obj->getTag() == "enemies" || obj->getTag() == "boss")
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
				bullet->addComponent(std::make_shared<DamageOnContact>(bullet, owner->getComponent<Stat>()->getDamage(), "enemies")); // Thêm damage
				bullet->addComponent(std::make_shared<DamageOnContact>(bullet, owner->getComponent<Stat>()->getDamage(), "boss")); // Thêm damage
				GameManager::getInstance().getCurrentScene()->addGameObject(bullet);
			}
		}
	}
	else if (owner->getTag() == "enemies" || owner->getTag() == "boss")
	{
		elapsed += deltaTime;
		if (elapsed >= cooldown)
		{
			elapsed = 0.f;

			sf::Vector2f origin = owner->getOrigin();
			sf::Vector2f target = GameManager::getInstance().currentPlayer->getOrigin();
			sf::Vector2f size(10.f, 10.f);
			if (owner->getTag() == "boss")
			{
				// Bắn 3 tia: thẳng, lệch trái, lệch phải
				float angleToPlayer = std::atan2(target.y - origin.y, target.x - origin.x);
				float spread = 20.0f * 3.14159265f / 180.0f; // 20 độ sang radian

				for (int i = -1; i <= 1; ++i)
				{
					float angle = angleToPlayer + i * spread;
					sf::Vector2f dir(std::cos(angle), std::sin(angle));
					sf::Vector2f bulletTarget = origin + dir * 100.f;

					auto bullet = GameObjectFactory::createBullet(owner->getOrigin(),size);
					bullet->getHitbox().setFillColor(sf::Color::Yellow);
					bullet->getHitbox().setSize(sf::Vector2f(32, 32)); // Đạn to hơn
					bullet->addComponent(std::make_shared<MoveForward>(bullet, GameManager::getInstance().currentPlayer->getOrigin(), 350.f));
					bullet->addComponent(std::make_shared<DamageOnContact>(bullet, owner->getComponent<Stat>()->getDamage(), "player"));
					GameManager::getInstance().getCurrentScene()->addGameObject(bullet);
				}
			}
			else // enemy thường
			{
				auto bullet = GameObjectFactory::createBullet(owner->getOrigin(),size);
				bullet->getHitbox().setFillColor(sf::Color::Red);
				bullet->addComponent(std::make_shared<MoveForward>(bullet, GameManager::getInstance().currentPlayer->getOrigin(), 300.f));
				bullet->addComponent(std::make_shared<DamageOnContact>(bullet, owner->getComponent<Stat>()->getDamage(), "player"));
				GameManager::getInstance().getCurrentScene()->addGameObject(bullet);
			}
		}
	}
}
	//nếu là player thì bắn khi nhấn space, nếu là enemy thì bắn theo cooldown


#include "PlayerShoot.h"
#include "GameManager.h"
#include "MoveForward.h"
#include "DamageOnContact.h"
#include "GameObjectFactory.h"

PlayerShoot::PlayerShoot(std::shared_ptr<GameObject> owner, float cooldown)
	: Component(owner), cooldown(cooldown), elapsed(0.f) {
}

void PlayerShoot::update(float deltaTime)
{
	elapsed += deltaTime;

	// N?u ?ang trong th?i gian animation fire
	if (fireAnimTimer > 0.f) {
		fireAnimTimer -= deltaTime;
		isFiring = true;
		if (fireAnimTimer <= 0.f) {
			isFiring = false;
		}
		return;
	}

	// T? ??ng b?n khi ?? cooldown


	auto gameObjects = GameManager::getInstance().getCurrentScene()->getGameObjects();
	std::shared_ptr<GameObject> closestEnemy = nullptr;
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

	// Ch? b?n khi có enemy
	if (elapsed >= cooldown && closestEnemy)
	{
		elapsed = 0.f;
		fireAnimTimer = fireAnimDuration;
		isFiring = true;

		sf::Vector2f size(20.f, 5.f);

		// Tính h??ng t? player ??n enemy
		sf::Vector2f dir = closestEnemy->getOrigin() - owner->getOrigin();
		float angle = std::atan2(dir.y, dir.x) * 180.f / 3.14159265f;

		// L?t player v? phía enemy g?n nh?t
		float playerX = owner->getOrigin().x;
		float enemyX = closestEnemy->getOrigin().x;
		bool flipped = (enemyX < playerX);
		owner->setFlipped(flipped);

		auto bullet = GameObjectFactory::createBullet(owner->getOrigin(), size,"player_bullet");//add tag for each bullet
		bullet->getHitbox().setFillColor(sf::Color::White);
		bullet->getHitbox().setRotation(angle);
		bullet->addComponent(std::make_shared<MoveForward>(bullet, closestEnemy->getOrigin(), 700.f));
		bullet->addComponent(std::make_shared<DamageOnContact>(bullet, owner->getComponent<Stat>()->getDamage(), "enemies"));
		bullet->addComponent(std::make_shared<DamageOnContact>(bullet, owner->getComponent<Stat>()->getDamage(), "boss"));
		GameManager::getInstance().getCurrentScene()->addGameObject(bullet);
	}
	else {
		isFiring = false;
	}
}
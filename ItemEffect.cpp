#include "ItemEffect.h"
#include "Stat.h"
ItemEffect::ItemEffect(std::shared_ptr<GameObject> owner,
	std::function<std::shared_ptr<Component>(std::shared_ptr<GameObject>)> creator)
	:Component(owner), componentCreator(creator) {}

void ItemEffect::update(float deltaTime) {
	// No update logic needed for ItemEffect
}

void ItemEffect::onCollisionEnter(std::shared_ptr<GameObject> other) {
	if (other->getTag() == "player") {
		auto component = componentCreator(other);
		if (component) {
			component->setOwner(other);
			other->addComponent(component);
		}

		/*auto stat = other->getComponent<Stat>();*/
		//if (stat) {
		//	// Heal
		//	float healValue = stat->getHealth() * 0.2f;
		//	stat->setHealth(std::min(stat->getHealth() + healValue, stat->getMaxHealth()));

		//	// Shield
		//	stat->addShield(50.f, 5.f); // 50 shield, tồn tại 5s

		//	// Speed
		//	float buffAmount = stat->getSpeed() * 0.2f;
		//	stat->addSpeedBuff(buffAmount, 5.f); // tăng 20% tốc độ, tồn tại 5s
		//}

		owner->needDeleted = true;
	}
}
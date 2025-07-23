#include "ItemEffect.h"

ItemEffect::ItemEffect(std::shared_ptr<GameObject> owner,
	std::function<std::shared_ptr<Component>(std::shared_ptr<GameObject>)> creator)
	:Component(owner), componentCreator(creator) {}

void ItemEffect::update(float deltaTime) {
	// No update logic needed for ItemEffect
}

void ItemEffect::onCollisionEnter(std::shared_ptr<GameObject> other) {
	// cho bat ke mọi đối tượng đều nhặt được kể cả enenmy
	if (other->getTag() == "enemies" || other->getTag() == "player") {
		auto component = componentCreator(other);
		if (component) {
			component->setOwner(other);
			other->addComponent(component);
			owner->needDeleted = true; // Destroy the item after applying the effect
		}
	}
}
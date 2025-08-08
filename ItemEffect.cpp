#include "ItemEffect.h"
#include "Assets.h"
ItemEffect::ItemEffect(std::shared_ptr<GameObject> owner,
	std::function<std::shared_ptr<Component>(std::shared_ptr<GameObject>)> creator)
	:Component(owner), componentCreator(creator) {}

void ItemEffect::update(float deltaTime) {
	// No update logic needed for ItemEffect
}

void ItemEffect::onCollisionEnter(std::shared_ptr<GameObject> other) {
	if (other->getTag() == "enemies" || other->getTag() == "player") {
		// cho bat ke mọi đối tượng đều nhặt được kể cả enenmy
		if (other->getTag() == "player") {
			auto component = componentCreator(other);
			if (component) {
				component->setOwner(other);
				other->addComponent(component);
			}
			if (owner->getTag().find("gem") != std::string::npos ) // find tag have "gem" 
			{
				Assets::GEM_PICKUP_SOUND.play();
				Assets::GEM_PICKUP_SOUND.setVolume(30.f);
			}
			else
			{
				Assets::POWERUP_PICKUP_SOUND.play();
			}
			owner->needDeleted = true; // Luôn xóa item/gem sau khi nhặt
		}
	}
}
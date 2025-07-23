#include "DamageOnContact.h"
#include "GameObject.h"
#include "Stat.h"

DamageOnContact::DamageOnContact(std::shared_ptr<GameObject> owner, float damage, std::string targetTag) :
	Component(owner), damage(damage), targetTag(targetTag)
{
}

void DamageOnContact::update(float deltaTime) {}

void DamageOnContact::onCollisionEnter(std::shared_ptr<GameObject> other) {
	if (other->getTag() != targetTag) return;
	other->getComponent<Stat>()->takeDamage(this->damage);

	if (owner->getTag() == "bullet")
	{
		owner->needDeleted = true;
	}
}
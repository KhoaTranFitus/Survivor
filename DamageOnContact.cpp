#include "DamageOnContact.h"
#include "GameObject.h"
#include "Stat.h"
#include "Shield.h" // Add this include

DamageOnContact::DamageOnContact(std::shared_ptr<GameObject> owner, float damage, std::string targetTag, float cooldown)
	: Component(owner), damage(damage), targetTag(targetTag), cooldown(cooldown), timer(0.f)
{
}

void DamageOnContact::update(float deltaTime)
{
	if (timer > 0.0f)
		timer -= deltaTime;
	if (timer < 0.0f)
		timer = 0.0f;
}

void DamageOnContact::onCollisionEnter(std::shared_ptr<GameObject> other)
{
	if (!other) return;
	if (other->getTag() != targetTag) return;
	if (timer <= 0.0f)
	{
		// Nếu có shield thì không trừ máu, bất kể owner là gì
		if (other->getComponent<Shield>()) {
			// Shield is active, ignore damage
			if (owner && (owner->getTag() == "boss_bullet" || owner->getTag() == "player_bullet" || owner->getTag() == "enemy_bullet"))
			{
				owner->needDeleted = true;
			}
			// Nếu là enemy thì không xóa enemy, chỉ bỏ qua damage
			return;
		}

		auto stat = other->getComponent<Stat>();
		if (stat)
		{
			float newHealth = stat->getHealth() - damage;
			stat->setHealth(newHealth);

			other->setAttacked(true);
			other->setHurtTime(0.2f);
			timer = cooldown;
			if (newHealth <= 0)
			{
				if (other->getTag() == "player")
				{
					other->setState(4);
				}
				else if (other->getTag() == "enemies" || other->getTag() == "boss")
				{
					other->needDeleted = true;
				}
			}
		}
		if (owner) {
			std::string tag = owner->getTag();
			if (tag == "player_bullet" || tag == "enemy_bullet") {
				owner->needDeleted = true;
			}
		}
	}
}
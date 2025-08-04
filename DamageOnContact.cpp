#include "DamageOnContact.h"
#include "GameObject.h"
#include "Stat.h"

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
		auto stat = other->getComponent<Stat>();
		if (stat)
		{
			float newHealth = stat->getHealth() - damage;
			stat->setHealth(newHealth);

			// Đánh dấu trạng thái hurt cho player hoặc enemy bị trúng đạn
			other->setAttacked(true);
			other->setHurtTime(0.2f);
			timer = cooldown;
			if (newHealth <= 0)
			{
				if (other->getTag() == "player")
				{
					// Đặt trạng thái DIE cho player
					other->setState(4);
					other->setHurtTime(2.0f); // đợi 2s cho animation DIE chạy
				}
				else if (other->getTag() == "enemies" || other->getTag() == "boss")
				{
					other->needDeleted = true; // enemy, boss chết thì xóa luôn
				}
			}
		}
		// Nếu là bullet (player hoặc enemy) thì xóa luôn sau va chạm
		if (owner) {
			std::string tag = owner->getTag();
			if (tag == "player_bullet" || tag == "enemy_bullet") {
				owner->needDeleted = true;
			}
		}
	}
}
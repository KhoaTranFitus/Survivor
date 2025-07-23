#pragma once
#include "Component.h"
class DamageOnContact :public Component
{
private:
	float damage;
	std::string targetTag;
public:
	DamageOnContact(std::shared_ptr<GameObject> owner, float damage, std::string targetTag) ;
	void update(float deltaTime) override;
	void onCollisionEnter(std::shared_ptr<GameObject> other) override;
};
#include "GameObject.h"
#include "KeyboardMove.h"
#include "PlayerShoot.h"
#include "Shield.h"
#include "Speed.h"
#include "Stat.h"
#include "Assets.h"
GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::addComponent(std::shared_ptr<Component> component)
{
	//component->setOwner(shared_from_this());
	this->components.push_back(component);
}

void GameObject::setTag(const std::string n_tag)
{
	this->tag = n_tag;
}

std::string GameObject::getTag()
{
	return this->tag;
}

void GameObject::setFlipped(bool flipped)
{
	this->flipped = flipped;
}

int GameObject::getCurrentState()
{
	return this->currentState;
}


void GameObject::updateComponents(float deltaTime)
{
	for (auto& component : this->components)
	{
		if (component)
		{
			component->update(deltaTime);
		}
	}
}

void GameObject::onDestroy()
{
}

sf::Vector2f GameObject::getOrigin() const
{
	return this->hitbox.getPosition() + this->hitbox.getSize() / 2.f;
}

void GameObject::onCollisionEnter(std::shared_ptr<GameObject> other)
{
	for (const auto& component : this->components)
	{
		if (component)
		{
			component->onCollisionEnter(other);
		}
	}
}

void GameObject::setState(int num)
{
	this->currentState = num;
}

void GameObject::setAttacked(bool attacked)
{
	this->isAttacked = attacked;
}

void GameObject::setHurtTime(float time)
{
	this->hurtTimer = time;
}

void GameObject::move(sf::Vector2f offset)
{
	this->hitbox.move(offset);
}

sf::RectangleShape& GameObject::getHitbox()
{
	return this->hitbox;
}

void GameObject::update(float deltaTime)
{

	// Ưu tiên trạng thái DIE
	if (currentState == 4) {
		if (!this->animations.empty()) {
			for (auto& a : animations) {
				a->update(deltaTime, flipped);
				a->setPosition(this->hitbox.getPosition());
			}
		}
		return;
	}
	this->updateComponents(deltaTime);

	auto move = getComponent<KeyboardMove>();
	hurtTimer -= deltaTime;
	auto shoot = getComponent<PlayerShoot>();
	// Ưu tiên trạng thái bắn
	if (move) {
		sf::Vector2f currentDirection = move->getDirection();
		if (isAttacked && hurtTimer > 0)
		{
			currentState = 3; // HURT
			Assets::PLAYER_HURT_SOUND.play();
		}
		else if (shoot && shoot->isFiring) {
			currentState = 2; // Fire
		}

		else isAttacked = false;
		if (currentDirection.x != 0.f || currentDirection.y != 0.f) {
			currentState = 1; // Running 
		}
		else {
			currentState = 0; // Idle
		}
		// Compare new direction with the previous direction (on the x-axis)
		if (currentDirection.x != 0 || lastDirection.x != 0) {
			if (lastDirection.x <= 0) {
				flipped = true;
			}
			else if (lastDirection.x > 0) {
				flipped = false;
			}
		}

		// Update the previous direction
		lastDirection = currentDirection;
	}

	if (!this->animations.empty()) {
		for (auto& a : animations) {
			a->update(deltaTime, flipped);
			a->setCenter();
			a->setPosition(this->hitbox.getPosition() + this->hitbox.getSize() / 2.f);
		}
	}
}

void GameObject::render(sf::RenderWindow& window)
{
	if (!animations.empty()) {
		animations[currentState]->render(window);
	}
	else window.draw(this->hitbox);


	for (const auto& component : this->components)
	{
		if (!component) continue;
		//neu la enemies va Boss thi khong 
		if (this->getTag() == "enemies") continue;

		if (isType<Stat>(component))
		{
			component->render(window);
		}
	}
}

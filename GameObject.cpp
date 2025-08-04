#include "GameObject.h"
#include "KeyboardMove.h"
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
	this->updateComponents(deltaTime);

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

	auto move = getComponent<KeyboardMove>();
	hurtTimer -= deltaTime;
	if (move) {
		sf::Vector2f currentDirection = move->getDirection();

		// Determine state based on movement direction
		if (currentDirection.x != 0.f || currentDirection.y != 0.f) {
			currentState = 1; // Running
		}
		else {
			currentState = 0; // Idle
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			currentState = 2; // Update state to 2 when Enter key is pressed
		}
		if (isAttacked && hurtTimer > 0)
		{
			currentState = 3;
		}
		else isAttacked = false;
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
			a->setPosition(this->hitbox.getPosition());
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
		if (component)
		{
			component->render(window);
		}
	}
}

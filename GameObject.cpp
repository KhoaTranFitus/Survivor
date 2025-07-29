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

	auto move = getComponent<KeyboardMove>();
		// So sánh hướng mới với hướng cũ (theo trục x)
	if (move)
	{
		sf::Vector2f currentDirection = move->getDirection();

		// Xác định trạng thái dựa trên hướng di chuyển
		if (currentDirection.x != 0.f || currentDirection.y != 0.f) {
			currentState = 1; // Đang chạy
		}
		else {
			currentState = 0; // Đứng yên
		}

		// So sánh hướng mới với hướng cũ (theo trục x)
		if (currentDirection.x != 0 || lastDirection.x != 0)
		{
			if (lastDirection.x <= 0)
			{
				flipped = true;
			}
			else if (lastDirection.x > 0)
			{
				flipped = false;
			}
		}

		// Cập nhật hướng cũ
		lastDirection = currentDirection;
	}
	if (!this->animations.empty())
	{
		for (auto& a : animations)
		{
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

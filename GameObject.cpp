#include "GameObject.h"

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

void GameObject::markForDestroy()
{
	destroyed = true;
}

void GameObject::revive()
{
	destroyed = false;
}

bool GameObject::isDestroyed()
{
	return destroyed;
}

void GameObject::update(float deltaTime)
{
	this->updateComponents(deltaTime);

	//if (1)
	//{
	//	currentState = INT(PLAYER_STATE::WALKING);
	//}

	//if (!this->animations.empty())
	//{
	//	for (auto& a : animations)
	//	{
	//		a->update(deltaTime, false);
	//		a->setPosition(this->hitbox.getPosition());
	//	}
	//}
}

void GameObject::render(sf::RenderWindow& window)
{
	/*if (!animations.empty()) {
		animations[currentState]->render(window);
	}*/
	window.draw(this->hitbox);

	for (const auto& component : this->components)
	{
		if (component)
		{
			component->render(window);
		}
	}
}

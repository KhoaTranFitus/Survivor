// GameObject.h
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Component.h"
#include "Animation.h"

class GameObject : public std::enable_shared_from_this<GameObject>
{
protected:
    sf::RectangleShape hitbox;
    sf::Sprite sprite;
    std::vector<std::shared_ptr<Component>> components;
    std::vector<std::shared_ptr<Animation>> animations;
    std::string tag;

    bool flipped = false  ;              // true = sang trái
    sf::Vector2f lastDirection = { 0.f,0.f }; // để biết đang đi hướng nào

    bool isAttacked = false;
    int currentState = 0;
    float hurtTimer = 0.f;

public:
    GameObject();
    virtual ~GameObject();

    void addComponent(std::shared_ptr<Component> component);
    void updateComponents(float deltaTime);

    bool needDeleted = false;
	virtual void onDestroy();

    sf::Vector2f getOrigin() const;
    virtual void onCollisionEnter(std::shared_ptr<GameObject> other);

    void setState(int num);
    void setAttacked(bool attacked);
    void setHurtTime(float time);
    template<class T>
    std::shared_ptr<T> getComponent();

    template<class T>
    std::shared_ptr<T> removeComponent();

    void move(sf::Vector2f offset);
    sf::RectangleShape& getHitbox();

    void setTag(const std::string n_tag);
    std::string getTag();

	void setFlipped(bool flipped); 
    int getCurrentState();

    virtual void update(float deltaTime);
    virtual void render(sf::RenderWindow& window);
};

template<class T>
inline std::shared_ptr<T> GameObject::getComponent()
{
    for (const auto& component : components)
    {
        if (isType<T>(component))
        {
            return std::dynamic_pointer_cast<T>(component);
        }
    }
    return nullptr;
}


// xóa component
// ví dụ: người chơi nhặt được khiên trong hiệu lực 5s, ban đầu sẽ thêm component Shield vào người chơi
// nhưng sau 5s thì sẽ xóa component Shield ra khỏi người chơi -> người chơi mất khiên
template<class T>
inline std::shared_ptr<T> GameObject::removeComponent()
{
    for (auto it = components.begin(); it != components.end(); ++it)
    {
        if (isType<T>(*it))
        {
            std::shared_ptr<T> removedComponent = std::dynamic_pointer_cast<T>(*it);
            components.erase(it);
            return removedComponent;
        }
    }
    return nullptr;
}
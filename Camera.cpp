#include "Camera.h"
#include "GameManager.h"
Camera::Camera()
{
    this->position = sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    this->velocity = sf::Vector2f(0, 0);
}

Camera::~Camera()
{
}

const sf::View Camera::getView(sf::Vector2u windowSize)
{
    float aspect = float(windowSize.x) / float(windowSize.y);
    float zoom_level = 720.f;

    if (aspect > 1.f)
    {
        size = sf::Vector2f(zoom_level * aspect, zoom_level);
    }
    else
    {
        size = sf::Vector2f(zoom_level, zoom_level / aspect);
    }
    // for screen view

    return sf::View(this->position, size);
}

const sf::Vector2f Camera::getPosition() const
{
    return this->position;
}

void Camera::setPosition(sf::Vector2f position)
{
    this->position = position;
}

void Camera::move(sf::Vector2f velocity)
{
    this->position += velocity;
}

sf::Vector2f Camera::getSize()
{
    return this->size;
}
//get the rectangle of the view
sf::FloatRect Camera::getViewRect() const {
    return sf::FloatRect(
        position.x - size.x / 2,
        position.y - size.y / 2,
        size.x,
        size.y
    );
}
void Camera::update(float deltaTime, sf::Vector2f playerPosition)
{
    sf::Vector2f offset = playerPosition - this->position;

    float CAMERA_FOLLOW_DISTANCE = 50.f; // Distance to follow the player
    float CAMERA_SMOOTHING_FACTOR = 5.f; // Smoothing factor for camera movement

    if (std::abs(offset.x) > CAMERA_FOLLOW_DISTANCE)
    {
        velocity.x = (offset.x - CAMERA_FOLLOW_DISTANCE * (offset.x > 0 ? 1 : -1)) * CAMERA_SMOOTHING_FACTOR;
    }
    else
    {
        velocity.x = 0.f;
    }

    if (std::abs(offset.y) > CAMERA_FOLLOW_DISTANCE)
    {
        velocity.y = (offset.y - CAMERA_FOLLOW_DISTANCE * (offset.y > 0 ? 1 : -1)) * CAMERA_SMOOTHING_FACTOR;
    }
    else
    {
        velocity.y = 0.f;
    }

    this->move(this->velocity * deltaTime);
}
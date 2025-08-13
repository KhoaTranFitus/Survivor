#include "Stat.h"
#include "GameObject.h"

Stat::Stat(std::shared_ptr<GameObject> owner, float health, float damage) :
	Component(owner), health(health), maxHealth(health), damage(damage) // Gán maxHealth = health ban ??u
{
	//neu la enemy thi ko ender health bar
	if (owner->getTag() == "player")
	{
	this->healthBar.setSize(sf::Vector2f(50.f, 12.f));
	this->healthBar.setFillColor(sf::Color::Green);
	auto hitbox = this->owner->getHitbox();
	offset.x = hitbox.getPosition().x + hitbox.getSize().x / 2 - this->healthBar.getSize().x / 2;
	offset.y = hitbox.getPosition().y - this->healthBar.getSize().y - 5;
	offset = offset - hitbox.getPosition();
	}
		auto hitbox = this->owner->getHitbox();
		offset.x = hitbox.getPosition().x + hitbox.getSize().x / 2 - this->healthBar.getSize().x / 2;
		offset.y = hitbox.getPosition().y - this->healthBar.getSize().y - 10;
		offset = offset - hitbox.getPosition();
	updateHealthBar();
}

void Stat::update(float deltaTime)
{
	auto hitbox = this->owner->getHitbox();

	this->healthBar.setPosition(hitbox.getPosition() + offset);
}

void Stat::render(sf::RenderWindow& window)
{
        if (owner->getTag() == "player")
        {
            // Lấy vị trí trên đầu hitbox player
            auto hitbox = owner->getHitbox();
            sf::Vector2f barPos = hitbox.getPosition() + offset;

            float hpPercent = health / maxHealth;
            float barWidth = 50.f;
            float barHeight = 7.f;

            // ===== Background =====
            sf::RectangleShape background(sf::Vector2f(barWidth, barHeight));
            background.setFillColor(sf::Color::Red); // xám tối
            background.setPosition(barPos);
            window.draw(background);

            // ===== Thanh máu =====
            sf::RectangleShape hpBar(sf::Vector2f(barWidth * hpPercent, barHeight));
            hpBar.setFillColor(sf::Color::Green);
            hpBar.setPosition(barPos);
            window.draw(hpBar);

            // ===== Viền =====
            sf::RectangleShape border(sf::Vector2f(barWidth, barHeight));
            border.setFillColor(sf::Color::Transparent);
            border.setOutlineColor(sf::Color::Yellow);
            border.setOutlineThickness(1.f);
            border.setPosition(barPos);
            window.draw(border);
        }
        else if (owner->getTag() == "boss") {
        
            sf::View oldView = window.getView();
            window.setView(window.getDefaultView());

            float hp = this->getHealth();
            float maxHp = this->getMaxHealth();
            float percent = std::max(0.f, std::min(1.f, hp / maxHp));

            // Vị trí và kích thước
            float barWidth = 500.f;
            float barHeight = 22.f;
            float windowWidth = window.getSize().x;
            float bossBarY = barHeight + 32.f; // Dưới exp bar 16px

            float barX = (windowWidth - barWidth) / 2.f;

            // Khung nền máu boss
            sf::RectangleShape bossBarBg(sf::Vector2f(barWidth, barHeight));
            bossBarBg.setFillColor(sf::Color(60, 20, 20));
            bossBarBg.setPosition(barX, bossBarY);

            // Thanh máu boss
            sf::RectangleShape bossBar(sf::Vector2f(barWidth * percent, barHeight));
            bossBar.setFillColor(sf::Color(255, 40, 40));
            bossBar.setPosition(barX, bossBarY);

            // Viền
            sf::RectangleShape border(sf::Vector2f(barWidth, barHeight));
            border.setFillColor(sf::Color::Transparent);
            border.setOutlineColor(sf::Color::Yellow);
            border.setOutlineThickness(1.5f);
            border.setPosition(barX, bossBarY);

            window.draw(bossBarBg);
            window.draw(bossBar);
            window.draw(border);
            window.setView(oldView);
        }

}

float Stat::getHealth()
{
	return this->health;
}

float Stat::getDamage()
{
	return this->damage;
}

float Stat::getMaxHealth()
{
	return maxHealth;
}

void Stat::setHealth(float value)
{
	health = value;
	if (health > maxHealth) health = maxHealth;
	if (health < 0) health = 0;
	updateHealthBar();
}

void Stat::setDamage(float value)
{
	damage = value;
}

void Stat::updateHealthBar()
{
	float percent = (maxHealth > 0) ? (health / maxHealth) : 0.f;
	if (percent < 0) percent = 0;
	healthBar.setSize(sf::Vector2f(50 * percent, 10));
}



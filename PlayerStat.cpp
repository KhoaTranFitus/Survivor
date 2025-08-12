#include "PlayerStat.h"
#include <sstream>
#include "GameManager.h"
#include "LevelUpScene.h"
#include "GamePlayScene.h"
#include "Assets.h"
PlayerStat::PlayerStat(std::shared_ptr<GameObject> owner) :Component(owner)
{
    this->owner = owner;
    level = 1;
    exp = 0;
    expToNextLevel = 100; // Giả sử cần 100 exp để lên level đầu tiên
}

void PlayerStat::addExp(int amount)
{
    exp += amount;
    while (exp >= expToNextLevel) {
        exp -= expToNextLevel;
        level++;
        std::cout << "Level up! New level: " << level << std::endl;
        expToNextLevel *= 1.1f;
        // Show LevelUpScene
        auto gameplayScene = std::dynamic_pointer_cast<GamePlayScene>(GameManager::getInstance().getCurrentScene());
        GameManager::getInstance().setScene(
            std::make_shared<LevelUpScene>(owner, gameplayScene)
        );
    }
}

void PlayerStat::update(float deltaTime)
{
}

void PlayerStat::render(sf::RenderWindow& window, const sf::Font& font) {
    // Kích thước và vị trí thanh exp
    float barWidth = 400.f;
    float barHeight = 22.f;
    float windowWidth = window.getSize().x;
    float barX = (windowWidth - barWidth) / 2.f;
    float barY = 16.f;

    // Level box
    float levelBoxWidth = 60.f;
    float levelBoxHeight = barHeight + 8.f;
    float levelBoxX = barX - levelBoxWidth - 10.f;
    float levelBoxY = barY - 4.f;

    // Vẽ khung level
    sf::RectangleShape levelBox(sf::Vector2f(levelBoxWidth, levelBoxHeight));
    levelBox.setFillColor(sf::Color(40, 40, 40));
    levelBox.setOutlineColor(sf::Color::White);
    levelBox.setOutlineThickness(2.f);
    levelBox.setPosition(levelBoxX, levelBoxY);
    window.draw(levelBox);

    // Vẽ số level
    std::ostringstream oss;
    oss << "Lv " << getLevel();
    sf::Text levelText(oss.str(), font, 22);
    levelText.setFillColor(sf::Color::White);
    sf::FloatRect textRect = levelText.getLocalBounds();
    levelText.setPosition(
        levelBoxX + (levelBoxWidth - textRect.width) / 2.f,
        levelBoxY + (levelBoxHeight - textRect.height) / 2.f - 4.f
    );
    window.draw(levelText);

	// Hiển thị viền thanh exp
    sf::RectangleShape border(sf::Vector2f(barWidth, barHeight));
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineColor(sf::Color::White);
    border.setOutlineThickness(1.5f);
    border.setPosition(barX, barY);
    window.draw(border);

    // Hiển thị thanh exp
    int exp = getExp();
    int expToNext = getExpToNextLevel();
    float percent = static_cast<float>(exp) / expToNext;

    // Khung nền exp
    sf::RectangleShape expBarBg(sf::Vector2f(barWidth, barHeight));
    expBarBg.setFillColor(sf::Color(50, 50, 50));
    expBarBg.setPosition(barX, barY);

    // Thanh exp
    sf::RectangleShape expBar(sf::Vector2f(barWidth * percent, barHeight));
    expBar.setFillColor(sf::Color(255, 165, 0)); // Màu cam
    expBar.setPosition(barX, barY);

    window.draw(expBarBg);
    window.draw(expBar);

    // Text exp
    std::ostringstream expText;
    expText << static_cast<int>(exp) << " / " << static_cast<int>(expToNext);
    sf::Text expValue(expText.str(), font, 16);
    expValue.setFillColor(sf::Color::White);
    sf::FloatRect expRect = expValue.getLocalBounds();
    expValue.setPosition(
        barX + (barWidth - expRect.width) / 2.f,
        barY + (barHeight - expRect.height) / 2.f - 2.f
    );
    window.draw(expValue);
}
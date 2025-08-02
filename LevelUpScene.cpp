#include "LevelUpScene.h"
#include "GameManager.h"
#include "Stat.h"
#include "Speed.h"
#include "Heal.h"
#include <SFML/Graphics.hpp>
#include <random>
#include <algorithm>

LevelUpScene::LevelUpScene() {}

LevelUpScene::LevelUpScene(std::shared_ptr<Scene> prev)
    : previousScene(prev)
{
    auto player = GameManager::getInstance().currentPlayer;
    auto stat = player ? player->getComponent<Stat>() : nullptr;

    std::vector<SkillNode> allSkills;

    if (stat && stat->damageUpgradeLevel < 5) {
        allSkills.push_back({
            "Tăng Sát Thương",
            "Tăng sát thương gốc +5 (Hiện tại: " + std::to_string(stat->damageUpgradeLevel) + "/5)",
            stat->damageUpgradeLevel, 5,
            [stat]() { stat->upgradeBaseDamage(); }
            });
    }

    if (player && stat && stat->healthUpgradeLevel < 5) {
        allSkills.push_back({
            "Hồi Máu",
            "Hồi 20% máu gốc (Hiện tại: " + std::to_string(stat->healthUpgradeLevel) + "/5)",
            stat->healthUpgradeLevel, 5,
            [player]() {
                auto stat = player->getComponent<Stat>();
                float maxHp = stat->getMaxHealth();
                player->addComponent(std::make_shared<Heal>(player, maxHp * 0.2f));
            }
            });
    }

    if (player && stat && stat->reloadUpgradeLevel < 5) {
        allSkills.push_back({
            "Tăng Tốc Độ Bắn",
            "Giảm thời gian reload 10% (Hiện tại: " + std::to_string(stat->reloadUpgradeLevel) + "/5)",
            stat->reloadUpgradeLevel, 5,
            [stat]() { stat->upgradeBaseReload(); }
            });
    }

    if (player && stat && stat->speedUpgradeLevel < 5) {
        allSkills.push_back({
            "Tăng Tốc Độ Chạy",
            "Tăng tốc độ chạy 30% trong 5s (Hiện tại: " + std::to_string(stat->speedUpgradeLevel) + "/5)",
            stat->speedUpgradeLevel, 5,
            [player]() {
                player->addComponent(std::make_shared<Speed>(player, 0.3f, 5.f));
            }
            });
    }

    std::shuffle(allSkills.begin(), allSkills.end(), std::mt19937(std::random_device()()));
    for (int i = 0; i < 3 && i < allSkills.size(); ++i) {
        skills.push_back(allSkills[i]);
    }
}

void LevelUpScene::update(float deltaTime)
{
    handleInput();
}

void LevelUpScene::handleInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && skills.size() > 0) {
        skills[0].onUpgrade();
        GameManager::getInstance().setScene(previousScene);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && skills.size() > 1) {
        skills[1].onUpgrade();
        GameManager::getInstance().setScene(previousScene);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && skills.size() > 2) {
        skills[2].onUpgrade();
        GameManager::getInstance().setScene(previousScene);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) selected = std::max(0, selected - 1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) selected = std::min((int)skills.size() - 1, selected + 1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !skills.empty()) {
        skills[selected].onUpgrade();
        GameManager::getInstance().setScene(previousScene);
    }
}

void LevelUpScene::render(sf::RenderWindow& window)
{
    window.clear(sf::Color(30, 30, 30));
    float width = window.getSize().x;
    float height = window.getSize().y;

    sf::RectangleShape panel(sf::Vector2f(width * 0.8f, height * 0.7f));
    panel.setPosition(width * 0.1f, height * 0.15f);
    panel.setFillColor(sf::Color(50, 50, 60));
    panel.setOutlineThickness(5.f);
    panel.setOutlineColor(sf::Color::White);
    window.draw(panel);

    sf::Font font;
    font.loadFromFile("arial.ttf");

    sf::Text title("LEVEL UP! CHON 1 KY NANG", font, 36);
    title.setFillColor(sf::Color::Yellow);
    title.setStyle(sf::Text::Bold);
    title.setPosition(width / 2.f - title.getGlobalBounds().width / 2.f, height * 0.18f);
    window.draw(title);

    float skillBoxWidth = 180.f;
    float skillBoxHeight = 200.f;
    float gap = 60.f;
    float startX = width / 2.f - (skills.size() * (skillBoxWidth + gap) - gap) / 2.f;
    float y = height * 0.3f;

    for (int i = 0; i < skills.size(); ++i) {
        sf::Vector2f pos(startX + i * (skillBoxWidth + gap), y);

        sf::RectangleShape box(sf::Vector2f(skillBoxWidth, skillBoxHeight));
        box.setPosition(pos);
        box.setFillColor(i == selected ? sf::Color(100, 160, 255) : sf::Color(70, 70, 80));
        box.setOutlineThickness(3);
        box.setOutlineColor(sf::Color::Red);
        window.draw(box);

        sf::Text name(skills[i].name, font, 22);
        name.setFillColor(sf::Color::White);
        name.setStyle(sf::Text::Bold);
        name.setPosition(pos.x + 10, pos.y + 10);
        window.draw(name);

        sf::Text desc(skills[i].description, font, 16);
        desc.setFillColor(sf::Color(200, 200, 200));
        desc.setPosition(pos.x + 10, pos.y + 50);
        window.draw(desc);

        for (int j = 0; j < skills[i].maxLevel; ++j) {
            sf::Text star((j < skills[i].currentLevel) ? "★" : "☆", font, 24);
            star.setFillColor((j < skills[i].currentLevel) ? sf::Color::Yellow : sf::Color(100, 100, 100));
            star.setPosition(pos.x + 15 + j * 25, pos.y + skillBoxHeight - 40);
            window.draw(star);
        }
    }

    sf::Text note("<- or -> De Di Chuyen | Enter De Chon | 1/2/3 ", font, 22);
    note.setFillColor(sf::Color(180, 180, 180));
    note.setPosition(width / 2.f - note.getGlobalBounds().width / 2.f, height * 0.85f);
    window.draw(note);
}

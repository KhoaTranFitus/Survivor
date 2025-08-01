#include "LevelUpScene.h"
#include "GameManager.h"
#include "Stat.h"
#include <SFML/Graphics.hpp>
#include <random>
#include <algorithm>


LevelUpScene::LevelUpScene() {
 
}

LevelUpScene::LevelUpScene(std::shared_ptr<Scene> prev)
    : previousScene(prev)
{
    // Lấy Stat của player
    auto player = GameManager::getInstance().currentPlayer;
    auto stat = player ? player->getComponent<Stat>() : nullptr;

    // Danh sách tất cả các skill
    std::vector<SkillNode> allSkills;

    if (stat && stat->damageUpgradeLevel < 5) {
        allSkills.push_back({
            "Tăng Sát Thương",
            "Tăng sát thương gốc +5 (Hiện tại: " + std::to_string(stat->damageUpgradeLevel) + "/5)",
            stat->damageUpgradeLevel, 5,
            [stat]() { stat->upgradeBaseDamage(); }
        });
    }
    if (stat && stat->healthUpgradeLevel < 5) {
        allSkills.push_back({
            "Tăng Máu",
            "Tăng máu gốc +20 (Hiện tại: " + std::to_string(stat->healthUpgradeLevel) + "/5)",
            stat->healthUpgradeLevel, 5,
            [stat]() { stat->upgradeBaseHealth(); }
        });
    }
    if (stat && stat->reloadUpgradeLevel < 5) {
        allSkills.push_back({
            "Tăng Tốc Độ Bắn",
            "Giảm thời gian reload 10% (Hiện tại: " + std::to_string(stat->reloadUpgradeLevel) + "/5)",
            stat->reloadUpgradeLevel, 5,
            [stat]() { stat->upgradeReload(); }
        });
    }
    if (stat && stat->speedUpgradeLevel < 5) {
        allSkills.push_back({
            "Tăng Tốc Độ Chạy",
            "Tăng tốc độ chạy gốc +30 (Hiện tại: " + std::to_string(stat->speedUpgradeLevel) + "/5)",
            stat->speedUpgradeLevel, 5,
            [stat]() { stat->upgradeBaseSpeed(); }
        });
    }

    // Random 3 skill không trùng nhau
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
    // Chọn skill bằng phím 1, 2, 3 hoặc Enter/Space
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
    // Dùng phím mũi tên để chọn, Enter để xác nhận
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) selected = std::max(0, selected - 1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) selected = std::min((int)skills.size() - 1, selected + 1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !skills.empty()) {
        skills[selected].onUpgrade();
        GameManager::getInstance().setScene(previousScene);
    }
}

//void LevelUpScene::render(sf::RenderWindow& window)
//{
//    window.clear(sf::Color(30, 30, 30));
//    float width = window.getSize().x;
//    float height = window.getSize().y;
//    float boxWidth = width / 4.f;
//    float boxHeight = height * 0.6f;
//    float startX = width / 2.f - (boxWidth * 1.5f);
//
//    sf::Font font;
//    font.loadFromFile("arial.ttf");
//
//    for (int i = 0; i < skills.size(); ++i) {
//        sf::RectangleShape box(sf::Vector2f(boxWidth, boxHeight));
//        box.setPosition(startX + i * (boxWidth + 20), height / 2.f - boxHeight / 2.f);
//        box.setFillColor(i == selected ? sf::Color(100, 200, 255) : sf::Color(60, 60, 60));
//        window.draw(box);
//
//        sf::Text name(skills[i].name, font, 28);
//        name.setFillColor(sf::Color::White);
//        name.setPosition(box.getPosition().x + 20, box.getPosition().y + 20);
//        window.draw(name);
//
//        sf::Text desc(skills[i].description, font, 20);
//        desc.setFillColor(sf::Color(200, 200, 200));
//        desc.setPosition(box.getPosition().x + 20, box.getPosition().y + 70);
//        window.draw(desc);
//
//        sf::Text level("Level: " + std::to_string(skills[i].currentLevel) + "/" + std::to_string(skills[i].maxLevel), font, 20);
//        level.setFillColor(sf::Color::Yellow);
//        level.setPosition(box.getPosition().x + 20, box.getPosition().y + boxHeight - 40);
//        window.draw(level);
//    }
//
//    sf::Text title("LEVEL UP! Chon 1 nang cap (1/2/3 hoac Enter)", font, 32);
//    title.setFillColor(sf::Color::Green);
//    title.setPosition(width / 2.f - 250, 50);
//    window.draw(title);
//}

//void LevelUpScene::render(sf::RenderWindow& window)
//{
//    window.clear(sf::Color(30, 30, 30));
//    float width = window.getSize().x;
//    float height = window.getSize().y;
//    float boxWidth = 150.f;
//    float boxHeight = 150.f;
//    float spacing = 50.f;
//    float totalWidth = 3 * boxWidth + 2 * spacing;
//    float startX = (width - totalWidth) / 2.f;
//    float topY = height / 2.f - boxHeight / 2.f;
//
//    sf::Font font;
//    if (!font.loadFromFile("arial.ttf")) {
//        std::cerr << "Không thể load font arial.ttf\n";
//        return;
//    }
//
//    // Tiêu đề
//    sf::Text title("Weapon Skill", font, 36);
//    title.setFillColor(sf::Color::Yellow);
//    title.setStyle(sf::Text::Bold);
//    title.setPosition(width / 2.f - title.getLocalBounds().width / 2.f, 50);
//    window.draw(title);
//
//    // Vẽ các skill
//    for (int i = 0; i < skills.size(); ++i) {
//        sf::Vector2f boxPos(startX + i * (boxWidth + spacing), topY);
//
//        // Khung kỹ năng
//        sf::RectangleShape box(sf::Vector2f(boxWidth, boxHeight));
//        box.setPosition(boxPos);
//        box.setFillColor(i == selected ? sf::Color(90, 140, 255) : sf::Color(80, 80, 80));
//        box.setOutlineColor(sf::Color::White);
//        box.setOutlineThickness(2);
//        window.draw(box);
//
//        // Placeholder icon (sẽ thay bằng ảnh sau)
//        sf::CircleShape icon(25);
//        icon.setFillColor(sf::Color::Green);
//        icon.setPosition(boxPos.x + boxWidth / 2.f - 25, boxPos.y + 20);
//        window.draw(icon);
//
//        // Dòng sao
//        for (int j = 0; j < skills[i].maxLevel; ++j) {
//            sf::Text starText((j < skills[i].currentLevel) ? "★" : "☆", font, 22);
//            starText.setFillColor((j < skills[i].currentLevel) ? sf::Color::Yellow : sf::Color(150, 150, 150));
//            float starX = boxPos.x + boxWidth / 2.f - (skills[i].maxLevel * 12) + j * 24;
//            float starY = boxPos.y + boxHeight - 35;
//            starText.setPosition(starX, starY);
//            window.draw(starText);
//        }
//
//        // Tên kỹ năng
//        sf::Text name(skills[i].name, font, 18);
//        name.setFillColor(sf::Color::White);
//        name.setPosition(boxPos.x + 10, boxPos.y + boxHeight - 70);
//        window.draw(name);
//    }
//
//    // Hướng dẫn chọn
//    sf::Text guide("Chon nang cap: [1], [2], [3] hoac mui ten + Enter", font, 20);
//    guide.setFillColor(sf::Color::White);
//    guide.setPosition(width / 2.f - guide.getLocalBounds().width / 2.f, height - 60);
//    window.draw(guide);
//}

void LevelUpScene::render(sf::RenderWindow& window)
{
    window.clear(sf::Color(30, 30, 30));
    float width = window.getSize().x;
    float height = window.getSize().y;

    // ========== Vẽ khung chính ==========
    sf::RectangleShape panel(sf::Vector2f(width * 0.8f, height * 0.7f));
    panel.setPosition(width * 0.1f, height * 0.15f);
    panel.setFillColor(sf::Color(50, 50, 60));
    panel.setOutlineThickness(5.f);
    panel.setOutlineColor(sf::Color::White);
    window.draw(panel);

    // ========== Font ==========
    sf::Font font;
    font.loadFromFile("arial.ttf");

    // ========== Vẽ tiêu đề ==========
    sf::Text title("LEVEL UP! CHON 1 KY NANG", font, 36);
    title.setFillColor(sf::Color::Yellow);
    title.setStyle(sf::Text::Bold);
    title.setPosition(width / 2.f - title.getGlobalBounds().width / 2.f, height * 0.18f);
    window.draw(title);

    // ========== Vẽ từng kỹ năng ==========
    float skillBoxWidth = 180.f;
    float skillBoxHeight = 200.f;
    float gap = 60.f;
    float startX = width / 2.f - (skills.size() * (skillBoxWidth + gap) - gap) / 2.f;
    float y = height * 0.3f;

    for (int i = 0; i < skills.size(); ++i) {
        sf::Vector2f pos(startX + i * (skillBoxWidth + gap), y);

        // Khung mỗi skill
        sf::RectangleShape box(sf::Vector2f(skillBoxWidth, skillBoxHeight));
        box.setPosition(pos);
        box.setFillColor(i == selected ? sf::Color(100, 160, 255) : sf::Color(70, 70, 80));
        box.setOutlineThickness(3);
        box.setOutlineColor(sf::Color::Red);
        window.draw(box);

        // Tên kỹ năng
        sf::Text name(skills[i].name, font, 22);
        name.setFillColor(sf::Color::White);
        name.setStyle(sf::Text::Bold);
        name.setPosition(pos.x + 10, pos.y + 10);
        window.draw(name);
        

        // Mô tả
        sf::Text desc(skills[i].description, font, 16);
        desc.setFillColor(sf::Color(200, 200, 200));
        desc.setPosition(pos.x + 10, pos.y + 50);
        window.draw(desc);

        // Các sao hiển thị cấp độ
        for (int j = 0; j < skills[i].maxLevel; ++j) {
            sf::Text star((j < skills[i].currentLevel) ? "★" : "☆", font, 24);
            star.setFillColor((j < skills[i].currentLevel) ? sf::Color::Yellow : sf::Color(100, 100, 100));
            star.setPosition(pos.x + 15 + j * 25, pos.y + skillBoxHeight - 40);
            window.draw(star);
        }
    }

    // Gợi ý điều khiển
    sf::Text note("<- or -> De Di Chuyen | Enter De Chon | 1/2/3 ", font, 22);
    note.setFillColor(sf::Color(180, 180, 180));
    note.setPosition(width / 2.f - note.getGlobalBounds().width / 2.f, height * 0.85f);
    window.draw(note);
}


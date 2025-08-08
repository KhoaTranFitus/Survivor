#include "LevelUpScene.h"
#include "PlayerDamageUpgrade.h"
#include "PlayerSpeedUpgrade.h"
#include "PlayerHealthUpgrade.h"
#include "PlayerReloadUpgrade.h"
#include "PlayerMagnetUpgrade.h"
#include "GameManager.h"
#include "SwitchSceneCommand.h"
#include "GamePlayScene.h"
#include <random>
#include <SFML/Graphics.hpp>

static const char* skillNames[5] = {
    "Damage Up", "Speed Up", "Health Up", "Reload Up", "Magnet Up"
};

LevelUpScene::LevelUpScene(std::shared_ptr<GameObject> player, std::shared_ptr<GamePlayScene> gamePlayScene)
    : player(player), gamePlayScene(gamePlayScene)
{
    // Build a list of skills that are not maxed out
    std::vector<int> availableSkills;
    if (!player->getComponent<PlayerDamageUpgrade>() || player->getComponent<PlayerDamageUpgrade>()->getLevel() < 5)
        availableSkills.push_back(0);
    if (!player->getComponent<PlayerSpeedUpgrade>() || player->getComponent<PlayerSpeedUpgrade>()->getLevel() < 5)
        availableSkills.push_back(1);
    if (!player->getComponent<PlayerHealthUpgrade>() || player->getComponent<PlayerHealthUpgrade>()->getLevel() < 5)
        availableSkills.push_back(2);
    if (!player->getComponent<PlayerReloadUpgrade>() || player->getComponent<PlayerReloadUpgrade>()->getLevel() < 5)
        availableSkills.push_back(3);
    if (!player->getComponent<PlayerMagnetUpgrade>() || player->getComponent<PlayerMagnetUpgrade>()->getLevel() < 5)
        availableSkills.push_back(4);

    // Shuffle and pick up to 3 skills
    std::shuffle(availableSkills.begin(), availableSkills.end(), std::mt19937{std::random_device{}()});
    selectedSkills.clear();
    for (int i = 0; i < 3 && i < availableSkills.size(); ++i)
        selectedSkills.push_back(availableSkills[i]);

    float startY = 400.f; // Y position for all buttons (centered vertically)
    float buttonHeight = 100.f;
    float buttonWidth = 300.f;
    float spacing = 40.f; // Space between buttons
    float totalWidth = 3 * buttonWidth + 2 * spacing;
    float windowWidth = 1280.f; // Or use window.getSize().x if available
    float buttonY = startY;
    float buttonX = (windowWidth - totalWidth) / 2.f; // Center the row

    for (int i = 0; i < selectedSkills.size(); ++i) {
        int skillIdx = selectedSkills[i];
        std::string btnText = skillNames[skillIdx];
        btnText += " Lv.";

        // Get current level
        int curLevel = 0;
        switch (skillIdx) {
        case 0: {
            auto comp = player->getComponent<PlayerDamageUpgrade>();
            curLevel = comp ? comp->getLevel() : 0;
            break;
        }
        case 1: {
            auto comp = player->getComponent<PlayerSpeedUpgrade>();
            curLevel = comp ? comp->getLevel() : 0;
            break;
        }
        case 2: {
            auto comp = player->getComponent<PlayerHealthUpgrade>();
            curLevel = comp ? comp->getLevel() : 0;
            break;
        }
        case 3: {
            auto comp = player->getComponent<PlayerReloadUpgrade>();
            curLevel = comp ? comp->getLevel() : 0;
            break;
        }
        case 4: {
            auto comp = player->getComponent<PlayerMagnetUpgrade>();
            curLevel = comp ? comp->getLevel() : 0;
            break;
        }
        }
        btnText += std::to_string(curLevel + 1);

        auto button = std::make_shared<Button>(
            btnText, "skill",
            buttonX + i * (buttonWidth + spacing), buttonY,
            sf::Vector2f(buttonWidth, buttonHeight),
            std::make_shared<SwitchSceneCommand>([this, i, gamePlayScene]() {
                this->onSkillSelected(i);
                return gamePlayScene;
            })
        );
        skillButtons.push_back(button);
    }
    buttons = skillButtons;
}

void LevelUpScene::onSkillSelected(int skillIndex) {
    int skillIdx = selectedSkills[skillIndex];
    switch (skillIdx) {
        case 0: {
            auto comp = player->getComponent<PlayerDamageUpgrade>();
            if (comp) {
                if (comp->getLevel() < 5) comp->upgrade();
                // else do nothing
            }
            else {
                player->addComponent(std::make_shared<PlayerDamageUpgrade>(player));
            }
            break;
        }
        case 1: {
            auto comp = player->getComponent<PlayerSpeedUpgrade>();
            if (comp) comp->upgrade();
            else player->addComponent(std::make_shared<PlayerSpeedUpgrade>(player));
            break;
        }
        case 2: {
            auto comp = player->getComponent<PlayerHealthUpgrade>();
            if (comp) comp->upgrade();
            else player->addComponent(std::make_shared<PlayerHealthUpgrade>(player));
            break;
        }
        case 3: {
            auto comp = player->getComponent<PlayerReloadUpgrade>();
            if (comp) comp->upgrade();
            else player->addComponent(std::make_shared<PlayerReloadUpgrade>(player));
            break;
        }
        case 4: {
            auto comp = player->getComponent<PlayerMagnetUpgrade>();
            if (comp) comp->upgrade();
            else player->addComponent(std::make_shared<PlayerMagnetUpgrade>(player));
            break;
        }
    }
    // Switch back to gameplay scene
    GameManager::getInstance().setScene(gamePlayScene);
}

void LevelUpScene::update(float deltaTime) {
    for (auto& button : buttons) button->update(deltaTime);
}

void LevelUpScene::render(sf::RenderWindow& window) {
    // Vẽ lại gameplay scene phía sau
    if (gamePlayScene) gamePlayScene->render(window);

    // Vẽ lớp phủ bán trong suốt lên toàn bộ cửa sổ để làm mờ nền khi lên level
    sf::RectangleShape overlay(sf::Vector2f(window.getSize()));
    overlay.setFillColor(sf::Color(0, 0, 0, 128));
    window.draw(overlay);

    // Tính lại vị trí và kích thước cho khung tổng
    float buttonHeight = 100.f;
    float buttonWidth = 300.f;
    float spacing = 40.f;
    float totalWidth = buttons.size() * buttonWidth + (buttons.size() - 1) * spacing;
    float windowWidth = window.getSize().x;
    float buttonY = 400.f;
    float buttonX = (windowWidth - totalWidth) / 2.f;


    // Vẽ từng khung cho mỗi nút
    for (size_t i = 0; i < buttons.size(); ++i) {
        float x = buttonX + i * (buttonWidth + spacing);
        float y = buttonY;

        sf::RectangleShape buttonFrame(sf::Vector2f(buttonWidth, buttonHeight));
        buttonFrame.setFillColor(sf::Color(50, 50, 50, 220));
        buttonFrame.setOutlineColor(sf::Color::White);
        buttonFrame.setOutlineThickness(3.f);
        buttonFrame.setPosition(x, y);
        window.draw(buttonFrame);

        // Vẽ nút lên trên khung
        buttons[i]->render(window);
    }
}
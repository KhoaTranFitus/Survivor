#pragma once
#include "Scene.h"
#include <vector>
#include <string>
#include <functional>

struct SkillNode {
    std::string name;
    std::string description;
    int currentLevel;
    int maxLevel;
    std::function<void()> onUpgrade;
};

class LevelUpScene : public Scene {
    std::vector<SkillNode> skills;
    int selected = 0;
    std::shared_ptr<Scene> previousScene;
public:
    LevelUpScene();
    LevelUpScene(std::shared_ptr<Scene> prev);
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
    void handleInput();
};


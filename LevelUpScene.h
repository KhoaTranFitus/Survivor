#pragma once
#include "Scene.h"
#include "Button.h"
#include <vector>
#include <memory>

class GamePlayScene; // Forward declaration

class LevelUpScene : public Scene {
	std::shared_ptr<GameObject> player;
	std::shared_ptr<GamePlayScene> gamePlayScene;
	std::vector<std::shared_ptr<Button>> skillButtons;
	std::vector<int> selectedSkills; // Indices of 3 random skills
public:
	LevelUpScene(std::shared_ptr<GameObject> player, std::shared_ptr<GamePlayScene> gamePlayScene);
	void onSkillSelected(int skillIndex);
	void render(sf::RenderWindow& window) override;
	void update(float deltaTime) override;
};
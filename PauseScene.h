#pragma once
#include "Scene.h"
#include <memory>
#include <chrono>

class GamePlayScene; // Forward declaration

class PauseScene : public Scene
{
public:
    // Nhận shared_ptr<GamePlayScene> để resume
    PauseScene(std::shared_ptr<GamePlayScene> gameplayScene);
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;

private:
    std::shared_ptr<GamePlayScene> gamePlayScene;
    bool wasPaused_ = false; // Để đảm bảo chỉ pause 1 lần
};
#include "PauseScene.h"
#include "Button.h"
#include "SwitchSceneCommand.h"
#include "GamePlayScene.h"
#include "MenuScene.h"
#include "SelectLevelScene.h"
#include <SFML/Graphics.hpp>
#include <sstream>

// Constructor: lưu lại gameplayScene để resume
PauseScene::PauseScene(std::shared_ptr<GamePlayScene> gameplayScene)
    : gamePlayScene(gameplayScene)
{
    // Pause clock ngay khi vào scene pause
    if (gamePlayScene && !wasPaused_) {
        gamePlayScene->pauseClock();
        wasPaused_ = true;
    }

     //Resume button: resume lại gameplayScene cũ
    auto resumeButton = std::make_shared<Button>(
        "Resume", "type1", 535, 300, sf::Vector2f(210, 50),
        std::make_shared<SwitchSceneCommand>([scene = gamePlayScene]() {
            scene->resumeClock();
            return scene;
            })
    );
    buttons.push_back(resumeButton);

    auto menuButton = std::make_shared<Button>(
        "Menu", "type1", 535, 400, sf::Vector2f(210, 50),
        std::make_shared<SwitchSceneCommand>([](){
            return std::make_shared<SelectLevelScene>();
            })
    );
    buttons.push_back(menuButton);
}

void PauseScene::update(float deltaTime) {
    for (auto& button : buttons) button->update(deltaTime);
}

void PauseScene::render(sf::RenderWindow& window) {
    // Vẽ lại gameplay scene phía sau
    if (gamePlayScene) gamePlayScene->render(window);

    // Vẽ lớp phủ bán trong suốt lên toàn bộ cửa sổ để làm mờ nền khi pause
    sf::RectangleShape overlay(sf::Vector2f(window.getSize()));
    overlay.setFillColor(sf::Color(0, 0, 0, 128)); // 128: bán trong suốt
    window.draw(overlay);

    // Hiển thị thời gian tạm dừng với định dạng MM:SS
    if (gamePlayScene) {
        gamePlayScene->renderClock(window, { 555, 180 }, sf::Color::White,28);
    }

    // Sau đó vẽ các đối tượng giao diện (nút Resume, Menu) lên trên lớp phủ
    for (auto& button : buttons) button->render(window);
}

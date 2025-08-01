#include "SettingScene.h"
#include <algorithm>  // để dùng std::clamp
#include "Config.h"
#include "SwitchSceneCommand.h"
#include "MenuScene.h"
#include "MusicManager.h"

SettingScene::SettingScene() : Scene()
{
	//this->name = "SettingScene";
	gameObjects.push_back(GameObjectFactory::createBackground("./Assets/backGround/selectLevel.png"));
	// Thanh bar
	volumeBar.setSize(sf::Vector2f(300.f, 10.f));
	volumeBar.setPosition(490.f, 300.f);
	volumeBar.setFillColor(sf::Color::Black);

	// Nút tròn
	volumeDot.setRadius(10.f);
	volumeDot.setFillColor(sf::Color::Red);
	volumeDot.setOrigin(10.f, 10.f); // Đặt tâm
	volumeDot.setPosition(volumeBar.getPosition().x + volumeBar.getSize().x * (volume / 100.f), volumeBar.getPosition().y + 5.f);

	auto backButton = std::make_shared<Button>(
		"Back", "type2", 70, 650, sf::Vector2f(145, 50),
		std::make_shared<SwitchSceneCommand>([]() {
			return std::make_shared<MenuScene>();
			})
	);
	buttons.push_back(backButton);
}


SettingScene::~SettingScene()
{
}

void SettingScene::update(float deltaTime)
{
	Scene::update(deltaTime); // Để cập nhật các nút nếu có

	sf::Vector2f mousePos = mousePosition;
	sf::FloatRect dotBounds = volumeDot.getGlobalBounds();

	// Kiểm tra chuột nhấn lên nút
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (dotBounds.contains(mousePos) || isDragging)
		{
			isDragging = true;
			// Giới hạn kéo trong thanh bar
			float newX = std::clamp(mousePos.x, volumeBar.getPosition().x, volumeBar.getPosition().x + volumeBar.getSize().x);
			volumeDot.setPosition(newX, volumeDot.getPosition().y);

			// Tính lại volume
			float percent = (newX - volumeBar.getPosition().x) / volumeBar.getSize().x;
			volume = percent * 100.f;

			 // Điều chỉnh âm lượng nhạc nền
			MusicManager::getInstance().setVolume(volume);
		}
	}
	else
	{
		isDragging = false;
	}
}


void SettingScene::render(sf::RenderWindow& window)
{
	Scene::render(window); // Vẽ các nút khác nếu có

	window.draw(volumeBar);
	window.draw(volumeDot);
}

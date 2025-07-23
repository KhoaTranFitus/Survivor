#include "SettingScene.h"
#include <algorithm>  // để dùng std::clamp
#include "Config.h"

SettingScene::SettingScene() : Scene()
{
	//this->name = "SettingScene";

	// Thanh bar
	volumeBar.setSize(sf::Vector2f(300.f, 10.f));
	volumeBar.setPosition(300.f, 300.f);
	volumeBar.setFillColor(sf::Color::Black);

	// Nút tròn
	volumeDot.setRadius(10.f);
	volumeDot.setFillColor(sf::Color::Red);
	volumeDot.setOrigin(10.f, 10.f); // Đặt tâm
	volumeDot.setPosition(volumeBar.getPosition().x + volumeBar.getSize().x * (volume / 100.f), volumeBar.getPosition().y + 5.f);
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

			// Gọi điều chỉnh âm lượng ở đây nếu bạn dùng sf::Music hoặc Sound
			// sound.setVolume(volume);
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

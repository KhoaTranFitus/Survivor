#include "SettingScene.h"
#include <algorithm>  // để dùng std::clamp
#include "Config.h"
#include "SwitchSceneCommand.h"
#include "MenuScene.h"
#include "MusicManager.h"
#include "Assets.h"


SettingScene::SettingScene() : Scene()
{
	//this->name = "SettingScene";
	gameObjects.push_back(GameObjectFactory::createBackground("./Assets/backGround/background.png"));
	// Thanh bar
	volumeBar.setSize(sf::Vector2f(300.f, 10.f));
	volumeBar.setPosition(490.f, 420.f);
	volumeBar.setFillColor(sf::Color::Black);

	// Nút tròn
	volumeDot.setRadius(10.f);
	volumeDot.setFillColor(sf::Color::Blue);
	volumeDot.setOrigin(10.f, 10.f); // Đặt tâm
	volumeDot.setPosition(volumeBar.getPosition().x + volumeBar.getSize().x
		* (volume / 100.f), volumeBar.getPosition().y + 5.f);

	sfxBar.setSize(sf::Vector2f(300.f, 10.f));
	sfxBar.setPosition(490.f, 570.f);
	sfxBar.setFillColor(sf::Color::Black);

	// Nút tròn SFX
	sfxDot.setRadius(10.f);
	sfxDot.setFillColor(sf::Color::Blue);
	sfxDot.setOrigin(10.f, 10.f);
	sfxDot.setPosition(sfxBar.getPosition().x + sfxBar.getSize().x
		* (sfxVolume / 100.f), sfxBar.getPosition().y + 5.f);

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
	sf::FloatRect sfxDotBounds = sfxDot.getGlobalBounds();

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
		else if (sfxDotBounds.contains(mousePos) || isDraggingSFX)
		{
			isDraggingSFX = true;
			float newX = std::clamp(mousePos.x, sfxBar.getPosition().x, sfxBar.getPosition().x + sfxBar.getSize().x);
			sfxDot.setPosition(newX, sfxDot.getPosition().y);

			float percent = (newX - sfxBar.getPosition().x) / sfxBar.getSize().x;
			sfxVolume = percent * 100.f;

		}
	}
	else
	{
		isDragging = false;
		isDraggingSFX = false;
	}
}


void SettingScene::render(sf::RenderWindow& window)
{
	Scene::render(window); // Vẽ các nút khác nếu có

	window.draw(volumeBar);
	window.draw(volumeDot);

	window.draw(sfxBar);
	window.draw(sfxDot);


	sf::Font font;
	font.loadFromFile("PixelOperator8-Bold.ttf");
	sf::Text title("Setting", font, 40);
	title.setFillColor(sf::Color(107, 85, 74));
	title.setStyle(sf::Text::Italic);
	title.setPosition(520.f, 125.f); // Điều chỉnh vị trí cho phù hợp
	window.draw(title);

	// Thêm label cho thanh nhạc nền
	sf::Text musicLabel("Music", font, 22);
	musicLabel.setFillColor(sf::Color(107, 85, 74));
	musicLabel.setPosition(volumeBar.getPosition().x, volumeBar.getPosition().y - 45.f);
	window.draw(musicLabel);

	// Thêm label cho thanh sound effect
	sf::Text sfxLabel("Sound", font, 22);
	sfxLabel.setFillColor(sf::Color(107, 85, 74));
	sfxLabel.setPosition(sfxBar.getPosition().x , sfxBar.getPosition().y - 45.f);
	window.draw(sfxLabel);
}

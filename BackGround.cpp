#include "BackGround.h"

Background::Background(const std::string& imagePath)
{
    if (!texture.loadFromFile("./Assets/backGround/Game1.jpg")) {
        std::cerr << "Failed to load background image\n";
    }
    else {
        sprite.setTexture(texture);
    }

    sprite.setScale(2.f, 2.f);
    sprite.setPosition(0, 0);
}


//void Background::render(sf::RenderWindow& window)
//{
//    window.draw(sprite);
//}
void Background::render(sf::RenderWindow& window)
{
    // Lấy thông tin view hiện tại
    sf::View view = window.getView();
    sf::FloatRect viewRect(
        view.getCenter().x - view.getSize().x / 2.f,
        view.getCenter().y - view.getSize().y / 2.f,
        view.getSize().x,
        view.getSize().y
    );
	// tính kích thước của background dựa trên texture và scale của sprite
    sf::Vector2f bgSize(
        texture.getSize().x * sprite.getScale().x,
        texture.getSize().y * sprite.getScale().y
    );

    // Tìm vị trí bắt đầu vẽ (bên trái trên cùng của view, căn theo background)
    int startX = static_cast<int>(std::floor(viewRect.left / bgSize.x));
    int startY = static_cast<int>(std::floor(viewRect.top / bgSize.y));
    int endX = static_cast<int>(std::ceil((viewRect.left + viewRect.width) / bgSize.x));
    int endY = static_cast<int>(std::ceil((viewRect.top + viewRect.height) / bgSize.y));

    sf::Sprite tiledSprite = sprite; // copy sprite gốc

    for (int x = startX; x < endX; ++x) {
        for (int y = startY; y < endY; ++y) {
            tiledSprite.setPosition(x * bgSize.x, y * bgSize.y);
            window.draw(tiledSprite);
        }
    }
}


sf::Sprite& Background::getSprite()
{
	return sprite;
}
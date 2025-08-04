#pragma once

#include <SFML/Graphics.hpp>
#include "Config.h"
#include "GameObject.h"
#include "KeyboardMove.h"

class Player : public GameObject
{
public:
	Player();
	virtual ~Player();
	bool isControllable() const; // Thêm hàm kiểm tra có thể điều khiển không
};

#pragma once
#include "Enemies.h"

class Boss : public Enemies {
public:
    Boss();
    ~Boss() override = default;

    void update(float deltaTime) override;
};
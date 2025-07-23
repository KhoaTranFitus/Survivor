// SwitchSceneCommand.cpp
#include "SwitchSceneCommand.h"
#include "GameManager.h"
#include <iostream>

SwitchSceneCommand::SwitchSceneCommand
(std::function<std::shared_ptr<Scene>()> func)
    : createScene(std::move(func)) {
}

void SwitchSceneCommand::execute() {
    GameManager::getInstance().setScene(createScene());
}
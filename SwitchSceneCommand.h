// SwitchSceneCommand.h
#pragma once

#include "ICommand.h"
#include "Scene.h"
#include <memory>
#include <functional>

class SwitchSceneCommand : public ICommand {
private:
    std::function<std::shared_ptr<Scene>()> createScene;

public:
    SwitchSceneCommand(std::function<std::shared_ptr<Scene>()> func);
    void execute() override;
};
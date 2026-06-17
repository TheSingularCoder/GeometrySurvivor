#pragma once
#include "Component.h"
#include "Vector2D.h"
#include <vector>

class TransformComponent;
class ControllerComponent : public Component<ControllerComponent> {

  private:
    Vector2D dir; // vector betweeen the character and the mouse cursor

    std::vector<SDL_Event> &keyPressedVec;

    TransformComponent *tc = nullptr;

  public:
    ControllerComponent(std::vector<SDL_Event> &keyPressedVec);
    void init() override;
    void update(float dt) override;
};

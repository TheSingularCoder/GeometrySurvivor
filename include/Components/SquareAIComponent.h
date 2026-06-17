#pragma once
#include "Components/SimpleAIComponent.h"
#include "Timer.h"

class SquareAIComponent : public SimpleAIComponent {

  private:
    enum class State { Chasing, Stop, Dashing };

    State state = State::Chasing;
    Timer dashCooldown;
    Timer dashDuration;
    Timer stopDuration; // timer before the dash

  public:
    SquareAIComponent(infoAI &info, float dashDuration = 0.35f, float stopDuration = 0.2f, float dashCooldown = 2.0f);

    void update(float dt) override;
};

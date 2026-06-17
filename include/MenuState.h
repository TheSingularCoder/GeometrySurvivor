#pragma once
#include "SDL_wrapper.h"
#include "State.h"

class MenuState : public State {

  private:
  public:
    MenuState(std::function<void(StateID)> chaState, GameData &gData);
    ~MenuState();
    void handleEvent(const SDL::Event &e) override;
    void update(float dt) override;
    void render(SDL::RendererPtr r) override;
};

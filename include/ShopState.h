#pragma once

#include "State.h"
#include <cstddef>
#include <string_view>
#include <vector>

// possibles upgrades
constexpr std::string_view s = "hola";

class ShopState : public State {
  private:
    bool waitingInput = false;

    std::vector<size_t> spellsSelected{0, 0, 0, 0};
    size_t statSelected = 0;

  public:
    ShopState(std::function<void(StateID)> chaState, GameData &gData);
    void handleEvent(const SDL::Event &e) override;
    void update(float dt) override;
    void render(SDL::RendererPtr r) override;
};

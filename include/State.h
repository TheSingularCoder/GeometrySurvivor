#pragma once

#include "GameData.h"
#include "SDL_wrapper.h"
#include <functional>

// State identificator
enum class StateID {
    None,  // ID that represents a null State
    Close, // ID that represents exiting the game
    Playing,
    Menu,
    Shop
};
// Interface for the State

class State {

  protected:
    std::function<void(StateID id)> changeState;
    GameData &gameData;

  public:
    State(std::function<void(StateID)> chaState, GameData &gData) : changeState(chaState), gameData(gData) {}; // custom constructor for all the States
    virtual ~State() = default;
    virtual void handleEvent(const SDL::Event &e) = 0;
    virtual void update(float dt) = 0;
    virtual void render(SDL::RendererPtr r) = 0;
};

#pragma once

#include "ColliderManager.h"
#include "EntityManager.h"
#include "Factory.h"
#include "State.h"
#include "Timer.h"
#include "infoAI.h"

class PlayingState : public State {

  private:
    EntityManager eManager;
    ColliderManager cManager;
    Factory fact;

    std::vector<SDL_Event> keyPressedVec;
    infoAI aiContext;
    Entity *player = nullptr; // reference to the player

    Timer waveTimer = {15.0f};
    Timer shopTimer = {30.0f};

  public:
    PlayingState(std::function<void(StateID)> chaState, GameData &gdata);
    ~PlayingState();
    void handleEvent(const SDL::Event &e) override;
    void update(float dt) override;
    void render(SDL::RendererPtr r) override;
    void startWave();

    infoAI getAIContext() const { return aiContext; }
    void setAsPlayer(Entity &player) { this->player = &player; } // Selecting an entity to be a player+
    void setPlayerNull() { player = nullptr; }
    Entity *getPlayer() const { return player; }
};

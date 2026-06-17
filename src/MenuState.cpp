#include "MenuState.h"
#include "GameData.h"
#include "SDL_scancode.h"
#include "State.h"
#include <cstdio>

MenuState::MenuState(std::function<void(StateID)> chaState, GameData &gData) : State(chaState, gData) {
    printf("\033[2J\033[1;1H");
    printf("\n");
    printf("=========================================\n");
    printf("         GEOMETRY SURVIVOR            \n");
    printf("=========================================\n");
    printf("\n");
    printf("Welcome, traveler. What would you like to do?\n");
    printf("\n");
    printf("  1. Start Game\n");
    printf("  2. Options\n");
    printf("  3. Quit Game\n");
    printf("  4.Shop\n");
    printf("\n");
}

MenuState::~MenuState() = default;

void MenuState::handleEvent(const SDL::Event &e) {
    if (e.type == SDL_QUIT) {

        if (changeState)
            changeState(StateID::Close);
    }
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.scancode) {
        case SDL_SCANCODE_1:
            changeState(StateID::Playing);
            break;
        case SDL_SCANCODE_2:
            changeState(StateID::Close);
            break;
        case SDL_SCANCODE_3:
            changeState(StateID::Close);
            break;
        case SDL_SCANCODE_4:
            changeState(StateID::Shop);
            break;
        default:
            break;
        }
    }
}
void MenuState::update(float dt) {}

void MenuState::render(SDL::RendererPtr r) {}

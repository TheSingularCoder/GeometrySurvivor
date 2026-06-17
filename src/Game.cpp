#include "Game.h"
#include "MenuState.h"
#include "PlayingState.h"
#include "ShopState.h"
#include "State.h"
#include <ctime>
#include <memory>

Game::Game() : window(SDL::CreateWindow()), renderer(SDL::CreateRenderer(window)) {}

Game::~Game() = default;

void Game::init() {

    srand(time(0)); // initialize the random seed

    running = true;

    state = (std::make_unique<MenuState>([this](StateID id) { nextState = id; }, gameData));

    Uint64 lastTime = SDL_GetPerformanceCounter();

    float accumulator = 0.0f;
    constexpr float FIXED_DT = 1.0f / (60.0f);

    while (running) {

        // polling events
        SDL::Event e;

        while (SDL_PollEvent(&e)) {
            state->handleEvent(e);
        }

        // getting delta Time
        Uint64 now = SDL_GetPerformanceCounter();

        float dt = (float)(now - lastTime) / (float)SDL_GetPerformanceFrequency();
        lastTime = now;
        if (dt > 0.05f)
            dt = 0.05f; // delta Time clamp for lagspikes

        accumulator += dt;
        while (accumulator >= FIXED_DT) {
            state->update(FIXED_DT);
            accumulator -= FIXED_DT;
        }

        // fps , may remove later
        float fps = 1.0f / dt;
        SDL_SetWindowTitle(window.get(), ("GeometrySurvivor | FPS: " + std::to_string(static_cast<int>(fps))).c_str());

        updateState();
        SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255); // RGBA
        SDL::RenderClear(renderer.get());
        state->render(renderer.get());
        SDL::RenderPresent(renderer.get());
    }
}

void Game::updateState() {

    if (nextState != StateID::None) {

        auto stateCallback = [this](StateID id) { nextState = id; }; // callback

        switch (nextState) {
        case StateID::Close:

            running = false;
            break;
        case StateID::Playing:
            // if we are playing we destoy the menu state
            state = (std::make_unique<PlayingState>(stateCallback, gameData));
            break;
        case StateID::Menu:
            state = (std::make_unique<MenuState>(stateCallback, gameData));
        case StateID::Shop:
            state = (std::make_unique<ShopState>(stateCallback, gameData));
        default:
            break;
        }

        nextState = StateID::None; // no queued State
    }
}

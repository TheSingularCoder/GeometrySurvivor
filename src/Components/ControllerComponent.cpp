#include "Components/ControllerComponent.h"
#include "Components/SpellComponent.h"
#include "Components/TransformComponent.h"
#include "Entity.h"

ControllerComponent::ControllerComponent(std::vector<SDL_Event> &keyPressedVec) : keyPressedVec(keyPressedVec) {}
void ControllerComponent::init() {
    tc = this->entity->getComponent<TransformComponent>();
}
void ControllerComponent::update(float dt) {

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    float logicalX = mouseX * (static_cast<float>(WIDTH) / WIN_WIDTH);
    float logicalY = mouseY * (static_cast<float>(HEIGHT) / WIN_HEIGHT);

    Vector2D mousePos = {logicalX, logicalY};
    Vector2D playerPos = tc->getPos();
    Vector2D vectorPlayerMouse = (mousePos - playerPos);
    float speed = tc->getSpeed();
    float dist = vectorPlayerMouse.getMagnitude();

    if (dist <= 5.0f) { // if the distance is so small the component just stop(stops the jittering)
        tc->setVel(Vector2D{0, 0});
    } else {
        dir = vectorPlayerMouse * (1 / dist);
        tc->setVel(dir * speed);
    }

    for (auto const &e : keyPressedVec) {
        switch (e.key.keysym.scancode) {
        case SDL_SCANCODE_Z:

            if (auto *spell = this->entity->getComponent<SpellComponent>()) { // we create a variable so we dont check twice
                spell->castSpell(Spell::Primary, dir);
            }

            break;
        case SDL_SCANCODE_X:

            if (auto *spell = this->entity->getComponent<SpellComponent>()) { // we create a variable so we dont check twice
                spell->castSpell(Spell::Secondary, dir);
            }

            break;

        case SDL_SCANCODE_C:
            if (auto *spell = this->entity->getComponent<SpellComponent>()) { // we create a variable so we dont check twice
                spell->castSpell(Spell::Special, playerPos);
            }
            break;
        case SDL_SCANCODE_V:
            if (auto *spell = this->entity->getComponent<SpellComponent>()) { // we create a variable so we dont check twice
                spell->castSpell(Spell::Special2, playerPos);
            }
            break;

        default:
            break;
        }
    }

    keyPressedVec.clear(); // we clean the
}

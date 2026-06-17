#include "Components/SummonerAIComponent.h"
#include "Components/SimpleAIComponent.h"
#include "Components/SpellComponent.h"
#include "Components/TransformComponent.h"

SummonerAIComponent::SummonerAIComponent(infoAI &info) : SimpleAIComponent(info) {}

void SummonerAIComponent::update(float dt) {

    if (!info->isPlayerAlive) {
        tc->setVel(Vector2D{0, 0});
        return;
    }

    Vector2D targetPos = info->playerPos;
    Vector2D thisPos = tc->getPos();
    Vector2D vectorEntityPlayer = (targetPos - thisPos);
    float speed = tc->getSpeed();
    float dist = vectorEntityPlayer.getMagnitude(); // it cant be Sq

    if (dist <= 50.0f) { // if the distance is near enough it tries to run away
        dir = vectorEntityPlayer * (1 / dist);
        tc->setVel(-dir * speed * 0.9); // is harder to get away from the player
    } else if (dist >= 40.0f) {
        dir = vectorEntityPlayer * (1 / dist);
        tc->setVel(dir * speed);

    } else {
        tc->setVel(Vector2D{0, 0});
    }
    if (20.0f < dist && dist < 150.0f) {
        this->entity->getComponent<SpellComponent>()->castSpell(Spell::Primary, thisPos);
    }
}

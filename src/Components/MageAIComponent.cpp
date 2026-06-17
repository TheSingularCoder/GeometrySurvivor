#include "Components/MageAIComponent.h"
#include "Components/SpellComponent.h"
#include "Entity.h"
#include "RandomUtils.h"
#include "Vector2D.h"

MageAIComponent::MageAIComponent(infoAI &info) : SimpleAIComponent(info) {}

void MageAIComponent::update(float dt) {

    if (!info->isPlayerAlive) {
        tc->setVel(Vector2D{0, 0});
        return;
    }

    Vector2D targetPos = info->playerPos;
    Vector2D thisPos = tc->getPos();
    Vector2D vectorEntityPlayer = (targetPos - thisPos);
    float speed = tc->getSpeed();
    float dist = vectorEntityPlayer.getMagnitude(); // it cant be Sq

    Vector2D offset = Vector2D{randomFloat(-20, 20), randomFloat(-20, 20)};

    if (dist <= 100.0f) { // if the distance is near enough it tries to run away
        dir = vectorEntityPlayer * (1 / dist);
        tc->setVel(-dir * speed * 0.4); // is harder to get away from the player
    } else if (dist >= 220.0f) {
        dir = vectorEntityPlayer * (1 / dist);
        tc->setVel(dir * speed);

    } else {
        tc->setVel(Vector2D{0, 0});
    }
    if (20.0f < dist && dist < 200.0f) {
        this->entity->getComponent<SpellComponent>()->castSpell(Spell::Primary, targetPos + offset);
    }
}

#include "Components/Colliders.h"
#include "Components/HealthComponent.h"
#include "Entity.h"
#include <cstdio>

//==============SPELL COLLIDER====================
SpellCollider::SpellCollider(float radius, CollisionLayer::Type layer, CollisionLayer::Type mask, std::function<void(Entity *e)> spellBehaviour, float tick)
    : ColliderComponent(radius, layer, mask), spellBehaviour(spellBehaviour), tick(tick) {
    this->tick.setReady();
}

void SpellCollider::onCollision(Entity *e) {

    if (tick.isReady()) {

        if (spellBehaviour) {
            spellBehaviour(e);
        }
    }
}

void SpellCollider::update(float dt) {
    if (tick.isReady()) {
        tick.reset();
    } else {
        tick.update(dt);
    }
}

//======BULLET COLLIDER=============
BulletCollider::BulletCollider(float radius, CollisionLayer::Type layer, CollisionLayer::Type mask, std::function<void(Entity *e)> bulletBehaviour)
    : ColliderComponent(radius, layer, mask), bulletBehaviour(bulletBehaviour) {}
void BulletCollider::onCollision(Entity *e) {

    if (bulletBehaviour) {
        bulletBehaviour(e);
    }
    this->entity->destroy();
}

//================ENEMY COLLIDER====================
EnemyCollider::EnemyCollider(float radius, CollisionLayer::Type layer, CollisionLayer::Type mask) : ColliderComponent(radius, layer, mask) {}
void EnemyCollider::onCollision(Entity *e) {
    if (e->getComponent<HealthComponent>())
        e->getComponent<HealthComponent>()->getHit(10);
}
//===========PLAYER COLLIDER==========
PlayerCollider::PlayerCollider(float radius, CollisionLayer::Type layer, CollisionLayer::Type mask) : ColliderComponent(radius, layer, mask) {}
void PlayerCollider::onCollision(Entity *e) {}

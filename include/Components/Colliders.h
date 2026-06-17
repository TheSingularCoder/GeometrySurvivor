#pragma once
#include "Components/ColliderComponent.h"
#include "Timer.h"
#include <functional>

class SpellCollider : public ColliderComponent {
  private:
    std::function<void(Entity *e)> spellBehaviour;
    Timer tick;
    bool canHit = true;

  public:
    SpellCollider(float radius, CollisionLayer::Type layer, CollisionLayer::Type mask, std::function<void(Entity *e)> spellBehaviour, float tick = 0.25f);
    void onCollision(Entity *e) override;
    void update(float dt) override;
};

class BulletCollider : public ColliderComponent {
    int damage;
    std::function<void(Entity *e)> bulletBehaviour;

  public:
    BulletCollider(float radius, CollisionLayer::Type layer, CollisionLayer::Type mask, std::function<void(Entity *e)> bulletBehaviour);
    void onCollision(Entity *e) override;
};

class EnemyCollider : public ColliderComponent {

  public:
    EnemyCollider(float radius, CollisionLayer::Type layer, CollisionLayer::Type mask);
    void onCollision(Entity *e) override;
};

class PlayerCollider : public ColliderComponent {

  public:
    PlayerCollider(float radius, CollisionLayer::Type layer, CollisionLayer::Type mask);
    void onCollision(Entity *e);
};

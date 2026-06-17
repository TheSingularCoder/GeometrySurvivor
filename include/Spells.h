#pragma once

#include "Components/TransformComponent.h"
#include "Entity.h"
#include "Timer.h"

class ISpell {

  protected:
    Timer cooldown; // we have to reset each time we call
    int damage = 0;

  public:
    ISpell(float cooldown, int damage) : cooldown(cooldown), damage(damage) {}
    virtual ~ISpell() = default;
    virtual void cast(Entity &e, Vector2D dir) = 0;
    virtual void update(Entity &e, float dt) { cooldown.update(dt); };
    virtual void render(Entity &e, SDL::RendererPtr r) {}
    void upgrade(float newCooldown, int newDamage) {
        damage = newDamage;
        cooldown = Timer{newCooldown};
        cooldown.reset();
    }
};

class BulletSpell : public ISpell {

  private:
    std::function<void(Vector2D initPos, Vector2D dir, int damage)> castBullet;

  public:
    BulletSpell(float rechargeTime, int damage, std::function<void(Vector2D initPos, Vector2D dir, int damage)> func)
        : ISpell(rechargeTime, damage), castBullet(func) {}
    void cast(Entity &e, Vector2D dir) override {
        if (cooldown.isReady()) {
            if (castBullet)
                castBullet(e.getComponent<TransformComponent>()->getPos(), dir, damage);
            cooldown.reset();
        }
    }
};

class DashSpell : public ISpell {

  private:
    Timer dashTimer{.2f}; // how much time does the dash lasts
    bool dashing = false;
    float prevSpeed = 0.0f;

  public:
    DashSpell(float rechargeTime) : ISpell(rechargeTime, 0.0f) {}
    void cast(Entity &e, Vector2D dir) override {
        if (cooldown.isReady()) {
            auto *tc = e.getComponent<TransformComponent>();
            prevSpeed = tc->getSpeed();
            tc->setSpeed(prevSpeed * 3.0f);
            dashing = true;
            cooldown.reset();
            dashTimer.reset();
        }
    }
    void update(Entity &e, float dt) override {
        if (dashing) {
            dashTimer.update(dt);
        } else {
            cooldown.update(dt);
        }

        if (dashTimer.isReady()) {

            dashTimer.reset();
            auto *tc = e.getComponent<TransformComponent>();
            Vector2D dir = tc->getVel().getNormalized();
            tc->setSpeed(prevSpeed);
            dashing = false;
        }
    }
};

class CallbackSpell : public ISpell { // spell for which we only call a lambda

  private:
    std::function<void(Vector2D pos, int damage)> callback;

  public:
    CallbackSpell(float rechargeTime, int damage, std::function<void(Vector2D pos, int damage)> c) : ISpell(rechargeTime, damage), callback(c) {}
    void cast(Entity &e, Vector2D dir) override {
        if (cooldown.isReady()) {

            if (callback) {
                callback(dir, damage);
            }
            cooldown.reset();
        }
    }
};

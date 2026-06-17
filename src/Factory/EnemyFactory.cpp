#include "CollisionLayers.h"
#include "Components/ComponentsList.h"
#include "Components/MageAIComponent.h"
#include "Components/SummonerAIComponent.h"
#include "EntityManager.h"
#include "Factory.h"
#include "RandomUtils.h"

Vector2D randomSpawnPos(float screenW, float screenH, float margin = 50.0f) {
    switch (randomInt(0, 3)) {
    case 0:
        return {randomFloat(0, screenW), -margin};
    case 1:
        return {randomFloat(0, screenW), screenH + margin};
    case 2:
        return {-margin, randomFloat(0, screenH)};
    case 3:
        return {screenW + margin, randomFloat(0, screenH)};
    }
    return Vector2D{0, 0};
}

void Factory::makeRandomEnemy() {

    auto &e = addEntity(3);
    e.addComponent<TransformComponent>(randomSpawnPos(WIDTH, HEIGHT), randomFloat(30, 60));
    int rad = randomInt(5, 10); // radius of the enemy
    auto color = SDL::Color{static_cast<Uint8>(randomInt(0, 255)), static_cast<Uint8>(randomInt(0, 255)), static_cast<Uint8>(randomInt(0, 255)), 255};
    e.addComponent<SimpleSpriteComponent>(rad, randomInt(3, 10), color);
    e.addComponent<EnemyCollider>(rad, CollisionLayer::Enemy, CollisionLayer::Player);
    e.addComponent<HealthComponent>(rad * 10, 0.0f); // no inviTime for the enemies
    e.addComponent<SimpleAIComponent>(AIcontext);
    e.init();
}

void Factory::makeTriangule() {
    auto &e = addEntity(3);
    e.addComponent<TransformComponent>(randomSpawnPos(WIDTH, HEIGHT), randomFloat(50, 70));
    int rad = randomInt(5, 9); // radius of the enemy
    auto color = SDL::Color{static_cast<Uint8>(randomInt(0, 255)), static_cast<Uint8>(randomInt(0, 255)), static_cast<Uint8>(randomInt(0, 255)), 255};
    e.addComponent<SimpleSpriteComponent>(rad, 3, color);
    e.addComponent<EnemyCollider>(rad, CollisionLayer::Enemy, CollisionLayer::Player);
    e.addComponent<HealthComponent>(rad * 5.0f, 0.0f); // no inviTime for the enemies
    e.addComponent<SimpleAIComponent>(AIcontext);
    e.init();
}

void Factory::makeSquare() {
    auto &e = addEntity(3);
    e.addComponent<TransformComponent>(randomSpawnPos(WIDTH, HEIGHT), randomFloat(60, 80));
    int rad = randomInt(5, 10); // radius of the enemy
    auto color = SDL::Color{static_cast<Uint8>(randomInt(0, 255)), static_cast<Uint8>(randomInt(0, 255)), static_cast<Uint8>(randomInt(0, 255)), 255};
    e.addComponent<SimpleSpriteComponent>(rad, 4, color);
    e.addComponent<EnemyCollider>(rad, CollisionLayer::Enemy, CollisionLayer::Player);
    e.addComponent<HealthComponent>(rad * 7.5f, 0.0f); // no inviTime for the enemies
    e.addComponent<SquareAIComponent>(AIcontext);
    e.init();
}
void Factory::makePentagon() {

    auto &e = addEntity(3);
    e.addComponent<TransformComponent>(randomSpawnPos(WIDTH, HEIGHT), randomFloat(30, 60));
    int rad = randomInt(5, 10); // radius of the enemy
    auto color = SDL::Color{static_cast<Uint8>(randomInt(0, 255)), static_cast<Uint8>(randomInt(0, 255)), static_cast<Uint8>(randomInt(0, 255)), 255};
    e.addComponent<SimpleSpriteComponent>(rad, 5, color);
    e.addComponent<EnemyCollider>(rad, CollisionLayer::Enemy, CollisionLayer::Player);
    e.addComponent<HealthComponent>(rad * 10, 0.0f); // no inviTime for the enemies
    e.addComponent<ArcherAIComponent>(AIcontext);
    e.addComponent<SpellComponent>().addSpell(Spell::Primary, std::make_unique<BulletSpell>(0.35f, 1, [this](Vector2D initpos, Vector2D dir, int damage) {
                                                  this->makeBullet(initpos, dir, damage, CollisionLayer::Player);
                                              }));
    e.init();
}

void Factory::makeMiniBomber(Vector2D pos) {

    auto &e = addEntity(3);
    e.addComponent<TransformComponent>(pos, 80.0f);
    int rad = 4; // radius of the enemy
    auto color = SDL::Colors::SunFlower;
    e.addComponent<SimpleSpriteComponent>(rad, 3, color);
    e.addComponent<EnemyCollider>(rad, CollisionLayer::Enemy, CollisionLayer::None); // it has no collision damage
    e.addComponent<HealthComponent>(10.0f, 0.0f);                                    // no inviTime for the enemies
    e.addComponent<SimpleAIComponent>(AIcontext);
    e.addComponent<LifeTimeComponent>(2.5f, [this](Vector2D pos) { this->makeExplosion(pos, 6, 10, CollisionLayer::Player); });
    e.init();
}

void Factory::makeHexagon() {

    auto &e = addEntity(3);
    e.addComponent<TransformComponent>(randomSpawnPos(WIDTH, HEIGHT), randomFloat(30, 60));
    int rad = randomInt(7, 12); // radius of the enemy
    auto color = SDL::Color{static_cast<Uint8>(randomInt(0, 255)), static_cast<Uint8>(randomInt(0, 255)), static_cast<Uint8>(randomInt(0, 255)), 255};
    e.addComponent<SimpleSpriteComponent>(rad, 6, color);
    e.addComponent<EnemyCollider>(rad, CollisionLayer::Enemy, CollisionLayer::Player);
    e.addComponent<HealthComponent>(rad * 7, 0.0f); // no inviTime for the enemies
    e.addComponent<SummonerAIComponent>(AIcontext);
    e.addComponent<SpellComponent>().addSpell(
        Spell::Primary, std::make_unique<CallbackSpell>(3.0f, 1, [this](Vector2D initpos, int damage) { this->makeMiniBomber(initpos); }));
    e.init();
}

void Factory::makeHeptagon() {

    auto &e = addEntity(3);
    e.addComponent<TransformComponent>(randomSpawnPos(WIDTH, HEIGHT), randomFloat(30, 60));
    float rad = static_cast<float>(randomInt(7, 12)); // radius of the enemy
    auto color = SDL::Color{static_cast<Uint8>(randomInt(0, 255)), static_cast<Uint8>(randomInt(0, 255)), static_cast<Uint8>(randomInt(0, 255)), 255};
    e.addComponent<SimpleSpriteComponent>(rad, 7, color);
    e.addComponent<EnemyCollider>(rad, CollisionLayer::Enemy, CollisionLayer::Player);
    e.addComponent<HealthComponent>(rad * 3, 0.0f); // no inviTime for the enemies
    e.addComponent<MageAIComponent>(AIcontext);
    e.addComponent<SpellComponent>().addSpell(
        Spell::Primary, std::make_unique<CallbackSpell>(3.0f, 1, [this](Vector2D pos, int damage) { this->makeInferno(pos, damage, CollisionLayer::Player); }));
    e.init();
}

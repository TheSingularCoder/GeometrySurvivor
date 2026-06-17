#include "Factory.h"
#include "Components/ComponentsList.h"
#include "Components/SpellComponent.h"
#include "EntityManager.h"
#include "GameData.h"
#include "SpellStats.h"
#include "Spells.h"
#include <functional>
void equipSpellToSlot(Entity &e, GameData &gameData, Factory *factory, Spell::SpellSlot slot) {
    auto *spellComp = e.getComponent<SpellComponent>();

    int spellID = gameData.spellReg.getEquippedSpell(slot);

    if (spellID == -1)
        return;

    int level = gameData.spellReg.getSpellLevel(spellID);
    const auto &baseStats = SpellPresets::allSpells[spellID];

    int finalDamage = baseStats.damage + (baseStats.damageUpgrade * level);
    float finalCooldown = std::max(0.05f, baseStats.rechargeTime - (baseStats.rechargeTimeUpgrade * level));

    switch (spellID) {
    case 0:
        spellComp->addSpell(slot, std::make_unique<BulletSpell>(finalCooldown, finalDamage, [factory](Vector2D pos, Vector2D dir, int dmg) {
                                factory->makeBullet(pos, dir, dmg, CollisionLayer::Enemy);
                            }));
        break;

    case 1:
        spellComp->addSpell(slot, std::make_unique<DashSpell>(finalCooldown));
        break;

    case 2:
        spellComp->addSpell(slot, std::make_unique<CallbackSpell>(finalCooldown, finalDamage,
                                                                  [factory](Vector2D pos, int dmg) { factory->makeBlast(pos, dmg, CollisionLayer::Enemy); }));
        break;

    case 3:
        spellComp->addSpell(slot, std::make_unique<CallbackSpell>(finalCooldown, finalDamage,
                                                                  [factory](Vector2D pos, int dmg) { factory->makeIceAura(pos, CollisionLayer::Enemy); }));
        break;

    case 4:
        spellComp->addSpell(
            slot, std::make_unique<CallbackSpell>(finalCooldown, 0, [factory](Vector2D pos, int dmg) { factory->makeFireAura(pos, CollisionLayer::Enemy); }));
        break;

    case 5:
        spellComp->addSpell(slot, std::make_unique<CallbackSpell>(finalCooldown, 0,
                                                                  [factory](Vector2D pos, int dmg) { factory->makeThunderAura(pos, CollisionLayer::Enemy); }));
        break;

    case 6:
        spellComp->addSpell(slot, std::make_unique<BulletSpell>(finalCooldown, finalDamage, [factory](Vector2D pos, Vector2D dir, int dmg) {
                                factory->makePiercingBullet(pos, dir, dmg, CollisionLayer::Enemy);
                            }));
        break;

    case 7:
        spellComp->addSpell(slot, std::make_unique<BulletSpell>(finalCooldown, finalDamage, [factory](Vector2D pos, Vector2D dir, int dmg) {
                                factory->makeBullet(pos, dir, dmg, CollisionLayer::Enemy);
                                factory->makeBullet(pos, Vector2D{dir.x * 0.8f, dir.y * 1.2f}, dmg, CollisionLayer::Enemy);
                                factory->makeBullet(pos, Vector2D{dir.x * 1.1f, dir.y * 1.3f}, dmg, CollisionLayer::Enemy);
                                factory->makeBullet(pos, Vector2D{dir.x * 1.3f, dir.y * 0.90f}, dmg, CollisionLayer::Enemy);
                                factory->makeBullet(pos, Vector2D{dir.x * 1.4f, dir.y * 1.1f}, dmg, CollisionLayer::Enemy);
                                factory->makeBullet(pos, Vector2D{dir.x * 1.2f, dir.y * 0.7f}, dmg, CollisionLayer::Enemy);
                                factory->makeBullet(pos, Vector2D{dir.x * 1.2f, dir.y * 1.4f}, dmg, CollisionLayer::Enemy);
                            }));
        break;

    case 8:
        spellComp->addSpell(
            slot, std::make_unique<BulletSpell>(finalCooldown, finalDamage, [factory](Vector2D pos, Vector2D dir, int dmg) {
                factory->makeBullet(pos, dir, dmg, CollisionLayer::Enemy);
                factory->makeBullet(pos, Vector2D{dir.x * 0.939f - dir.y * 0.349f, dir.x * 0.349f + dir.y * 0.939f}, dmg, CollisionLayer::Enemy);
                factory->makeBullet(pos, Vector2D{dir.x * 0.939f - dir.y * -0.349f, dir.x * -0.349f + dir.y * 0.939f}, dmg, CollisionLayer::Enemy);
            }));
        break;

    default:
        break;
    }
}

Factory::Factory(EntityManager &em, infoAI &ctx, GameData &gData) : eManager(&em), AIcontext(ctx), gameData(gData) {}
Factory::~Factory() = default;

Entity &Factory::addEntity(int depth) {
    auto e2 = std::make_unique<Entity>(depth);
    auto &e = *e2;
    eManager->addBufferEntity(std::move(e2));
    return e;
}

void Factory::makePlayer(std::function<void(Entity &e)> funcCreate, std::function<void()> funcDestroy, std::vector<SDL::Event> &keyPressedVec) {
    // ESTO ES UNA PUTA MIERDA; HACER UN REGISTER DE SPELLS QUE TENGA TODA LA INFO
    // Y SOLO PROEGUNTAS Y QUE EL BLACKBOAR TENGA UNA REFERENCIA SUYA Y PUNTO
    //  1. Da
    auto &e = addEntity(2);
    e.addComponent<TransformComponent>(Vector2D{400, 20}, 100.0f);
    e.addComponent<SimpleSpriteComponent>(8, 5, SDL::Colors::Player);
    e.addComponent<ControllerComponent>(keyPressedVec);
    e.addComponent<PlayerCollider>(8.0f, CollisionLayer::Player, CollisionLayer::None);
    e.addComponent<HealthComponent>(100);
    e.addComponent<PlayerComponent>(funcCreate, funcDestroy);

    e.addComponent<SpellComponent>().addSpell(Spell::Primary, std::make_unique<BulletSpell>(0.35f, 10, [this](Vector2D initpos, Vector2D dir, int damage) {
                                                  this->makeBullet(initpos, dir, 10, CollisionLayer::Enemy);
                                              }));
    equipSpellToSlot(e, gameData, this, Spell::Primary);
    equipSpellToSlot(e, gameData, this, Spell::Secondary);
    equipSpellToSlot(e, gameData, this, Spell::Special);
    equipSpellToSlot(e, gameData, this, Spell::Special2);
    e.init();
}

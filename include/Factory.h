#pragma once
#include "CollisionLayers.h"
#include "Entity.h"
#include "GameData.h"
#include "Spells.h"
#include "infoAI.h"
#include <functional>
#include <memory>
#include <unordered_map>
class EntityManager;

class Factory {

  private:
    EntityManager *eManager;
    infoAI &AIcontext;
    GameData &gameData;
    Entity &addEntity(int depth);

    std::unordered_map<std::string_view,
                       std::function<std::unique_ptr<ISpell>()>>
        spellDict; // diccionary that holds all the spells lambdas and shares the key with the blackboard

  public:
    Factory(EntityManager &em, infoAI &ctx, GameData &gData);
    ~Factory();

    void makePlayer(std::function<void(Entity &e)> funcCreate, std::function<void()> funcDestroy, std::vector<SDL::Event> &keyPressedVec);

    //========SPELLS=======
    void makeBullet(Vector2D pos, Vector2D dir, int damage, CollisionLayer::Type mask = CollisionLayer::Enemy);
    void makePiercingBullet(Vector2D pos, Vector2D dir, int damage, CollisionLayer::Type mask = CollisionLayer::Enemy);
    void makeBlast(Vector2D pos, int damage, CollisionLayer::Type mask = CollisionLayer::Enemy);
    void makeExplosion(Vector2D, float rad, int damage, CollisionLayer::Type mask = CollisionLayer::Enemy); // has no lingering efeects like blast
    void makeIceAura(Vector2D pos, CollisionLayer::Type mask = CollisionLayer::Enemy);
    void makeFireAura(Vector2D pos, CollisionLayer::Type mask = CollisionLayer::Enemy);
    void makeThunderAura(Vector2D pos, CollisionLayer::Type mask = CollisionLayer::Enemy);
    void makeInferno(Vector2D pos, int damage, CollisionLayer::Type mask = CollisionLayer::Enemy);

    //==========ENEMIES============
    void makeRandomEnemy(); //
    void makeMiniBomber(Vector2D pos);

    void makeTriangule(); // zombie enemy
    void makeSquare();    // dasher enemy
    void makePentagon();  // lasser enemy
    void makeHexagon();   // summoner enemy
    void makeHeptagon();  // area wizard enemy

    void update();
};

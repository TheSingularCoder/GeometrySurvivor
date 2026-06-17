#pragma once
#include "SDL_wrapper.h"
#include <array>
#include <bitset>
#include <future>
#include <vector>

constexpr size_t MAX_COMPONENTS = 32;
enum class Faction { None, Enemy, Player, Bullet, Spell }; // faction of each entity

class BaseComponent; // forward declaration of out interface of component

class Entity {

  private:
    inline static size_t nextID = 0;

    size_t ID = 0;

    bool active = true;

    std::vector<std::unique_ptr<BaseComponent>> componentVec; // vector that hold the life cycle of our components

    std::array<BaseComponent *, MAX_COMPONENTS> componentContainer; // array that holds the raw pointers of the components and works as an observer

    std::bitset<MAX_COMPONENTS> componentBitset; // bitset that represent if an entity has an especific component

    int depth = 0; // order in witch we are going to render the entity

  public:
    Entity() : ID(nextID++) {};
    Entity(int depthE) : ID(nextID++), depth(depthE) { // printf("%d\n",nextID);
    }

    ~Entity() = default;
    template <typename T, typename... Args> T &addComponent(Args &&...args);

    template <typename T> void deleteComponent();

    template <typename T> bool hasComponent() const;

    template <typename T> T *getComponent() const;

    void setDepth(int newD) { depth = newD; }
    int getDepth() const { return depth; }

    size_t getID() const { return ID; }

    bool isActive() const { return active; }
    void destroy() { active = false; }

    void init();
    void update(float dt);
    void render(SDL::RendererPtr r);
};

#include "Components/Component.h"

inline void Entity::init() {
    for (auto &c : componentVec) {
        c->init();
    }
}

inline void Entity::update(float dt) {
    for (auto &c : componentVec) { // we iterate the vector because does not have any nullptr like de array and has adjacent-memory
        c->update(dt);
    }
}

inline void Entity::render(SDL::RendererPtr r) {
    for (const auto &c : componentVec) {
        c->render(r);
    }
}

template <typename T, typename... Args> T &Entity::addComponent(Args &&...args) {

    auto component = std::make_unique<T>(std::forward<Args>(args)...);
    component->entity = this;
    componentBitset[component->getStaticID()] = true;
    componentContainer[component->getStaticID()] = component.get();

    T *componentPtr = component.get();

    componentVec.push_back(std::move(component));

    componentPtr->init();

    return *componentPtr;
}

template <typename T> void Entity::deleteComponent() {
    auto componentID = T::getStaticID();
    componentBitset[componentID] = false;
    componentContainer[componentID] = nullptr;

    for (size_t i = 0; i < componentVec.size(); ++i) {
        if (componentVec[i]->getID() == componentID) {

            componentVec[i] = std::move(componentVec.back());
            componentVec.pop_back();
            break;
        }
    }
}

template <typename T> bool Entity::hasComponent() const {
    return componentBitset[T::getStaticID()];
}

template <typename T> T *Entity::getComponent() const {
    if (!componentBitset[T::getStaticID()])
        return nullptr;                                            // we make sure its created
    return static_cast<T *>(componentContainer[T::getStaticID()]); // we use static_cast because we can be certain that the pointer we get is that specific type
}

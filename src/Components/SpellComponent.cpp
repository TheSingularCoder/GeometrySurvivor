#include "Components/SpellComponent.h"
#include "SpellStats.h"

SpellComponent::SpellComponent() {}

void SpellComponent::addSpell(Spell::SpellSlot slot, std::unique_ptr<ISpell> ptr) {
    spells[slot] = std::move(ptr);
}

void SpellComponent::castSpell(Spell::SpellSlot slot, Vector2D pos) {
    if (auto &spell = spells[slot])
        spell->cast(*this->entity, pos);
}

void SpellComponent::update(float dt) {

    for (auto const &s : spells) {
        if (!s)
            continue;
        s->update(*this->entity, dt);
    }
}

void SpellComponent::render(SDL::RendererPtr r) {

    for (auto const &s : spells) {
        if (!s)
            continue;
        s->render(*this->entity, r);
    }
}

void SpellComponent::upgradeSpell(Spell::SpellSlot slot, SpellStats stats) {}

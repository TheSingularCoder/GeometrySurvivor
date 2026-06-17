#pragma once
#include "Components/Component.h"
#include "SpellStats.h"
#include "Spells.h"
#include <array>
#include <memory>

namespace Spell {
enum SpellSlot {

    Primary,
    Secondary,
    Special,
    Special2
};
}

constexpr size_t MAX__SPELLS = 4;
class SpellComponent : public Component<SpellComponent> {

  private:
    std::array<std::unique_ptr<ISpell>, MAX__SPELLS> spells;

  public:
    SpellComponent();

    void addSpell(Spell::SpellSlot slot, std::unique_ptr<ISpell> ptr); // the making of the spells is made in the factory
    void castSpell(Spell::SpellSlot slot, Vector2D pos);
    void upgradeSpell(Spell::SpellSlot, SpellStats stats);

    void update(float dt) override;
    void render(SDL::RendererPtr r) override;
};

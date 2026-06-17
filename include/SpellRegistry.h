#pragma once
#include "Components/SpellComponent.h"
#include "SpellStats.h"
#include <array>
class SpellRegistry {
  private:
    std::array<int, SpellPresets::SpellNum> spellLevels; // keeps the level of all the spells

    // this array is keeping the id of each spell, -1 means no spells
    std::array<int, 4> equippedSpells;

  public:
    SpellRegistry() {
        spellLevels.fill(0);
        equippedSpells.fill(-1);
        // primary bullet level 1
        spellLevels[0] = 1;
        equippedSpells[Spell::Primary] = 0;
    }

    void levelUpSpell(int spellID) { spellLevels[spellID]++; }
    int getSpellLevel(int spellID) const { return spellLevels[spellID]; }

    void equipSpell(Spell::SpellSlot slot, int spellID) { equippedSpells[slot] = spellID; }
    int getEquippedSpell(Spell::SpellSlot slot) const { return equippedSpells[slot]; }
};

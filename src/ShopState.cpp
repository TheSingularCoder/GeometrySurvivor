#include "ShopState.h"
#include "RandomUtils.h"
#include "SDL_wrapper.h"
#include "SpellStats.h"

#include <cstdio>
#include <string>
#include <sys/stat.h>
#include <vector>
ShopState::ShopState(std::function<void(StateID)> chaState, GameData &gData) : State(chaState, gData) {}

void ShopState::update(float dt) {
    if (waitingInput)
        return;

    std::vector<int> possibleSpells = {};
    for (int i = 0; i < SpellPresets::allSpells.size(); i++) {
        possibleSpells.push_back(i); // we make a vector with the numbers from 1 to ...
    }

    for (int i = 0; i < 4; i++) {
        int randomIndex = randomInt(0, possibleSpells.size() - 1);
        spellsSelected[i] = possibleSpells[randomIndex];            // choosing a random index of the vector that represent every spell the player can get
        possibleSpells.erase(possibleSpells.begin() + randomIndex); // we destroy the index so it cant show up again
    }
    const auto &aS = SpellPresets::allSpells;

    statSelected = randomInt(0, StatsPresets::statNum - 1);

    // cleaning up the terminal

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    printf("\n=========================================\n");
    printf("               MAGIC SHOP                \n");
    printf("=========================================\n");
    printf("Choose a spell to upgrade your power!\n\n");

    for (int i = 0; i < 4; i++) {
        int spellIndex = spellsSelected[i];
        const auto &spell = aS[spellIndex];

        std::string safeName(spell.name); // string conversion so its type safe for the printf

        // Print the spell header (e.g., 1. Fire Aura)
        printf("%d. [%s]\n", i + 1, safeName.c_str());

        // Print its stats formatted in columns
        if (spell.level == 0) {
            printf("   Status:locked\n");
            printf("   Base Damage: %-4d \n", spell.damage);
            printf("   Base Cooldown:    %.2fs\n", spell.rechargeTime);
            printf("\n");

        } else {
            printf("   Status:Unlocked lvl:%-4d\n", spell.level);
            printf("   Damage: %-4d (Upgrade: +%d)\n", spell.damage + spell.damageUpgrade * spell.level, spell.damageUpgrade);
            printf("   Cooldown:    %.2fs (Upgrade: -%.2fs)\n", spell.rechargeTime - spell.rechargeTimeUpgrade * spell.level, spell.rechargeTimeUpgrade);

            printf("\n");
        }
    }
    const auto &s = StatsPresets::allStats[statSelected];
    std::string safeName(s.name);
    printf("%d. [%s]\n", 5, safeName.c_str());
    printf("    lvl:%-4d\n", s.level);
    printf("    Value:  %g(Upgrade:  +%g)\n", s.stat, s.statUpgrade);

    printf("-----------------------------------------\n");
    printf("Enter your choice (1-4) or 0 to exit: ");

    // we wait for the input
    waitingInput = true;
}

void ShopState::handleEvent(const SDL::Event &e) {

    if (e.type == SDL_QUIT) {
        if (changeState)
            changeState(StateID::Close);
        return;
    }

    if (e.type == SDL_KEYDOWN) {
        int selectedSpellID = -1;
        const auto &stat = StatsPresets::allStats[statSelected];

        switch (e.key.keysym.scancode) {
        case SDL_SCANCODE_1:
            selectedSpellID = spellsSelected[0];
            break;
        case SDL_SCANCODE_2:
            selectedSpellID = spellsSelected[1];
            break;
        case SDL_SCANCODE_3:
            selectedSpellID = spellsSelected[2];
            break;
        case SDL_SCANCODE_4:
            selectedSpellID = spellsSelected[3];
            break;
        case SDL_SCANCODE_5: {
            std::string statName{stat.name};
            int currentLevel = gameData.getInfo<int>(statName).value_or(stat.level);
            gameData.addInfo(statName, currentLevel + 1);
            this->changeState(StateID::Playing);
            return;
        }
        default:
            return;
        }

        if (selectedSpellID != -1) {
            gameData.spellReg.levelUpSpell(selectedSpellID);

            bool alreadyEquipped = false;
            int firstEmptySlot = -1;

            for (int i = 0; i < 4; i++) {
                auto currentSlot = static_cast<Spell::SpellSlot>(i);
                int equippedID = gameData.spellReg.getEquippedSpell(currentSlot);

                if (equippedID == selectedSpellID) {
                    alreadyEquipped = true;
                    break;
                }

                if (equippedID == -1 && firstEmptySlot == -1) {
                    firstEmptySlot = i;
                }
            }

            if (!alreadyEquipped) {
                if (firstEmptySlot != -1) {
                    gameData.spellReg.equipSpell(static_cast<Spell::SpellSlot>(firstEmptySlot), selectedSpellID);
                } else {
                    gameData.spellReg.equipSpell(Spell::Primary, selectedSpellID);
                }
            }
        }

        this->changeState(StateID::Playing);
    }
}

void ShopState::render(SDL::RendererPtr r) {}

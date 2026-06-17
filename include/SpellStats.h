#pragma once

#include <array>
#include <cstddef>
#include <string_view>

// List of presets of the spells

struct SpellStats {

    std::string_view name;
    int damage = 0;
    int damageUpgrade = 0; // damage that we add to the damage total each upgrade
    // maybe add duration
    float rechargeTime = 0;
    float rechargeTimeUpgrade = 0; // time that we substract from the rechargeTime with each upgrade
    int level = 1;
};

// template <typename T, typename = std::enable_if_t<std::is_same_v<T, int> || std::is_same_v<T, float>, void>> // SFINAE
struct BodyStats {
    std::string_view name;
    float stat = 0;
    float statUpgrade = 0;
    int level = 1;
};

namespace StatsPresets {
constexpr size_t statNum = 2;
inline constexpr BodyStats health = {"health", 100, 10, 1};
inline constexpr BodyStats speed = {"speed", 0, 5, 1};
inline constexpr std::array<BodyStats, statNum> allStats{health, speed};

}; // namespace StatsPresets

// Presets for the Player Spells Stats

// level zero means that is locked
//
// The string represent their key to their respective level so we can check in the gameData
namespace SpellPresets {
inline constexpr size_t SpellNum = 9;

inline constexpr SpellStats Primary = {"PrimaryBullet", 10, 2, 0.35f, 0.05f, 1};

inline constexpr SpellStats Dash = {"Dash", 0, 0, 2.0f, 0.2f, 0};

inline constexpr SpellStats Blast = {"Blast", 50, 15, 3.0f, 0.3f, 0};

inline constexpr SpellStats IceAura = {"IceAura", 15, 5, 4.0f, 0.4f, 0};

inline constexpr SpellStats FireAura = {"FireAura", 20, 7, 4.0f, 0.4f, 0};

inline constexpr SpellStats ThunderAura = {"ThunderAura", 25, 8, 5.0f, 0.5f, 0};

inline constexpr SpellStats PiercingBullet = {"PiercingBullet", 15, 5, 1.0f, 0.1f, 0};

inline constexpr SpellStats ShotgunBullet = {"ShotgunBullet", 12, 3, 1.5f, 0.15f, 0};

inline constexpr SpellStats SpreadBullet = {"SpreadBullet", 10, 3, 1.5f, 0.15f, 0};

inline constexpr std::array<SpellStats, SpellNum> allSpells = {Primary,     Dash,           Blast,         IceAura,     FireAura,
                                                               ThunderAura, PiercingBullet, ShotgunBullet, SpreadBullet};
}; // namespace SpellPresets

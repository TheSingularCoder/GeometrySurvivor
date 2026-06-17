#pragma once
#include "SpellRegistry.h"
#include "Vector2D.h"
#include <SpellStats.h>
#include <functional>
#include <optional>
#include <unordered_map>
#include <variant>

// balckboard patter for the state to share information without touching eachother

using blackBoardValue = std::variant<int, float, std::string, BodyStats, SpellStats, std::function<void(Vector2D pos)>>;
class GameData {
  private:
    std::unordered_map<std::string, blackBoardValue> blackboard;

  public:
    SpellRegistry spellReg;
    int wave = -1;

    GameData() {}
    ~GameData() = default;

    void addInfo(const std::string &key, blackBoardValue value) {
        blackboard[key] = value; // careful it might rewrite
    }
    template <typename T> std::optional<T> getInfo(const std::string &key) {
        auto it = blackboard.find(key);
        if (it != blackboard.end() && std::holds_alternative<T>(it->second)) { // holds_alternative ask the variant if they have that type
            return std::get<T>(it->second);
        } else {
            return std::nullopt;
        }
    }
};

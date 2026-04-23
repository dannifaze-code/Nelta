#include "cheat_manager.h"
#include <iostream>

CheatManager::CheatManager() {}

CheatManager::~CheatManager() {}

void CheatManager::addCheat(const std::string& name, const std::string& code) {
    CheatCode newCheat;
    newCheat.name = name;
    newCheat.code = code;
    newCheat.enabled = false; // Default to off
    
    cheats.push_back(newCheat);
    std::cout << "Added Cheat: " << name << "\n";
}

void CheatManager::toggleCheat(const std::string& name, bool enable) {
    for (auto& cheat : cheats) {
        if (cheat.name == name) {
            cheat.enabled = enable;
            std::cout << "Cheat '" << name << "' is now " << (enable ? "ON" : "OFF") << "\n";
            return;
        }
    }
    std::cout << "Cheat not found: " << name << "\n";
}

const std::vector<CheatCode>& CheatManager::getCheats() const {
    return cheats;
}

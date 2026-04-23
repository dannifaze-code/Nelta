#ifndef CHEAT_MANAGER_H
#define CHEAT_MANAGER_H

#include <string>
#include <vector>

struct CheatCode {
    std::string name;
    std::string code; // The raw hex code (e.g., "12345678 00000000")
    bool enabled;
};

class CheatManager {
public:
    CheatManager();
    ~CheatManager();

    // Add a cheat manually
    void addCheat(const std::string& name, const std::string& code);
    
    // Toggle a specific cheat on or off
    void toggleCheat(const std::string& name, bool enable);
    
    // Get all loaded cheats
    const std::vector<CheatCode>& getCheats() const;

private:
    std::vector<CheatCode> cheats;
};

#endif // CHEAT_MANAGER_H

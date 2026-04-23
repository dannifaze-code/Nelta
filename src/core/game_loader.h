#ifndef GAME_LOADER_H
#define GAME_LOADER_H

#include <string>
#include <vector>

class GameLoader {
public:
    GameLoader();
    ~GameLoader();

    bool loadROM(const std::string &filePath);
    bool validateROM();
    std::string getGameMetadata() const;

private:
    std::string romPath;
    std::vector<std::string> metadata;
};

#endif // GAME_LOADER_H

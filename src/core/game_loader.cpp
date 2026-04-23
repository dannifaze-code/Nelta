#include <iostream>

class GameLoader {
public:
    void loadGame(const std::string& gameName) {
        std::cout << "Loading game: " << gameName << std::endl;
    }
};

int main() {
    GameLoader gameLoader;
    gameLoader.loadGame("Example Game");
    return 0;
}
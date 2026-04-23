#ifndef CONTROLLER_MANAGER_H
#define CONTROLLER_MANAGER_H

#include <SDL2/SDL.h>
#include <cstdint>
#include <unordered_map>

class ControllerManager {
public:
    ControllerManager();
    ~ControllerManager();

    // Process an SDL event (returns true if the event was an input event we care about)
    bool processEvent(const SDL_Event& event);

    // Get the current bitmask of all pressed keys
    uint32_t getKeyMask() const;

private:
    uint32_t currentKeyMask;

    // Maps an SDL_Keycode to an NDS Button bit
    std::unordered_map<SDL_Keycode, uint32_t> keyMap;

    // Set up the default keyboard layout
    void setupDefaultKeyMap();
};

#endif // CONTROLLER_MANAGER_H

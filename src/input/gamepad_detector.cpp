#include "controller_manager.h"

// Standard NDS Key Mapping (melonDS hardware bit layout)
enum NDS_Keys {
    KEY_A      = (1 << 0),
    KEY_B      = (1 << 1),
    KEY_SELECT = (1 << 2),
    KEY_START  = (1 << 3),
    KEY_RIGHT  = (1 << 4),
    KEY_LEFT   = (1 << 5),
    KEY_UP     = (1 << 6),
    KEY_DOWN   = (1 << 7),
    KEY_R      = (1 << 8),
    KEY_L      = (1 << 9),
    KEY_X      = (1 << 10),
    KEY_Y      = (1 << 11)
};

ControllerManager::ControllerManager() : currentKeyMask(0) {
    setupDefaultKeyMap();
}

ControllerManager::~ControllerManager() {}

void ControllerManager::setupDefaultKeyMap() {
    // Default PC keyboard mapping to DS buttons
    keyMap[SDLK_x]      = KEY_A;
    keyMap[SDLK_z]      = KEY_B;
    keyMap[SDLK_s]      = KEY_X;
    keyMap[SDLK_a]      = KEY_Y;
    keyMap[SDLK_RSHIFT] = KEY_SELECT;
    keyMap[SDLK_RETURN] = KEY_START;
    keyMap[SDLK_RIGHT]  = KEY_RIGHT;
    keyMap[SDLK_LEFT]   = KEY_LEFT;
    keyMap[SDLK_UP]     = KEY_UP;
    keyMap[SDLK_DOWN]   = KEY_DOWN;
    keyMap[SDLK_q]      = KEY_L;
    keyMap[SDLK_w]      = KEY_R;
}

bool ControllerManager::processEvent(const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
        auto it = keyMap.find(event.key.keysym.sym);
        
        if (it != keyMap.end()) {
            if (event.type == SDL_KEYDOWN) {
                currentKeyMask |= it->second; // Set the bit (Key Pressed)
            } else if (event.type == SDL_KEYUP) {
                currentKeyMask &= ~(it->second); // Clear the bit (Key Released)
            }
            return true;
        }
    }
    return false;
}

uint32_t ControllerManager::getKeyMask() const {
    return currentKeyMask;
}

#ifndef EMULATOR_WRAPPER_H
#define EMULATOR_WRAPPER_H

#include <string>
#include <vector>
#include <cstdint>
#include "../audio/audio_engine.h"

// Forward declaration for melonDS core
namespace melonDS {
    class NDS; 
}

class EmulatorCore {
public:  
    EmulatorCore();
    ~EmulatorCore();

    bool loadROM(const std::string &romPath);
    void runFrame();
    
    // Expose the raw 256x384 pixel buffer for the GameViewport
    const uint32_t* getFramebuffer() const;
    
    void reset();
    bool isRunning() const;

private:  
    melonDS::NDS* melonDSInstance;
    bool running;

    AudioEngine audioEngine;
};

#endif // EMULATOR_WRAPPER_H
#ifndef EMULATOR_WRAPPER_H
#define EMULATOR_WRAPPER_H

#include <string>
#include <vector>
#include <cstdint>
#include "../audio/audio_engine.h"

namespace melonDS {
    class NDS; 
}

class EmulatorCore {
public:  
    EmulatorCore();
    ~EmulatorCore();

    bool loadROM(const std::string &romPath);
    void runFrame();
    const uint32_t* getFramebuffer() const;
    
    // Pass the input state from the ControllerManager to the Core
    void setInputMask(uint32_t keyMask);
    
    void reset();
    bool isRunning() const;

private:  
    melonDS::NDS* melonDSInstance;
    bool running;

    AudioEngine audioEngine;
};

#endif // EMULATOR_WRAPPER_H
#ifndef EMULATOR_WRAPPER_H
#define EMULATOR_WRAPPER_H

#include <string>
#include <vector>
#include <cstdint>
#include "../audio/audio_engine.h"

namespace melonDS {
    class NDS; 
}

class EmulatorCore {
public:  
    EmulatorCore();
    ~EmulatorCore();

    bool loadROM(const std::string &romPath);
    void runFrame();
    const uint32_t* getFramebuffer() const;
    void setInputMask(uint32_t keyMask);
    
    // --- New Save & State Management ---
    void saveSRAM();
    void loadSRAM();
    void saveState(int slot = 1);
    void loadState(int slot = 1);

    void reset();
    bool isRunning() const;

private:  
    melonDS::NDS* melonDSInstance;
    bool running;
    std::string currentROMPath; // Track current game for saves

    AudioEngine audioEngine;
};

#endif // EMULATOR_WRAPPER_H
#ifndef EMULATOR_WRAPPER_H
#define EMULATOR_WRAPPER_H

#include <string>
#include <vector>
#include <cstdint>
#include "../audio/audio_engine.h"
#include "../cheats/cheat_manager.h"

namespace melonDS {
    class NDS; 
}

class EmulatorCore {
public:  
    EmulatorCore();
    ~EmulatorCore();

    bool loadROM(const std::string &romPath);
    void runFrame();
    const uint32_t* getFramebuffer() const;
    void setInputMask(uint32_t keyMask);
    
    void saveSRAM();
    void loadSRAM();
    void saveState(int slot = 1);
    void loadState(int slot = 1);
    
    // Pass the active cheats to the melonDS Action Replay engine
    void applyCheats(const CheatManager& cheatManager);

    void reset();
    bool isRunning() const;

private:  
    melonDS::NDS* melonDSInstance;
    bool running;
    std::string currentROMPath; 

    AudioEngine audioEngine;
};

#endif // EMULATOR_WRAPPER_H

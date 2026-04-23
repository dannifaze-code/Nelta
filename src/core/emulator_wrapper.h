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

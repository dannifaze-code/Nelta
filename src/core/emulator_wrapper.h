#ifndef EMULATOR_WRAPPER_H
#define EMULATOR_WRAPPER_H

#include <string>
#include <vector>
#include "../audio/audio_engine.h" // <-- Include our new Audio Engine

// Forward declaration for melonDS core to avoid including full headers here
namespace melonDS {
    class NDS; 
}

class EmulatorCore {
public:  
    EmulatorCore();
    ~EmulatorCore();

    bool loadROM(const std::string &romPath);
    void runFrame();
    std::vector<unsigned char> getFramebuffer();
    void reset();
    bool isRunning() const;

private:  
    melonDS::NDS* melonDSInstance;  // Cast this properly instead of void*
    bool running;

    AudioEngine audioEngine;        // <-- Add the Audio Engine instance
};

#endif // EMULATOR_WRAPPER_H

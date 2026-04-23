#include "emulator_wrapper.h"
#include <iostream>

// Include melonDS headers (adjust paths based on your melonDS submodule location)
#include "NDS.h"
#include "SPU.h"
#include "GPU.h" 

EmulatorCore::EmulatorCore() : melonDSInstance(nullptr), running(false) {
    // melonDS instance initialization would go here...
    // melonDSInstance = new melonDS::NDS(...);
    
    // Initialize our AudioEngine 
    // (Ensure the sample rate matches what you passed to the melonDS::SPU constructor!
    // melonDS native is 32768, but PC frontends often configure the SPU to output 48000Hz)
    if (!audioEngine.init(48000, 2)) {
        std::cerr << "Warning: AudioEngine failed to initialize." << std::endl;
    }
}

EmulatorCore::~EmulatorCore() {
    // AudioEngine destructor cleans itself up automatically via SDL2
    if (melonDSInstance) {
        delete melonDSInstance;
    }
}

bool EmulatorCore::loadROM(const std::string &romPath) {
    if (!melonDSInstance) return false;

    // Placeholder for melonDS ROM loading logic
    // e.g., melonDSInstance->LoadROM(romPath.c_str());
    std::cout << "Loading ROM: " << romPath << std::endl;
    
    running = true; 
    return true;
}

void EmulatorCore::runFrame() {
    if (!running || !melonDSInstance) return;

    // 1. Run the emulator for exactly one frame
    // melonDSInstance->RunFrame(); 

    // 2. Extract Audio from the SPU
    int samplesAvailable = melonDSInstance->SPU.GetOutputSize(); 
    
    if (samplesAvailable > 0) {
        // Create a buffer to hold the stereo samples (size * 2 channels)
        std::vector<int16_t> audioBuffer(samplesAvailable * 2);

        // Tell the SPU to write its internal buffer into our vector
        melonDSInstance->SPU.ReadOutput(audioBuffer.data(), samplesAvailable);

        // 3. Push the audio to the SDL2 queue!
        audioEngine.queueAudio(audioBuffer);
    }
}

const uint32_t* EmulatorCore::getFramebuffer() const {
    if (!melonDSInstance || !running) return nullptr;

    // melonDS exposes the composited 256x384 frame here.
    // Note: The exact variable name depends on the melonDS version you are building against.
    // Replace 'Framebuffer' with the correct 2D array pointer from your melonDS instance.
    // return melonDSInstance->GPU.Framebuffer; 
    
    return nullptr; 
}

void EmulatorCore::reset() {
    if (melonDSInstance) {
        // melonDSInstance->Reset();
    }
}

bool EmulatorCore::isRunning() const {
    return running;
}

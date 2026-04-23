#include "emulator_wrapper.h"
#include <iostream>

// Include melonDS headers (adjust paths based on your melonDS submodule location)
#include "NDS.h"
#include "SPU.h"

EmulatorCore::EmulatorCore() : running(false) {
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

void EmulatorCore::runFrame() {
    if (!running || !melonDSInstance) return;

    // 1. Run the emulator for exactly one frame
    // melonDSInstance->RunFrame(); // (or whatever melonDS's tick function is called in your version)

    // 2. Extract Audio from the SPU
    // GetOutputSize() returns the number of sample frames (1 frame = 1 left + 1 right sample)
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

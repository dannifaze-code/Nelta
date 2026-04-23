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
#include "emulator_wrapper.h"
#include <iostream>

#include "NDS.h"
#include "SPU.h"
#include "GPU.h" 

EmulatorCore::EmulatorCore() : melonDSInstance(nullptr), running(false) {
    if (!audioEngine.init(48000, 2)) {
        std::cerr << "Warning: AudioEngine failed to initialize." << std::endl;
    }
}

EmulatorCore::~EmulatorCore() {
    if (melonDSInstance) {
        delete melonDSInstance;
    }
}

bool EmulatorCore::loadROM(const std::string &romPath) {
    if (!melonDSInstance) return false;
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
        std::vector<int16_t> audioBuffer(samplesAvailable * 2);
        melonDSInstance->SPU.ReadOutput(audioBuffer.data(), samplesAvailable);
        audioEngine.queueAudio(audioBuffer);
    }
}

const uint32_t* EmulatorCore::getFramebuffer() const {
    if (!melonDSInstance || !running) return nullptr;
    // return melonDSInstance->GPU.Framebuffer; 
    return nullptr; 
}

void EmulatorCore::setInputMask(uint32_t keyMask) {
    if (!melonDSInstance || !running) return;

    // The DS hardware is active-low (0 = pressed, 1 = unpressed).
    // We invert the mask from the ControllerManager so melonDS reads it correctly.
    // 0x0FFF masks out just the 12 standard buttons to prevent garbage data.
    
    // melonDSInstance->SetKeyMask(~keyMask & 0x0FFF);
}

void EmulatorCore::reset() {
    if (melonDSInstance) {
        // melonDSInstance->Reset();
    }
}

bool EmulatorCore::isRunning() const {
    return running;
}
#include "emulator_wrapper.h"
#include <iostream>

#include "NDS.h"
#include "SPU.h"
#include "GPU.h" 
#include "SaveManager.h" // For SRAM
#include "Savestate.h"   // For Quick Saves

EmulatorCore::EmulatorCore() : melonDSInstance(nullptr), running(false) {
    if (!audioEngine.init(48000, 2)) {
        std::cerr << "Warning: AudioEngine failed to initialize." << std::endl;
    }
}

EmulatorCore::~EmulatorCore() {
    // Always save SRAM before closing!
    if (running) {
        saveSRAM();
    }
    if (melonDSInstance) {
        delete melonDSInstance;
    }
}

bool EmulatorCore::loadROM(const std::string &romPath) {
    if (running) {
        saveSRAM(); // Save current game before loading a new one
    }

    currentROMPath = romPath;
    
    // Placeholder for melonDS instance creation and ROM loading
    // melonDSInstance = new melonDS::NDS();
    // melonDSInstance->LoadROM(romPath.c_str());

    std::cout << "Loading ROM: " << romPath << std::endl;
    running = true; 
    
    // Automatically load battery save if it exists
    loadSRAM();

    return true;
}

void EmulatorCore::runFrame() {
    if (!running || !melonDSInstance) return;

    // melonDSInstance->RunFrame(); 

    int samplesAvailable = melonDSInstance->SPU.GetOutputSize(); 
    if (samplesAvailable > 0) {
        std::vector<int16_t> audioBuffer(samplesAvailable * 2);
        melonDSInstance->SPU.ReadOutput(audioBuffer.data(), samplesAvailable);
        audioEngine.queueAudio(audioBuffer);
    }
}

const uint32_t* EmulatorCore::getFramebuffer() const {
    if (!melonDSInstance || !running) return nullptr;
    // return melonDSInstance->GPU.Framebuffer; 
    return nullptr; 
}

void EmulatorCore::setInputMask(uint32_t keyMask) {
    if (!melonDSInstance || !running) return;
    // melonDSInstance->SetKeyMask(~keyMask & 0x0FFF);
}

// --- Save & State Management ---

void EmulatorCore::saveSRAM() {
    if (!running || currentROMPath.empty()) return;
    std::string savePath = currentROMPath + ".sav";
    std::cout << "Saving SRAM to: " << savePath << "\n";
    // melonDS::SaveManager::Save(savePath.c_str());
}

void EmulatorCore::loadSRAM() {
    if (!running || currentROMPath.empty()) return;
    std::string savePath = currentROMPath + ".sav";
    std::cout << "Attempting to load SRAM from: " << savePath << "\n";
    // melonDS::SaveManager::Load(savePath.c_str());
}

void EmulatorCore::saveState(int slot) {
    if (!running || currentROMPath.empty()) return;
    std::string statePath = currentROMPath + ".ml" + std::to_string(slot);
    std::cout << "Saving State to slot " << slot << "...\n";
    // melonDS::Savestate::Save(statePath.c_str());
}

void EmulatorCore::loadState(int slot) {
    if (!running || currentROMPath.empty()) return;
    std::string statePath = currentROMPath + ".ml" + std::to_string(slot);
    std::cout << "Loading State from slot " << slot << "...\n";
    // melonDS::Savestate::Load(statePath.c_str());
}

void EmulatorCore::reset() {
    if (melonDSInstance) {
        // melonDSInstance->Reset();
    }
}

bool EmulatorCore::isRunning() const {
    return running;
}

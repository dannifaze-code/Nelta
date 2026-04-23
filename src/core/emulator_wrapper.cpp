#include "emulator_wrapper.h"
#include <iostream>

#include "NDS.h"
#include "SPU.h"
#include "GPU.h" 
#include "SaveManager.h" 
#include "Savestate.h"   
#include "AREngine.h" // melonDS Action Replay Engine

EmulatorCore::EmulatorCore() : melonDSInstance(nullptr), running(false) {
    if (!audioEngine.init(48000, 2)) {
        std::cerr << "Warning: AudioEngine failed to initialize." << std::endl;
    }
}

EmulatorCore::~EmulatorCore() {
    if (running) saveSRAM();
    if (melonDSInstance) delete melonDSInstance;
}

bool EmulatorCore::loadROM(const std::string &romPath) {
    if (running) saveSRAM();
    currentROMPath = romPath;
    
    // melonDSInstance = new melonDS::NDS();
    // melonDSInstance->LoadROM(romPath.c_str());

    std::cout << "Loading ROM: " << romPath << std::endl;
    running = true; 
    loadSRAM();
    return true;
}

void EmulatorCore::applyCheats(const CheatManager& cheatManager) {
    if (!melonDSInstance || !running) return;

    // Here you hook into melonDS's AREngine
    // melonDS::AREngine::ClearCodes();
    // for (const auto& cheat : cheatManager.getCheats()) {
    //     if (cheat.enabled) {
    //         melonDS::AREngine::AddCode(cheat.code.c_str());
    //     }
    // }
}

void EmulatorCore::runFrame() {
    if (!running || !melonDSInstance) return;

    // Apply cheats right before the frame runs
    // melonDS::AREngine::Run();
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

void EmulatorCore::saveSRAM() {
    if (!running || currentROMPath.empty()) return;
    std::string savePath = currentROMPath + ".sav";
    // melonDS::SaveManager::Save(savePath.c_str());
}

void EmulatorCore::loadSRAM() {
    if (!running || currentROMPath.empty()) return;
    std::string savePath = currentROMPath + ".sav";
    // melonDS::SaveManager::Load(savePath.c_str());
}

void EmulatorCore::saveState(int slot) {
    if (!running || currentROMPath.empty()) return;
    std::string statePath = currentROMPath + ".ml" + std::to_string(slot);
    // melonDS::Savestate::Save(statePath.c_str());
}

void EmulatorCore::loadState(int slot) {
    if (!running || currentROMPath.empty()) return;
    std::string statePath = currentROMPath + ".ml" + std::to_string(slot);
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

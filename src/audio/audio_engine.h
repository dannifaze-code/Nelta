#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H

#include <SDL2/SDL.h>
#include <vector>
#include <cstdint>

class AudioEngine {
public:
    AudioEngine();
    ~AudioEngine();

    // Initialize the SDL audio device (Default DS: 32768Hz, Stereo)
    bool init(int sampleRate = 32768, int channels = 2); 
    
    // Push raw audio samples from the emulator core into the SDL buffer
    void queueAudio(const std::vector<int16_t>& samples); 
    
    // Clear the audio buffer (useful for save states or pausing)
    void clearBuffer(); 
    
    void setVolume(float newVolume); // Set volume (0.0f to 1.0f)
    void pause();
    void resume();

private:
    SDL_AudioDeviceID audioDevice;
    float volume;
};

#endif // AUDIO_ENGINE_H

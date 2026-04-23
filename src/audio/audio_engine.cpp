#include <SDL2/SDL.h>
#include <iostream>

class AudioEngine {
public:
    AudioEngine() : audioDevice(0), audioSpec{} {
        // Initialize SDL audio
        if (SDL_Init(SDL_INIT_AUDIO) < 0) {
            std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << '\n';
        }
    }

    ~AudioEngine() {
        // Close audio device if it's open
        if (audioDevice != 0) {
            SDL_CloseAudioDevice(audioDevice);
        }
        SDL_Quit();
    }

    void loadSound(const char* path) {
        // Load sound file and handle accordingly
        // This function will contain the logic to load sound files.
    }

    void playSound() {
        // Play loaded sound
        // Logic to play sound will be here.
    }

private:
    SDL_AudioDeviceID audioDevice;
    SDL_AudioSpec audioSpec;
};

int main() {
    AudioEngine audio;
    // Load and play a sound
    audio.loadSound("path/to/sound.wav");
    audio.playSound();
    return 0;
}
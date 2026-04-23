#include "audio_engine.h"
#include <iostream>
#include <algorithm>

AudioEngine::AudioEngine() : audioDevice(0), volume(1.0f) {}

AudioEngine::~AudioEngine() {
    if (audioDevice != 0) {
        SDL_CloseAudioDevice(audioDevice);
    }
}

bool AudioEngine::init(int sampleRate, int channels) {
    if (SDL_WasInit(SDL_INIT_AUDIO) == 0) {
        if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0) {
            std::cerr << "SDL Audio could not initialize! Error: " << SDL_GetError() << '\n';
            return false;
        }
    }

    SDL_AudioSpec desiredSpec;
    SDL_zero(desiredSpec);
    desiredSpec.freq = sampleRate;
    desiredSpec.format = AUDIO_S16SYS; // 16-bit signed audio (standard for melonDS)
    desiredSpec.channels = channels;   // 2 for Stereo
    desiredSpec.samples = 1024;        // Buffer size (tweak if you get audio crackling/latency)

    SDL_AudioSpec obtainedSpec;
    
    // Open the default audio device
    audioDevice = SDL_OpenAudioDevice(nullptr, 0, &desiredSpec, &obtainedSpec, 0);
    
    if (audioDevice == 0) {
        std::cerr << "Failed to open audio device: " << SDL_GetError() << '\n';
        return false;
    }

    // Start playback
    resume();
    return true;
}

void AudioEngine::queueAudio(const std::vector<int16_t>& samples) {
    if (audioDevice == 0 || samples.empty()) return;

    // Optional: Apply volume scaling here if volume < 1.0f
    if (volume < 1.0f) {
        std::vector<int16_t> adjustedSamples = samples;
        for (auto& sample : adjustedSamples) {
            sample = static_cast<int16_t>(sample * volume);
        }
        SDL_QueueAudio(audioDevice, adjustedSamples.data(), adjustedSamples.size() * sizeof(int16_t));
    } else {
        // Fast path: no volume adjustment
        SDL_QueueAudio(audioDevice, samples.data(), samples.size() * sizeof(int16_t));
    }
}

void AudioEngine::clearBuffer() {
    if (audioDevice != 0) {
        SDL_ClearQueuedAudio(audioDevice);
    }
}

void AudioEngine::setVolume(float newVolume) {
    volume = std::max(0.0f, std::min(newVolume, 1.0f)); // Clamp between 0.0 and 1.0
}

void AudioEngine::pause() {
    if (audioDevice != 0) {
        SDL_PauseAudioDevice(audioDevice, 1);
    }
}

void AudioEngine::resume() {
    if (audioDevice != 0) {
        SDL_PauseAudioDevice(audioDevice, 0);
    }
}

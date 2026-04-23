#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H

// Audio Engine header file for the audio system

class AudioEngine {
public:
    AudioEngine();
    ~AudioEngine();

    void init();  // Initialize the audio engine
    void playSound(const std::string& soundFile); // Play a sound
    void stopSound(); // Stop currently playing sound
    void setVolume(float volume); // Set volume level

private:
    float volume;
    // Additional private members for audio management
};

#endif // AUDIO_ENGINE_H
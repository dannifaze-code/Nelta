#include "game_viewport.h"
#include <iostream>

GameViewport::GameViewport() : dsTexture(nullptr) {}

GameViewport::~GameViewport() {
    destroy();
}

bool GameViewport::init(SDL_Renderer* renderer) {
    if (!renderer) return false;

    // Create a streaming texture. 
    // SDL_PIXELFORMAT_ARGB8888 is standard for melonDS, but if the colors 
    // look swapped (e.g., blue instead of red), change this to SDL_PIXELFORMAT_ABGR8888
    dsTexture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888, 
        SDL_TEXTUREACCESS_STREAMING,
        DS_WIDTH,
        DS_HEIGHT
    );

    if (!dsTexture) {
        std::cerr << "Failed to create GameViewport texture: " << SDL_GetError() << '\n';
        return false;
    }

    return true;
}

void GameViewport::updatePixels(const uint32_t* pixels) {
    if (!dsTexture || !pixels) return;

    // Lock the texture, copy the pixels from the emulator, and unlock it.
    // The pitch is simply the width * size of one pixel (4 bytes)
    void* mPixels;
    int mPitch;

    if (SDL_LockTexture(dsTexture, nullptr, &mPixels, &mPitch) == 0) {
        memcpy(mPixels, pixels, DS_WIDTH * DS_HEIGHT * sizeof(uint32_t));
        SDL_UnlockTexture(dsTexture);
    }
}

void GameViewport::render(SDL_Renderer* renderer, const SDL_Rect* destRect) {
    if (!dsTexture || !renderer) return;

    // Render the DS screens to the window.
    // If destRect is nullptr, it will stretch to fill the entire window.
    SDL_RenderCopy(renderer, dsTexture, nullptr, destRect);
}

void GameViewport::destroy() {
    if (dsTexture) {
        SDL_DestroyTexture(dsTexture);
        dsTexture = nullptr;
    }
}

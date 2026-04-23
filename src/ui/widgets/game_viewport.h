#ifndef GAME_VIEWPORT_H
#define GAME_VIEWPORT_H

#include <SDL2/SDL.h>
#include <cstdint>

class GameViewport {
public:
    GameViewport();
    ~GameViewport();

    // Initialize the viewport with the main SDL Renderer
    bool init(SDL_Renderer* renderer);

    // Push the raw 256x384 pixel buffer from melonDS to the GPU
    // Standard DS color format is usually 32-bit ARGB/BGRA
    void updatePixels(const uint32_t* pixels);

    // Draw the texture to the screen
    // Optional: pass a destination rectangle to handle window scaling/aspect ratio
    void render(SDL_Renderer* renderer, const SDL_Rect* destRect = nullptr);

    // Clean up resources
    void destroy();

private:
    SDL_Texture* dsTexture;
    
    // DS Native Dimensions
    const int DS_WIDTH = 256;
    const int DS_HEIGHT = 384; // 192 (Top) + 192 (Bottom)
};

#endif // GAME_VIEWPORT_H

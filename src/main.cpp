#include <iostream>
#include <string>
#include <SDL2/SDL.h>

// Include our custom Nelta systems
#include "core/emulator_wrapper.h"
#include "input/controller_manager.h"
#include "ui/widgets/game_viewport.h"

int main(int argc, char* argv[]) {
    // 1. Initialize SDL2 (Video for Window/Graphics, Audio for Sound)
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "Failed to initialize SDL2: " << SDL_GetError() << '\n';
        return -1;
    }

    // 2. Create the Application Window
    // The DS native resolution is 256x384. We scale it up 2x for a better default PC view.
    const int WINDOW_WIDTH = 256 * 2;
    const int WINDOW_HEIGHT = 384 * 2;

    SDL_Window* window = SDL_CreateWindow(
        "Nelta - DS Emulator",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );

    if (!window) {
        std::cerr << "Failed to create SDL Window: " << SDL_GetError() << '\n';
        SDL_Quit();
        return -1;
    }

    // 3. Create the Hardware-Accelerated Renderer
    // SDL_RENDERER_PRESENTVSYNC is crucial here: it caps our loop to the monitor's refresh rate (~60Hz), 
    // which matches the Nintendo DS's native 59.82Hz screen refresh perfectly without writing custom timers.
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, 
        -1, 
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!renderer) {
        std::cerr << "Failed to create SDL Renderer: " << SDL_GetError() << '\n';
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // 4. Instantiate our Nelta Subsystems
    EmulatorCore emulatorCore;
    ControllerManager controllerManager;
    GameViewport gameViewport;

    // Initialize the Viewport with our renderer
    if (!gameViewport.init(renderer)) {
        std::cerr << "Failed to initialize GameViewport.\n";
    }

    // 5. Load a ROM (For testing, you can pass it as a command line argument or hardcode a path)
    std::string romPath = (argc > 1) ? argv[1] : "test_rom.nds";
    if (!emulatorCore.loadROM(romPath)) {
        std::cerr << "Failed to load ROM: " << romPath << "\n";
        // Not exiting here just yet so you can see the window open even without a ROM.
    }

    // 6. The Main Emulator Loop
    bool isRunning = true;
    SDL_Event event;

    while (isRunning) {
        // --- EVENT POLLING & INPUT ---
        while (SDL_PollEvent(&event)) {
            // Handle clicking the 'X' on the window
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
            
            // Pass keyboard events to the ControllerManager
            controllerManager.processEvent(event);
        }

        // --- EMULATOR TICK ---
        // Send the latest button states to the core
        emulatorCore.setInputMask(controllerManager.getKeyMask());

        // Run exactly one frame of emulation (generates audio and video internally)
        emulatorCore.runFrame();

        // --- GRAPHICS PIPELINE ---
        // Clear the screen (Black background)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Fetch the raw pixels from the emulator
        const uint32_t* currentFrame = emulatorCore.getFramebuffer();
        
        if (currentFrame) {
            // Push pixels to the GPU
            gameViewport.updatePixels(currentFrame);
            
            // Render the DS screens to the window
            // Passing nullptr for the destRect stretches it to fit the window cleanly
            gameViewport.render(renderer, nullptr);
        }

        // Display the frame on the screen (VSync will pause execution here to cap at ~60FPS)
        SDL_RenderPresent(renderer);
    }

    // 7. Cleanup & Shutdown
    gameViewport.destroy();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

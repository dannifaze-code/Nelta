#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <windows.h> 

#include "core/emulator_wrapper.h"
#include "input/controller_manager.h"
#include "ui/widgets/game_viewport.h"
#include "cheats/cheat_manager.h"

std::string openFileDialog() {
    char filename[MAX_PATH] = {0};
    OPENFILENAMEA ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = nullptr;
    ofn.lpstrFilter = "Nintendo DS ROMs (*.nds)\0*.nds\0All Files (*.*)\0*.*\0";
    ofn.lpstrFile = filename;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrTitle = "Select a Nintendo DS ROM";
    ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

    if (GetOpenFileNameA(&ofn)) {
        return std::string(filename);
    }
    return "";
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "Failed to initialize SDL2: " << SDL_GetError() << '\n';
        return -1;
    }

    const int WINDOW_WIDTH = 256 * 2;
    const int WINDOW_HEIGHT = 384 * 2;

    SDL_Window* window = SDL_CreateWindow(
        "Nelta - DS Emulator",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    EmulatorCore emulatorCore;
    ControllerManager controllerManager;
    GameViewport gameViewport;
    CheatManager cheatManager;

    gameViewport.init(renderer);

    // Load a test cheat
    cheatManager.addCheat("Infinite Health", "12345678 00000000");

    if (argc > 1) {
        emulatorCore.loadROM(argv[1]);
    }

    bool isRunning = true;
    SDL_Event event;

    // FPS Tracking Variables
    Uint32 fpsLastTime = SDL_GetTicks();
    int fpsFrames = 0;

    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
            
            if (event.type == SDL_KEYDOWN) {
                // Ctrl + O: Open ROM
                if (event.key.keysym.sym == SDLK_o && (SDL_GetModState() & KMOD_CTRL)) {
                    std::string newRom = openFileDialog();
                    if (!newRom.empty()) {
                        emulatorCore.loadROM(newRom);
                    }
                }
                // F1: Save State 
                else if (event.key.keysym.sym == SDLK_F1) {
                    emulatorCore.saveState(1);
                }
                // F3: Load State
                else if (event.key.keysym.sym == SDLK_F3) {
                    emulatorCore.loadState(1);
                }
                // C: Toggle Test Cheat
                else if (event.key.keysym.sym == SDLK_c) {
                    cheatManager.toggleCheat("Infinite Health", !cheatManager.getCheats()[0].enabled);
                }
            }
            
            controllerManager.processEvent(event);
        }

        // Apply state to core
        emulatorCore.setInputMask(controllerManager.getKeyMask());
        emulatorCore.applyCheats(cheatManager);
        
        // Execute Frame
        emulatorCore.runFrame();

        // Graphics Render
        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255); 
        SDL_RenderClear(renderer);

        const uint32_t* currentFrame = emulatorCore.getFramebuffer();
        if (currentFrame) {
            gameViewport.updatePixels(currentFrame);
            int currentWinW, currentWinH;
            SDL_GetWindowSize(window, &currentWinW, &currentWinH);
            gameViewport.render(renderer, currentWinW, currentWinH);
        }

        SDL_RenderPresent(renderer);

        // --- Performance Monitoring (FPS Counter) ---
        fpsFrames++;
        Uint32 currentTicks = SDL_GetTicks();
        if (currentTicks - fpsLastTime >= 1000) {
            std::string title = "Nelta - DS Emulator [" + std::to_string(fpsFrames) + " FPS]";
            SDL_SetWindowTitle(window, title.c_str());
            fpsFrames = 0;
            fpsLastTime = currentTicks;
        }
    }

    gameViewport.destroy();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

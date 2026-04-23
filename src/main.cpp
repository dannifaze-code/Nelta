SDL_Event event;
while (SDL_PollEvent(&event)) {
    // If the event was a keypress, the ControllerManager handles it
    controllerManager.processEvent(event);
}

// Send the current button states to the emulator before running the frame
emulatorCore.setInputMask(controllerManager.getKeyMask());

// Run the frame!
emulatorCore.runFrame();

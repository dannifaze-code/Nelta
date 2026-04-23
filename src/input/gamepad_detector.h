#pragma once

#include <iostream>
#include <vector>
#include <string>

class GamepadDetector {
public:
    GamepadDetector();  // Constructor to initialize the gamepad detector
    ~GamepadDetector(); // Destructor to clean up resources

    void detectGamepads(); // Method to detect connected gamepads
    void manageGamepads();  // Method to manage gamepad states

private:
    std::vector<std::string> connectedGamepads; // List of connected gamepads
    void handleBluetoothGamepads(); // Handle detection of Bluetooth gamepads
    void handleWiredGamepads(); // Handle detection of wired gamepads
};

#endif // GAMEPAD_DETECTOR_H

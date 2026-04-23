#include <iostream>

class GraphicsSettings {
public:
    void setResolution(int width, int height) {
        this->width = width;
        this->height = height;
    }

    void setFullscreen(bool fullscreen) {
        this->fullscreen = fullscreen;
    }

    void printSettings() {
        std::cout << "Resolution: " << width << 'x' << height << "\n";
        std::cout << "Fullscreen: " << (fullscreen ? "Yes" : "No") << "\n";
    }

private:
    int width = 1920;
    int height = 1080;
    bool fullscreen = false;
};

// Example usage
// int main() {
//     GraphicsSettings gs;
//     gs.setResolution(1280, 720);
//     gs.setFullscreen(true);
//     gs.printSettings();
//     return 0;
// }

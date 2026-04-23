#ifndef GRAPHICS_SETTINGS_H
#define GRAPHICS_SETTINGS_H

class GraphicsSettings {
public:
    GraphicsSettings();
    ~GraphicsSettings();

    void setResolution(int width, int height);
    void setFullScreen(bool isFullScreen);
    void setVSync(bool enable);

    int getWidth() const;
    int getHeight() const;
    bool isFullScreen() const;
    bool isVSyncEnabled() const;

private:
    int width;
    int height;
    bool fullScreen;
    bool vSyncEnabled;
};

#endif // GRAPHICS_SETTINGS_H
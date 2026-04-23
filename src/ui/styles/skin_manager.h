#ifndef SKIN_MANAGER_H
#define SKIN_MANAGER_H

#include <string>
#include <map>

class SkinManager {
public:
    SkinManager();
    ~SkinManager();

    void loadSkin(const std::string& skinName);
    void applySkin();
    std::string getCurrentSkin() const;

private:
    std::string currentSkin;
    std::map<std::string, std::string> skins;
};

#endif // SKIN_MANAGER_H
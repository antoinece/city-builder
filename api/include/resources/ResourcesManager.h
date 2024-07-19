
#ifndef COREMATHS_RESOURCESMANAGER_H
#define COREMATHS_RESOURCESMANAGER_H

#include <SFML/Graphics.hpp>
#include <array>

class ResourcesManager 
{

public:

    enum class Resource
    {
        kEmpty,
        kWall,
        kWoodHouse,
        kFlower,
        kButton,
        kStoneHouse,
        kWoodMan,
        kCaillou,
        kStoneMan,
        kLength
    };

    enum class Font
    {
        kArial,
        kLength
    };

private:
    void LoadTextures();
    void LoadFonts();

    std::array<sf::Texture, static_cast<int>(Resource::kLength)> textures_;
    std::array<sf::Font, static_cast<int>(Font::kLength)> fonts_;

    sf::Texture blank_texture_;
    sf::Font blank_font_;

public:

    ResourcesManager();
    ~ResourcesManager();

    static ResourcesManager& Get();

    
    ResourcesManager(const ResourcesManager& obj) = delete;
    ResourcesManager& operator=(const ResourcesManager&) = delete;

    sf::Texture& GetTexture(Resource resource_id);
};



#endif

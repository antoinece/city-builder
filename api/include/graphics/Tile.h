#ifndef COREMATHS_TILE_H
#define COREMATHS_TILE_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Window.hpp>

#include "resources/ResourcesManager.h"

class Tile : public sf::Drawable
{
public:
    enum class TileType
    {
        kGround,
        kForest,
        kCutTree
    };
    Tile();
    Tile(ResourcesManager::Resource resource, float x, float y, bool walkable);
    sf::Vector2i GetPosition();
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    bool is_walkable_;

private:
    int tile_height_;
    int tile_width_;
    sf::Sprite sprite_;
    TileType type_;

public:

    bool is_selected_ = false;
    void Select();
    void Unselect();
    sf::Vector2f Position() const { return sprite_.getPosition(); }
    TileType Type() const { return type_; }

    bool is_walkable() const { return is_walkable_; }
    void set_walkable(bool is_walkable);

    sf::Texture& GetFromType();
    sf::Sprite sprite() const { return sprite_; }
    void SetType(TileType new_type);

};

#endif // COREMATHS_TILE_H
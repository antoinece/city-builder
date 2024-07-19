
#ifndef COREMATHS_SELECTEDTILES_H
#define COREMATHS_SELECTEDTILES_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include "graphics/tilemap.h"

class SelectedTiles : public sf::Drawable , public sf::Transformable
{
public:

    SelectedTiles();


    sf::Vector2i GetSPos() { return s_pos; }

    void hoveredTile(const sf::RenderWindow& window, Tilemap& myTilemap, int windowWidth, int windowHeight);


    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void HandleEvent(const sf::Event& event);
private:

    sf::RectangleShape selectedTile_;
    bool pressed;
	sf::Vector2i pressed_pos_;
    sf::Vector2i mouse_tile_coord_;

    sf::Vector2i s_pos;
};

#endif // COREMATHS_SELECTEDTILES_H
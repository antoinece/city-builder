#pragma once
#include <functional>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/View.hpp>


#include "Tile.h"

class Tile;

class Tilemap : public sf::Drawable
{
public:
    

    Tilemap(int tilemap_height, int tilemap_width, Tile* tilemap);
    ~Tilemap();

    
    void Generate();
    sf::Sprite tile_state(int x, int y) const;
    void set_tile_state(int x, int y,ResourcesManager::Resource resourceId);
    void PrintTilemap() const;

    sf::View move();
    sf::View view_;
    sf::Vector2f offset_;
    sf::Vector2f Get_offset(){ return offset_; }
    sf::Vector2f Get_view_center(){ return view_.getCenter(); }

    sf::Vector2i Coords_to_tile_pos(sf::Vector2f) const;
    int const tile_height_;
    int const tile_width_;
    std::vector<sf::Vector2f> GetWalkables();

    sf::Vector2f GetClosestTree(sf::Vector2f pos);
    [[nodiscard]] bool GatherTree(sf::Vector2f pos);

    sf::Vector2f GetClosestHome(sf::Vector2f pos);
    sf::Vector2f GetClosestCaillou(sf::Vector2f pos);
    [[nodiscard]] bool GatherCaillou(sf::Vector2f pos);
    //std::function<void(Tile&)> ClickedTile;
    sf::Vector2i HandleEvent(const sf::Event& event);
    Tile GetTile(int x, int y) const;
    bool house = false;
    bool houseS = false;
    int nb_caillou_ = 10;
    int nb_tree_ = 10;
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::Vector2f a;
    sf::Sprite default_;
    int const tilemap_height_;
    int const tilemap_width_;
    std::vector<sf::Vector2f> trees_;
    std::vector<sf::Vector2f> caillou_;
    std::vector<sf::Vector2f> home_;
    Tile tileSelected_;
    Tile* tilemap_;
    sf::Vector2u playground_tile_offset_u_;
   
};

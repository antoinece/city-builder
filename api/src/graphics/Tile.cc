#include "graphics/Tile.h"

#include <Tracy/Tracy.hpp>

Tile::Tile() : is_walkable_(false)
{

}

Tile::Tile(ResourcesManager::Resource resource, float x, float y, bool walkable)
{
#ifdef TRACY_ENABLE
    ZoneScoped;
#endif

    tile_height_ = 16;
    tile_width_ = 16;
    sprite_.setTexture(ResourcesManager::Get().GetTexture(resource));
    sprite_.setPosition(x*tile_width_, y*tile_height_);
    is_walkable_ = walkable;
}

sf::Vector2i Tile::GetPosition()
{
    int x = sprite_.getPosition().x / tile_width_;
    int y = sprite_.getPosition().y / tile_height_;
    return sf::Vector2i(x,y);
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite_, states);
}

void Tile::set_walkable(const bool is_walkable)
{
    is_walkable_ = is_walkable;
}

void Tile::Select()
{
    is_selected_ = true;
}
void Tile::Unselect()
{
    is_selected_ = false;
}

sf::Texture& Tile::GetFromType()
{
	switch (type_)
	{
	case TileType::kForest:
		if (rand() % 2 != 0)
			return ResourcesManager::Get().GetTexture(ResourcesManager::Resource::kWall);
		else
			return ResourcesManager::Get().GetTexture(ResourcesManager::Resource::kWall);
		break;

	case TileType::kCutTree:
		return ResourcesManager::Get().GetTexture(ResourcesManager::Resource::kFlower);

	case TileType::kGround:
		return ResourcesManager::Get().GetTexture(ResourcesManager::Resource::kWoodHouse);
		break;
	default:;
	}



}

void Tile::SetType(TileType new_type)
{
    type_ = new_type;
    sprite_.setTexture(GetFromType());
}

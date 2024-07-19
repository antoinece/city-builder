
#include <iostream>

#include <gameplay/building_manager.h>

#include "gameplay/house.h"
#include "gameplay/mill.h"

void BuildingManager::SetActive(bool active)
{
	is_active_ = active;
}
bool BuildingManager::GetActive() const
{
	return is_active_;
}

void BuildingManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& b : buildings_)
	{
		target.draw(b, states);
	}
}

void BuildingManager::AddHouse(Tile& tile)
{
	if (!is_active_)
	{
		return;
	}

	std::cout << "Tile clicked, can we finally add a house ? [" << tile.Position().x << ":" << tile.Position().y << "]" << std::endl;

	if (tile.Type() == Tile::TileType::kGround)
	{
		House newHouse(tile.Position().x, tile.Position().y);

		buildings_.emplace_back(newHouse);
	}

}

void BuildingManager::AddMill(Tile& tile)
{

	if (is_active_)
	{
		std::cout << "Tile clicked, can we finally add a house ? [" << tile.Position().x << ":" << tile.Position().y << "]" << std::endl;

		if (tile.Type() == Tile::TileType::kGround)
		{
			Mill newMill(tile.Position().x, tile.Position().y);

			buildings_.emplace_back(newMill);
		}
	}

	is_active_ = false;

}
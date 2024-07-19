#include "graphics/tilemap.h"

#include <iostream>
#include <ostream>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <Tracy/Tracy.hpp>

#include "sfml_vec2f.h"
#include "../../../Core/include/maths/vec2i.h"

Tilemap::Tilemap(int tilemap_height, int tilemap_width, Tile* tilemap)
	: tilemap_height_(tilemap_height), tilemap_width_(tilemap_width), tilemap_(tilemap),
	tile_height_(16), tile_width_(16)  // Dimensions des tuiles définies ici
{

#ifdef TRACY_ENABLE
	ZoneScoped;
#endif

	tilemap_ = new Tile[tilemap_height_ * tilemap_width_]{  };

	view_.setSize(800, 600);
	view_.setCenter(view_.getSize().x / 2, view_.getSize().y / 2);
	Tilemap::playground_tile_offset_u_ = sf::Vector2u(tile_height_, tile_width_);
}

Tilemap::~Tilemap()
{
	delete[] tilemap_;
}



void Tilemap::Generate()
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif

	for (int x = 0; x < tilemap_width_; x++)
	{
		for (int y = 0; y < tilemap_height_; y++)
		{
			switch (rand() % 4)
			{
			case 0:
				set_tile_state(x, y, ResourcesManager::Resource::kWall);
				break;
			case 1:
				set_tile_state(x, y, ResourcesManager::Resource::kWall);
				
				break;
			case 2:
				set_tile_state(x, y, ResourcesManager::Resource::kFlower);
				trees_.emplace_back(x * 16, y * 16);
				break;
			case 3:
				set_tile_state(x, y, ResourcesManager::Resource::kCaillou);
				caillou_.emplace_back(x * 16, y * 16);
				break;
			default:
				set_tile_state(x, y, ResourcesManager::Resource::kEmpty);
				break;

			}
		}
	}
	tileSelected_ = GetTile(100, 100);
}

sf::Sprite Tilemap::tile_state(int x, int y) const
{
	if (x >= 0 && x < tilemap_width_ && y >= 0 && y < tilemap_height_)
	{
		return tilemap_[y * tilemap_width_ + x].Tile::sprite();
	}
	return default_;
}

void Tilemap::set_tile_state(int x, int y, ResourcesManager::Resource resourceId)
{
	if (x >= 0 && x < tilemap_width_ && y >= 0 && y < tilemap_height_)
	{
		tilemap_[y * tilemap_width_ + x] = Tile(resourceId, x, y, true);
	}
}

void Tilemap::PrintTilemap() const
{
	for (int y = 0; y < tilemap_height_; ++y)
	{
		for (int x = 0; x < tilemap_width_; ++x)
		{
			//std::cout << tilemap_[y * tilemap_width_ + x] << " ";
		}
		std::cout << std::endl;
	}
}

sf::View Tilemap::move()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		view_.move(3, 0);
		offset_.x = offset_.x + 3;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		view_.move(-3, 0);
		offset_.x = offset_.x - 3;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		view_.move(0, 3);
		offset_.y = offset_.y + 3;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		view_.move(0, -3);
		offset_.y = offset_.y - 3;
	}
	return view_;
}


std::vector<sf::Vector2f> Tilemap::GetWalkables()
{



	std::vector<sf::Vector2f> walkables;

	for (int y = 0; y < tilemap_height_; ++y)
	{
		for (int x = 0; x < tilemap_width_; ++x)
		{
			const Tile& t = tilemap_[y * tilemap_width_ + x];
			if (t.is_walkable())
			{
				walkables.emplace_back(t.Position());
			}
		}
	}

	return walkables;



}

sf::Vector2f Tilemap::GetClosestTree(sf::Vector2f pos)
{
	if (trees_.empty()) {
		std::cerr << "trees_ est vide" << std::endl;
		//return sf::Vector2f(); // ou une valeur par défaut appropriée
	}

	sf::Vector2f closestTree;
	float closest_tree_distance = std::numeric_limits<float>::infinity();

	std::for_each(trees_.begin(), trees_.end(), [&closest_tree_distance, &closestTree, pos](const sf::Vector2f& tree)
		{
			const float sq_dist = squaredMagnitude(tree - pos);

			if (sq_dist < closest_tree_distance)
			{
				closestTree = tree;
				closest_tree_distance = sq_dist;
			}
		});

	return closestTree;


}

bool Tilemap::GatherTree(sf::Vector2f pos)
{



	auto tree = std::find_if(trees_.begin(), trees_.end(), [pos](const sf::Vector2f& t) { return pos == t; });

	if (tree != trees_.end())
	{
		nb_tree_++;
		std::cout << "tree Cut \nnb de tree : " << nb_tree_ << "\n";
		trees_.erase(tree);

		// change tile type -----------
		set_tile_state(pos.x / 16, pos.y / 16, ResourcesManager::Resource::kWall);

		return true;
	}
	else
	{
		std::cout << "no trees found";
		return false;
	}



}


sf::Vector2f Tilemap::GetClosestCaillou(sf::Vector2f pos)
{
	if (caillou_.empty()) {
		std::cerr << "trees_ est vide" << std::endl;
		//return sf::Vector2f(); // ou une valeur par défaut appropriée
	}

	sf::Vector2f closestCaillou;
	float closest_caillou_distance = std::numeric_limits<float>::infinity();

	std::for_each(caillou_.begin(), caillou_.end(), [&closest_caillou_distance, &closestCaillou, pos](const sf::Vector2f& tree)
		{
			const float sq_dist = squaredMagnitude(tree - pos);

			if (sq_dist < closest_caillou_distance)
			{
				closestCaillou = tree;
				closest_caillou_distance = sq_dist;
			}
		});

	return closestCaillou;


}


sf::Vector2f Tilemap::GetClosestHome(sf::Vector2f pos)
{
	if (home_.empty()) {
		std::cerr << "home_ est vide" << std::endl;
		//return sf::Vector2f(); // ou une valeur par défaut appropriée
	}

	sf::Vector2f closestHome;
	float closest_Home_distance = std::numeric_limits<float>::infinity();

	std::for_each(home_.begin(), home_.end(), [&closest_Home_distance, &closestHome, pos](const sf::Vector2f& tree)
		{
			const float sq_dist = squaredMagnitude(tree - pos);

			if (sq_dist < closest_Home_distance)
			{
				closestHome = tree;
				closest_Home_distance = sq_dist;
			}
		});

	return closestHome;


}

bool Tilemap::GatherCaillou(sf::Vector2f pos)
{
	nb_caillou_++;
	std::cout << "caillou Cut \nnb de caillou : " << nb_caillou_ << "\n";



	auto caillou = std::find_if(caillou_.begin(), caillou_.end(), [pos](const sf::Vector2f& t) { return pos == t; });

	if (caillou != caillou_.end())
	{
		

		caillou_.erase(caillou);

		// change tile type -----------
		set_tile_state(pos.x / 16, pos.y / 16, ResourcesManager::Resource::kWall);

		return true;
	}
	else
	{
		std::cout << "no caillou found";
		return false;
	}



}


Tile Tilemap::GetTile(int x, int y) const
{
	if (x >= 0 && x < tilemap_width_ && y >= 0 && y < tilemap_height_)
	{
		return tilemap_[y * tilemap_width_ + x];
	}
}

void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

#ifdef TRACY_ENABLE
	ZoneScoped;
#endif
	sf::Vector2f view_center = view_.getCenter();
	sf::Vector2i tile_pos = Coords_to_tile_pos(view_center);
	for (int y = tile_pos.y - 20; y < tile_pos.y + 20; ++y)
	{
		if (y < tilemap_height_ && y >= 0)
		{
			for (int x = tile_pos.x - 25; x < tile_pos.x + 26; ++x)
			{
				if (x < tilemap_width_ && x >= 0)
				{
					//TileState tileState = ;

					//sf::Sprite sprite = sprite_[tileState];
					//sprite.setPosition(x * tile_width_, y * tile_height_);
					target.draw(tile_state(x, y), states);

				}
			}
		}
	}
	/*sf::Vector2i mouse_pos = Coords_to_tile_pos(static_cast<sf::Vector2f> ( sf::Mouse::getPosition()));
	sf::Sprite sprite =sprite_[tile_state(mouse_pos.x,mouse_pos.y)];
	sprite.setPosition(static_cast<sf::Vector2f>(mouse_pos));
	target.draw(sprite, states);*/
}

sf::Vector2i Tilemap::Coords_to_tile_pos(sf::Vector2f coords) const
{
	sf::Vector2i tile_pos = sf::Vector2i(std::floor(coords.x / tile_width_), std::floor(coords.y / tile_height_));
	//std::cout << "x : " << tile_pos.x << " y : " << tile_pos.y << "\n";
	return tile_pos;
}


sf::Vector2i Tilemap::HandleEvent(const sf::Event& event)
{
	// Check for mouse button pressed event
	if (house||houseS)
	{
		
		if (event.type == sf::Event::MouseMoved) {
			sf::Vector2f mousePosition = sf::Vector2f(
				event.mouseMove.x - event.mouseMove.x % playground_tile_offset_u_.x,
				event.mouseMove.y - event.mouseMove.y % playground_tile_offset_u_.y
			);
			// Unselect one cached

			// Unselect all
			//std::for_each(tiles_.begin(), tiles_.end(), [](Tile& t) {t.Unselect(); });
			a.x = (mousePosition.x + Get_offset().x) /16;
			a.y = (mousePosition.y + Get_offset().y) /16;
		}


		if (event.type == sf::Event::MouseButtonReleased)
		{
			// Check if the left mouse button is pressed
			if (event.mouseButton.button == sf::Mouse::Left) {
				// Code à faire pour le bouton ---------------------------------------------------
				if (house&&nb_tree_>9)
				{
					nb_tree_ = nb_tree_ - 10;
					set_tile_state(a.x, a.y, ResourcesManager::Resource::kStoneHouse);
					home_.emplace_back(a.x * 16,a.y * 16);
					return sf::Vector2i(a.x, a.y);
				}
				if (houseS && nb_caillou_ > 9)
				{
					nb_caillou_ = nb_caillou_ - 10;
					set_tile_state(a.x, a.y, ResourcesManager::Resource::kWoodHouse);
					home_.emplace_back(a.x * 16, a.y * 16);
					return sf::Vector2i(a.x, a.y);
				}
			}
		}
	}
	return sf::Vector2i(0,0);
}
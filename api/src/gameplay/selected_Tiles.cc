#include "gameplay/selected_Tiles.h"

#include <iostream>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Mouse.hpp>
#include <Tracy/Tracy.hpp>

// Constructor
SelectedTiles::SelectedTiles()
{
	selectedTile_.setSize(sf::Vector2f(16.0f, 16.0f));
	selectedTile_.setFillColor(sf::Color(255, 0, 0, 0));
	selectedTile_.setOutlineColor(sf::Color(250, 250, 250));
	selectedTile_.setOutlineThickness(-1);
	pressed = false;
}

// Function to update the position of the hovered tile
void SelectedTiles::hoveredTile(const sf::RenderWindow& window, Tilemap& myTilemap, int windowWidth, int windowHeight)
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif

	sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
	mouse_tile_coord_.x = (mouse_pos.x + myTilemap.Get_offset().x) / 16;
	mouse_tile_coord_.y = (mouse_pos.y + myTilemap.Get_offset().y) / 16;

	s_pos = mouse_tile_coord_;

	int scale_x = mouse_tile_coord_.x - pressed_pos_.x ;
	int scale_y = mouse_tile_coord_.y - pressed_pos_.y ;

	if (scale_x == 0)
	{
		scale_x = 1;
	}
	if (scale_y == 0)
	{
		scale_y = 1;
	}

	if (!pressed)
	{
		selectedTile_.setPosition(
			mouse_tile_coord_.x * 16,
			mouse_tile_coord_.y * 16);
		//selectedTile_.setScale(1, 1);
		selectedTile_.setSize(sf::Vector2f(16.0f, 16.0f));
	}
	else
	{
		//selectedTile_.setScale(scale_x, scale_y);
		selectedTile_.setSize(sf::Vector2f(16.0f * scale_x , 16.0f * scale_y));
	}

}

// Draw method
void SelectedTiles::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(selectedTile_, states);
}


void SelectedTiles::HandleEvent(const sf::Event& event)
{

	// Check for mouse button pressed event
	if (event.type == sf::Event::MouseButtonReleased) {

		if (event.mouseButton.button == sf::Mouse::Left) {
			pressed = false;
		}
	}

	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left) {
			if (!pressed)
			{
				pressed_pos_.x = selectedTile_.getPosition().x / 16;
				pressed_pos_.y = selectedTile_.getPosition().y / 16;
				pressed = true;
				
			}
			
		}
	}

}
#include "resources/ResourcesManager.h"

#include <iostream>
#include <Tracy/Tracy.hpp>


void ResourcesManager::LoadTextures()
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif


	blank_texture_ = sf::Texture();

	if (!textures_[(int)Resource::kWall].loadFromFile("ressources/sprites/tile_0000.png"))
	{
		std::cerr << "Erreur de chargement de la texture pour Wall" << std::endl;
	}

	if (!textures_[(int)Resource::kWoodHouse].loadFromFile("ressources/sprites/tile_0072.png"))
	{
		std::cerr << "Erreur de chargement de la texture pour Dirt" << std::endl;
	}
	
	if (!textures_[(int)Resource::kFlower].loadFromFile("ressources/sprites/tile_0002.png"))
	{
		std::cerr << "Erreur de chargement de la texture pour Flower" << std::endl;
	}

	if (!textures_[(int)Resource::kButton].loadFromFile("ressources/sprites/green_button01.png"))
	{
		std::cerr << "Erreur de chargement de la texture pour Button" << std::endl;
	}

	if (!textures_[(int)Resource::kStoneHouse].loadFromFile("ressources/sprites/tile_0078.png"))
	{
		std::cerr << "Erreur de chargement de la texture pour Bucket" << std::endl;
	}

	if (!textures_[(int)Resource::kWoodMan].loadFromFile("ressources/sprites/tile_0051.png"))
	{
		std::cerr << "Erreur de chargement de la texture pour WoodMan" << std::endl;
	}

	if (!textures_[(int)Resource::kCaillou].loadFromFile("ressources/sprites/tile_0025.png"))
	{
		std::cerr << "Erreur de chargement de la texture pour WoodMan" << std::endl;
	}

	if (!textures_[(int)Resource::kStoneMan].loadFromFile("ressources/sprites/tile_0186.png"))
	{
		std::cerr << "Erreur de chargement de la texture pour WoodMan" << std::endl;
	}

}

void ResourcesManager::LoadFonts()
{

#ifdef TRACY_ENABLE
	ZoneScoped;
#endif
	blank_font_ = sf::Font();

	if (!fonts_[(int)Font::kArial].loadFromFile("ressources/fonts/arial.ttf"))
	{
		std::cerr << "Erreur de chargement de la font arial" << std::endl;
	}
	
}

static ResourcesManager* instance_ = nullptr;
ResourcesManager::ResourcesManager()
{
	instance_ = this;
	LoadTextures();
	//LoadFonts();
}

ResourcesManager::~ResourcesManager()
{
	instance_ = nullptr;
}

ResourcesManager& ResourcesManager::Get()
{

	return *instance_;
}


sf::Texture& ResourcesManager::GetTexture(Resource resource_id) {

		return textures_[(int)resource_id];

}
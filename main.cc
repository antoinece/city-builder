#include <iostream>
#include <SFML/Graphics.hpp>
#include <ui/ui_button.h>

#ifdef TRACY_ENABLE
#include <Tracy/Tracy.hpp>
#include <tracy/TracyC.h>
#endif

#include "gameplay/building_manager.h"
#include "graphics/tilemap.h"
#include "resources/ResourcesManager.h"
#include "gameplay/building_manager.h"
#include "gameplay/selected_Tiles.h"
#include "gameplay/stones_man.h"
#include "gameplay/woods_man.h"
#include "maths/vec2i.h"
#include "pathfinding/path.h"
#include "pathfinding/path_finder.h"


static const int WINDOW_WIDTH = 800;
static const int WINDOW_HEIGHT = 600;

int main()
{

	ResourcesManager resources_manager;

	BuildingManager building_manager;
	//PathFinder path_finder;

	SelectedTiles selectedTiles;

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "My window", sf::Style::None);
	window.setFramerateLimit(60);

	//tilemap
	const int height = 1000;
	const int width = 1000;

	Tile* tilemap = new Tile[width * height];
	Tilemap myTilemap(height, width, tilemap);

	myTilemap.Generate();

	std::vector<Woodsman> woodsmen;
	std::vector<Stonesman> stonesmen;

	/*
	UiButton btn_generate(sf::Vector2f(20, 20), sf::Color::Yellow, "Generate");

	btn_generate.callback_ = [&myTilemap]() {
		myTilemap.Generate();
		};


	UiButton btn_add_villager(sf::Vector2f(100, 100), sf::Color::Yellow, "Villager");
	btn_add_villager.setScale(0.5f, 0.5f);
	btn_add_villager.callback_ = [&window, &myTilemap, &woodsmen]()
		{
			woodsmen.emplace_back(200, window.getSize().y / 2, 100, myTilemap);
		};*/

	UiButton btn_add_house(sf::Vector2f(300, 580), sf::Color::Yellow, "Wood Cutter");
	btn_add_house.callback_ = [&building_manager, &window, &myTilemap]()
		{
			myTilemap.house = true;
			myTilemap.houseS = false;
			return true;
		};

	UiButton btn_add_houseS(sf::Vector2f(100, 580), sf::Color::Yellow, "Stone Cutter");
	btn_add_houseS.callback_ = [&building_manager, &window, &myTilemap]()
		{
			myTilemap.houseS = true;
			myTilemap.house = false;
			return true;
		};


	sf::Clock clock;


	sf::Text text;
	sf::Text text2;
	sf::Text text3;
	sf::Font font;
	if (!font.loadFromFile("ressources/fonts/arial.ttf"))
	{
		std::cout << "ssssssssssssssssssssssssss";
	}
	text.setFont(font);
	text2.setFont(font);
	text3.setFont(font);
	text.setString("Hello world");
	text2.setString("Wood Cutter (cost 10 stones)");
	text3.setString("Stone Cutter (cost 10 Wood)");
	text.setCharacterSize(24);
	text2.setCharacterSize(14);
	text3.setCharacterSize(14);
	text2.setPosition(10, 570);
	text3.setPosition(210, 570);

	sf::View view;
	view.setSize(800, 600);
	view.setCenter(view.getSize().x / 2, view.getSize().y / 2);

	while (window.isOpen())
	{


#ifdef TRACY_ENABLE
		ZoneNamedN(gmaeLoop, "game loop", true);
#endif

		for (auto& w : woodsmen)
		{
			w.Tick();
		}
		for (auto& w : stonesmen)
		{
			w.Tick();
		}

		sf::Time frameTime = clock.restart();


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			/*if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right)
			{
				sf::Vector2f destination(event.mouseButton.x, event.mouseButton.y);
				Path p = path_finder.CalculatePath(myTilemap.GetWalkables(), woodsman.getPosition(), destination, 16);
				woodsman.set_path(p);
			}*/

			selectedTiles.HandleEvent(event);/*
			btn_add_villager.HandleEvent(event);
			btn_generate.HandleEvent(event);*/
			if (!btn_add_house.HandleEvent(event) && !btn_add_houseS.HandleEvent(event))
			{
				sf::Vector2i a = myTilemap.HandleEvent(event);
				if (a != sf::Vector2i(0, 0))
				{
					if (myTilemap.house)
					{
						woodsmen.emplace_back(a.x * 16, a.y * 16, 50, myTilemap);
					}
					if (myTilemap.houseS)
					{
						stonesmen.emplace_back(a.x * 16, a.y * 16, 50, myTilemap);
					}
				}
					}



			}
		text.setString("stone : "+std::to_string(myTilemap.nb_caillou_) + "\nwood : "+ std::to_string(myTilemap.nb_tree_));
		
		selectedTiles.hoveredTile(window, myTilemap, WINDOW_WIDTH, WINDOW_HEIGHT);

		//window
		window.clear(sf::Color::Black);

		window.setView(myTilemap.move());
#ifdef TRACY_ENABLE
		TracyCZoneN(windowDraw, "window draw", true);
#endif
		//---- Things to measure



		window.draw(myTilemap);
		window.draw(selectedTiles);
		window.draw(building_manager);
		for (auto& w : woodsmen)
		{
			window.draw(w);
			}
		for (auto& w : stonesmen)
		{
			window.draw(w);
		}

		window.setView(view);
		/*
		window.draw(btn_generate);
		window.draw(btn_add_villager);*/
		window.draw(btn_add_house);
		window.draw(btn_add_houseS);
		window.draw(text);
		window.draw(text2);
		window.draw(text3);
#ifdef  TRACY_ENABLE
		TracyCZoneEnd(windowDraw);
#endif

#ifdef TRACY_ENABLE
		TracyCZoneN(windowDisplay, "window display", true);
#endif
		window.display();

#ifdef  TRACY_ENABLE
		TracyCZoneEnd(windowDisplay);
#endif

#ifdef TRACY_ENABLE
		FrameMark;
#endif

	}
}

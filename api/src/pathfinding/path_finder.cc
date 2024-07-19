#include "pathfinding/path_finder.h"

#include <iostream>
#include <ostream>

#include "sfml_vec2f.h"

namespace Pathfinder
{
	static std::vector<sf::Vector2f> ConstructPath(const PathPoint& exit_point)
	{
		std::vector<sf::Vector2f> positions;

		PathPoint point = exit_point;

		positions.emplace_back(point.position);

		while (point.parent != nullptr)
		{
			point = *point.parent;
			positions.insert(positions.begin(), point.position);
		}

		return positions;
	}

	Path CalculatePath(std::vector<sf::Vector2f> positions, sf::Vector2f start, sf::Vector2f end, int tile_map_offset)
	{

		Path path;

		sf::Vector2f rounded_end;
		rounded_end.x = end.x - fmod(end.x, (float)tile_map_offset);
		rounded_end.y = end.y - fmod(end.y, (float)tile_map_offset);

		// --------------------------
		// Controle de la pertinence de la destination (distance, présence dans la liste des positions eventuelles)

		sf::Vector2f rounded_start;
		rounded_start.x = start.x - fmod(start.x, (float)tile_map_offset );
		rounded_start.y = start.y - fmod(start.y, (float)tile_map_offset );

		// -- Prepare the list with --
		positions.emplace_back(rounded_start);
		positions.emplace_back(rounded_end);

		// --
		std::priority_queue<PathPoint, std::vector<PathPoint>, std::greater<PathPoint>> open_queue;

		// TODO to unordered set
		std::vector<sf::Vector2f> open_list;
		std::vector<sf::Vector2f> closed_list;

		open_queue.emplace(0, Magnitude(rounded_end - rounded_start), rounded_start);
		open_list.emplace_back(rounded_start);

		while (!open_queue.empty())
		{
			// Find the lowest score point
			auto current = open_queue.top();
			closed_list.emplace_back(current.position);

			open_queue.pop();
			std::erase_if(open_list, [&current](sf::Vector2f p) {return current.position == p; });

			// Did we find the exit of the maze ?
			if (Magnitude(rounded_end - current.position) <= std::numeric_limits<float>::epsilon())
			{
				// :) :) :) :) :) :) :) :) :) :) :) :) :) :)
				// YES WE FOUND IT
				path.SetSteps(ConstructPath(current));
				//std::cout << "Found the path : nb steps = " << path.GetSteps().size() << std::endl;
				return path;
			}

			for (auto neighbour : kNeighbours)
			{
				// ReSharper disable once CppCStyleCast
				sf::Vector2f neighbourPos = current.position + neighbour * (float)tile_map_offset;

				// Tous les voisins
				auto found_position = std::find_if(positions.begin(), positions.end(), [&neighbourPos](sf::Vector2f& pos)
				{
					return pos == neighbourPos;
				});

				// Found a valid neighbour
				// Possible cases : outside of the map, empty lists, etc.
				if (found_position != positions.end())
				{
					bool is_in_closed = std::any_of(
						closed_list.begin(),
						closed_list.end(),
						[found_position](sf::Vector2f& closed_point)
						{
							return Magnitude(closed_point - *found_position) <= std::numeric_limits<float>::epsilon();
						}
					);
					bool is_in_open = std::any_of(
						open_list.begin(),
						open_list.end(),
						[found_position](sf::Vector2f& open_point)
						{
							return Magnitude(open_point - *found_position) <= std::numeric_limits<float>::epsilon();
						}
					);


					if (!is_in_closed && !is_in_open)
					{
						open_queue.emplace(current.g + tile_map_offset, Magnitude(rounded_end - current.position), *found_position, current);
						open_list.emplace_back(*found_position);
					}

				}

			}

		}

		// -
		/*std::cout << "Didn't find the path" << std::endl;
		std::cout << "Start : " << start.x << " " << start.y << std::endl;
		std::cout << "Rounded start : " << rounded_start.x << " " << rounded_start.y << std::endl;
		std::cout << "End : " << end.x << " " << end.y << std::endl;
		std::cout << "Rounded end : " << rounded_end.x << " " << rounded_end.y << std::endl;
		*/
		return path;


	}
}

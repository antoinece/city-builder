#ifndef API_PATH_FINDING_PATH_FINDER_H
#define API_PATH_FINDING_PATH_FINDER_H

#include <array>
#include <memory>

#include "path.h"


struct PathPoint
{

	sf::Vector2f position;

	// Members
	float f;
	float g;
	float h;

	//std::unique_ptr<PathPoint> parent;
	PathPoint* parent;

	// Ctor
	PathPoint();

	//PathPoint(const PathPoint& p)
	//{

	//	g = p.g;
	//	h = p.h;
	//	f = g + h;

	//	position = p.position;

	//	if (p.parent != nullptr)
	//	{
	//		//parent = std::make_unique<PathPoint>(*p.parent);
	//		parent = p.parent;
	//	}

	//}

	PathPoint(float g, float h, sf::Vector2f position, const PathPoint& parent) : g(g), h(h), position(position)
	{
		//this->parent = std::make_unique<PathPoint>(parent);
		this->parent = new PathPoint(parent);
		f = g + h;
	}
	PathPoint(float g, float h, sf::Vector2f position) : g(g), h(h), position(position)
	{
		this->parent = nullptr;
		f = g + h;
	}

	//PathPoint& operator=(const PathPoint& t)
	//{
	//	return *this;
	//}

	// Methods
	//int f() const { return g + h; } // Total cost function

	//// Operators
	//bool operator<(const PathPoint& other) const {
	//	return this->f() < other.f();
	//}
	//bool operator>(const PathPoint& other) const {
	//	return this->f() > other.f();
	//}

	// Operators
	bool operator<(const PathPoint& other) const {
		return this->f < other.f;
	}
	bool operator>(const PathPoint& other) const {
		return this->f > other.f;
	}
};


const std::array kNeighbours = {
	sf::Vector2f(0,1),
	sf::Vector2f(1,0),
	sf::Vector2f(0,-1),
	sf::Vector2f(-1, 0)
};


//class PathFinder
//{
//private:
//	std::vector<sf::Vector2f> ConstructPath(const PathPoint& exit_point);
//
//public:
//	Path CalculatePath(std::vector<sf::Vector2f> positions, sf::Vector2f start, sf::Vector2f end, int tile_map_offset);
//
//};

namespace Pathfinder
{
	Path CalculatePath(std::vector<sf::Vector2f> positions, sf::Vector2f start, sf::Vector2f end, int tile_size);
};

#endif // API_PATH_FINDING_PATH_FINDER_H

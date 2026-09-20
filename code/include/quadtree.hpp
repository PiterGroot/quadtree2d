#pragma once
#include <vector>

#include "rectangle.hpp"
#include "point.hpp"

namespace qt2d
{
	class Quadtree
	{
	public:
		Quadtree(qt2d::Rectangle inBoundary, int inCapacity);

		bool Insert(Point& point);
		void Query(Rectangle range, std::vector<Point>& found);

		void Draw();
		void Log() const;

	private:
		void Subdivide();

	private:
		std::vector<Point> points;

		Quadtree* childNw = nullptr;
		Quadtree* childNe = nullptr;
		Quadtree* childSw = nullptr;
		Quadtree* childSe = nullptr;

		Rectangle boundary;

		int capacity = 1;
		bool divided = false;

	};
}
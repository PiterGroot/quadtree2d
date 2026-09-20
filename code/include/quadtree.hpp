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
		~Quadtree();

		bool Insert(Point& point);
		void Query(Rectangle range, std::vector<Point>& found);
		void Clear();

		void Draw();

	private:
		void Subdivide();
		void Query(Rectangle range, std::vector<Point>& found, int& count);

	public:
		int queryCount = 0;

	private:
		std::vector<Point> points;

		Quadtree* childNw = nullptr;
		Quadtree* childNe = nullptr;
		Quadtree* childSw = nullptr;
		Quadtree* childSe = nullptr;

		Rectangle boundary;

		bool divided = false;
		int capacity = 1;
	};
}
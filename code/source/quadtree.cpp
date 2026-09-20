#include "quadtree.hpp"
#include <stdio.h>
#include <raylib/include/raylib.h>

using namespace qt2d;

Quadtree::Quadtree(qt2d::Rectangle inBoundary, int inCapacity)
{
	boundary = inBoundary;
	capacity = inCapacity;

	points.reserve(capacity);
}

bool Quadtree::Insert(Point& point)
{
	if (!boundary.Contains(point))
		return false;

	if (points.size() < capacity)
	{
		points.push_back(point);
		return true;
	}
	else
	{
		if (!divided)
			Subdivide();

		if (childNw->Insert(point))
			return true;

		else if (childNe->Insert(point))
			return true;

		else if (childSe->Insert(point))
			return true;

		else if (childSw->Insert(point))
			return true;
	}

	return false;
}

void Quadtree::Query(Rectangle range, std::vector<Point>& found)
{
	if (!boundary.Intersects(range))
	{
		return;
	}
	else
	{
		for (auto& point : points)
		{
			if (range.Contains(point))
				found.push_back(point);
		}
	}

	if (divided)
	{
		childNw->Query(range, found);
		childNe->Query(range, found);
		childSw->Query(range, found);
		childSe->Query(range, found);
	}
}

void Quadtree::Draw()
{
	DrawRectangleLines(
		(int)(boundary.x - boundary.w),
		(int)(boundary.y - boundary.h),
		(int)(boundary.w * 2.0f),
		(int)(boundary.h * 2.0f),
		WHITE
	);

	if (divided)
	{
		childNw->Draw();
		childNe->Draw();
		childSe->Draw();
		childSw->Draw();
	}

	for (auto& point : points)
	{
		DrawCircle((int)point.x, (int)point.y, 1.0f, WHITE);
	}
}


void Quadtree::Log() const
{
	printf("Boundary h: %f\n", boundary.h);
	printf("Boundary w: %f\n", boundary.w);
	printf("Boundary x: %f\n", boundary.x);
	printf("Boundary y: %f\n", boundary.y);
}

void Quadtree::Subdivide()
{
	Rectangle b = boundary;

	float halfWidth = b.w / 2.0f;
	float halfHeight = b.h / 2.0f;

	Rectangle neRectangle = { b.x + halfWidth,  b.y - halfHeight, halfWidth, halfHeight };
	Rectangle nwRectangle = { b.x - halfWidth,  b.y - halfHeight, halfWidth, halfHeight };
	Rectangle seRectangle = { b.x + halfWidth,  b.y + halfHeight, halfWidth, halfHeight };
	Rectangle swRectangle = { b.x - halfWidth,  b.y + halfHeight, halfWidth, halfHeight };

	childNw = new Quadtree(nwRectangle, capacity);
	childNe = new Quadtree(neRectangle, capacity);
	childSw = new Quadtree(swRectangle, capacity);
	childSe = new Quadtree(seRectangle, capacity);

	divided = true;
}

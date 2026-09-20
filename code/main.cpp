#include <iostream>
#include <raylib/include/raylib.h>

#include "rectangle.hpp"
#include "point.hpp"
#include "quadtree.hpp"

using namespace qt2d;

int main()
{
	int width = 400;
	int height = 400;

	InitWindow(width, height, "Quadtree");
	SetTargetFPS(60);

	qt2d::Rectangle boundary = { 200, 200, 200, 200 };
	Quadtree qtree = Quadtree(boundary, 1);

	for (int i = 0; i < 150; i++)
	{
		Point p = { (float)(rand() % width), (float)(rand() % height) };
		qtree.Insert(p);
	}

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		DrawFPS(0, 0);

		qtree.Draw();

		if (IsMouseButtonDown(0))
		{
			Vector2 moisePosition = GetMousePosition();
			Point p = { (float)(moisePosition.x), (float)(moisePosition.y) };

			qtree.Insert(p);
		}

		EndDrawing();
	}
}
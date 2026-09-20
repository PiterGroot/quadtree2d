#include <iostream>
#include <raylib/include/raylib.h>

#include "rectangle.hpp"
#include "point.hpp"
#include "quadtree.hpp"

using namespace qt2d;

int main()
{
	const int width = 800;
	const int height = 800;

	InitWindow(width, height, "Quadtree | Press space to randomize query rect");

	SetTargetFPS(60);
	srand(static_cast<unsigned int>(time(nullptr)));

	const float widthHalfLength = (float)width / 2.0f;
	const float heighthHalfLength = (float)height / 2.0f;

	qt2d::Rectangle boundary = { widthHalfLength, heighthHalfLength, widthHalfLength, heighthHalfLength };
	Quadtree qtree = Quadtree(boundary, 1);

	{ // Randomly insert points in the tree.
		for (int i = 0; i < 300; i++)
		{
			Point p = { (float)(rand() % width), (float)(rand() % height) };
			qtree.Insert(p);
		}
	}

	std::vector<Point> points;
	qt2d::Rectangle range = { (float)(rand() % width), (float)(rand() % height), 100, 100 };
	{ // Initial point query.
		qtree.Query(range, points);
	}

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		{ // Handle input.
			if (IsKeyDown(KEY_SPACE))
			{
				range.x = (float)(rand() % width);
				range.y = (float)(rand() % height);

				range.w = (float)(rand() % 100) + 15.0f;
				range.h = (float)(rand() % 100) + 15.0f;

				points.clear();
				qtree.Query(range, points);
			}

			if (IsMouseButtonPressed(0))
			{
				Vector2 moisePosition = GetMousePosition();
				Point p = { (float)(moisePosition.x), (float)(moisePosition.y) };

				qtree.Insert(p);
			}
		}

		{ // Handle drawing.
			qtree.Draw();

			DrawRectangleLinesEx({ range.x - range.w, range.y - range.h, range.w * 2, range.h * 2 }, 2.0f, GREEN);

			for (auto& point : points)
			{
				DrawCircle((int)point.x, (int)point.y, 2.0f, GREEN);
			}
		}

		EndDrawing();
	}
}
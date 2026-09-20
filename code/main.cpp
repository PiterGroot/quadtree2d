#include <iostream>
#include <raylib/include/raylib.h>
#include <string>

#include "rectangle.hpp"
#include "point.hpp"
#include "quadtree.hpp"

using namespace qt2d;

int main()
{
	const int width = 800;
	const int height = 800;
	const int insertedPoints = 300;

	SetConfigFlags(FLAG_VSYNC_HINT);

	InitWindow(width, height, "Quadtree2d");

	srand(static_cast<unsigned int>(time(nullptr)));

	const float widthHalfLength = (float)width / 2.0f;
	const float heighthHalfLength = (float)height / 2.0f;

	qt2d::Rectangle boundary = { widthHalfLength, heighthHalfLength, widthHalfLength, heighthHalfLength };
	Quadtree qtree = Quadtree(boundary, 1);

	{ // Initial randomly inserted points.
		for (int i = 0; i < insertedPoints; i++)
		{
			Point p = { (float)(rand() % width), (float)(rand() % height) };
			qtree.Insert(p);
		}
	}

	std::vector<Point> points;
	qt2d::Rectangle range = { (float)(rand() % width), (float)(rand() % height), 100, 100 };

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		{ // Handle input.
			Vector2 mousePosition = GetMousePosition();

			points.clear();
			qtree.Query(range, points);

			SetWindowTitle((std::string("Quadtree2d | Total points: ") + std::to_string(insertedPoints) + (std::string(" | Checked points: ") + std::to_string(qtree.queryCount))).c_str());

			range.x = mousePosition.x;
			range.y = mousePosition.y;

			if (IsMouseButtonPressed(0)) // Point inserter keybind.
			{
				Vector2 moisePosition = GetMousePosition();
				Point p = { (float)(moisePosition.x), (float)(moisePosition.y) };

				qtree.Insert(p);
			}

			if (IsKeyPressed(KEY_SPACE)) // Point randomizer keybind.
			{
				qtree.Clear();

				for (int i = 0; i < insertedPoints; i++)
				{
					Point p = { (float)(rand() % width), (float)(rand() % height) };
					qtree.Insert(p);
				}
			}

			if (IsKeyDown(KEY_TAB)) // FPS metrics keybind.
				DrawFPS(0, 0);
		}

		{ // Handle drawing.
			qtree.Draw();

			DrawRectangleLinesEx({ range.x - range.w, range.y - range.h, range.w * 2, range.h * 2 }, 2.0f, GREEN);

			for (auto& point : points)
			{
				DrawCircle((int)point.x, (int)point.y, 3.0f, GREEN);
			}
		}

		EndDrawing();
		qtree.queryCount = 0;
	}
}
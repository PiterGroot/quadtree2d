#include <iostream>

#include <raylib/include/raylib.h>

int main()
{
	InitWindow(900, 600, "Quadtree");

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		DrawFPS(0, 0);

		EndDrawing();
	}
}
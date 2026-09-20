#pragma once
#include "point.hpp"

namespace qt2d
{
	struct Rectangle
	{
		float x;
		float y;
		float w;
		float h;

		bool Contains(Point point) const
		{
			return (point.x >= x - w &&
				point.x <= x + w &&
				point.y >= y - h &&
				point.y <= y + h);
		}

		bool Intersects(Rectangle range) const
		{
			return !(range.x - range.w > x + w ||
				range.x + range.w < x - w ||
				range.y - range.h > y + h ||
				range.y + range.h < y - h);
		}
	};
}
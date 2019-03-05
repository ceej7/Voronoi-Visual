#include "stdafx.h"
#include "Vector2.h"
#include <cmath>
Vector2::Vector2()
{
	x = 0;
	y = 0;
	isEnd = false;
}

Vector2::Vector2(double _x, double _y)
{
	x = _x;
	y = _y;
	isEnd = false;
}

Vector2::Vector2(const Vector2 & obj)
{
	x = obj.x;
	y = obj.y;
	isEnd = obj.isEnd;
}

Vector2  Vector2::operator=(const Vector2 & vec)
{
	// TODO: insert return statement here
	x = vec.x;
	y = vec.y;
	isEnd = vec.isEnd;
	return *this;
}

void Vector2::normalize()
{
	if (x == 0 && y == 0) return;
	double len = sqrt(x*x + y * y);
	x = x / len;
	y = y / len;
}

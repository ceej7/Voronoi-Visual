#pragma once
#include "Vector2.h"
class Edge
{
public:
	Vector2 e1;
	Vector2 e2;

	Edge(const Vector2 &ptr1, const Vector2 &ptr2);
	void resize(const Vector2 &ptr1, const Vector2 &ptr2);

	Vector2* intersect_line(const Vector2& p, const Vector2& dir);
};
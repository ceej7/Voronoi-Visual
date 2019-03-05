#pragma once
#include <vector>
#include "Vector2.h"
#include "Edge.h"
class Cell
{
public:
	Vector2 center;
	std::vector<Edge *> e_Ptrs;
	Cell(double x, double y);
	Cell(const Vector2 &c);
	void insertEdges(Edge* e_ptr);
	void removeEdges(Edge* e_ptr);
};

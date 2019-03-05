#pragma once
#include <vector>
#include "Vector2.h"
#include "Edge.h"
#include "Cell.h"
#include <stdlib.h>//rand & srand
#include <ctime>//std::time
extern double randomf(double _min, double _max);
class CView;
class Voronoi
{
public:
	double width;
	double height;
	int site_count;
	CView *pview;
	Voronoi(double w, double h, int n, CView *p);
	~Voronoi();
	std::vector<Vector2 *> set_Sites_Ptrs;
	std::vector<Edge *> set_Edge_Ptrs;
	std::vector<Cell *> set_Cell_Ptrs;
	void insertEdge(Edge *e);
	void insertCell(Cell *c);

	void restart();
private:
	void ranGenerateSite();
	void pointsInfinityCellCreation();
	void appendCellForSite(Vector2* s_ptr);
	void removeEdge(Edge* e, Cell* c);
};
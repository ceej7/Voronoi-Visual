#include "stdafx.h"
#include "Cell.h"

Cell::Cell(double x, double y)
{
	center.x = x;
	center.y = y;
}

Cell::Cell(const Vector2 &c)
{
	center = c;
}

void Cell::insertEdges(Edge * e_ptr)
{
	//TODO: check if e_ptr exists in the e_ptrs vector
	for (Edge* e : e_Ptrs)
	{
		if (e == e_ptr)
		{
			//tempt throw
			throw "duplicated Edge inserted";
			break;
		}
	}
	e_Ptrs.push_back(e_ptr);
}

void Cell::removeEdges(Edge * e_ptr)
{
	std::vector<Edge *>::iterator iter_ePtrs;
	for (iter_ePtrs = e_Ptrs.begin(); iter_ePtrs != e_Ptrs.end(); iter_ePtrs++)
	{
		if (*iter_ePtrs == e_ptr)
		{
			e_Ptrs.erase(iter_ePtrs);
			return;
		}
	}
}

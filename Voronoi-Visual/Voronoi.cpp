#include "stdafx.h"
#include "Voronoi.h"
#include "Voronoi-VisualView.h"
Voronoi::Voronoi(double w, double h, int n, CView *p)
{
	width = w;
	height = h;
	site_count = n;
	pview = p;
}

Voronoi::~Voronoi()
{
	for (auto s : set_Sites_Ptrs)
	{
		delete s;
	}
	for (auto e : set_Edge_Ptrs)
	{
		delete e;
	}
	for (auto c : set_Cell_Ptrs)
	{
		delete c;
	}
}

void Voronoi::insertEdge(Edge * e)
{
	//TODO: adding animation
	for (Edge* e_ptr : set_Edge_Ptrs)
	{
		if (e == e_ptr)
		{
			//tempt throw
			throw "duplicated Edge inserted";
			break;
		}
	}
	set_Edge_Ptrs.push_back(e);
}

void Voronoi::insertCell(Cell * c)
{
	//TODO:
	//all edge is inserted through 
	for (Cell* c_ptr : set_Cell_Ptrs)
	{
		if (c == c_ptr)
		{
			//tempt throw
			throw "duplicated Cell inserted";
			break;
		}
	}

	set_Cell_Ptrs.push_back(c);
	for (Edge* tempt_e_ptr : c->e_Ptrs)
	{
		insertEdge(tempt_e_ptr);
	}
	((CVoronoiVisualView*)pview)->Invalidate(true);
	Sleep(300);
}

void Voronoi::restart()
{
	ranGenerateSite();
	pointsInfinityCellCreation();
	for (Vector2* v_ptr : set_Sites_Ptrs)
	{
		appendCellForSite(v_ptr);
	}
}

void Voronoi::ranGenerateSite()
{
	//generate the number of sites within the pre-defined space
	int i = 0;
	while (i < site_count)
	{
		double x = randomf(0, width);
		double y = randomf(0, height);
		bool toSkip = false;
		for (Vector2* var : set_Sites_Ptrs)
		{
			if (x == var->x&&y == var->y)
			{
				toSkip = true;
				break;
			}
		}
		if (!toSkip)
		{
			Vector2 *vec2 = new Vector2(x, y);
			set_Sites_Ptrs.push_back(vec2);
			i++;
		}
	}
}

void Voronoi::pointsInfinityCellCreation()
{
	Vector2 v1;
	Vector2 v2;
	//create cells at
	//(-w, -h) with {(w/2,h/2),(w/2,-10*h)} & {(w/2,-10*h),(-10*w,h/2)} & {(-10*w,h/2),(w/2,h/2)}
	Cell *cell_ll_ptr = new Cell(-width, -height);
	v1.x = width / 2;
	v1.y = height / 2;
	v2.x = width / 2;
	v2.y = -4 * height;
	Edge *e_ll_1 = new Edge(v1, v2);
	set_Edge_Ptrs.push_back(e_ll_1);
	cell_ll_ptr->insertEdges(e_ll_1);

	v1.x = -4 * width;
	v1.y = height / 2;
	v2.x = width / 2;
	v2.y = -4 * height;
	Edge *e_ll_2 = new Edge(v1, v2);
	set_Edge_Ptrs.push_back(e_ll_2);
	cell_ll_ptr->insertEdges(e_ll_2);

	v1.x = width / 2;
	v1.y = height / 2;
	v2.x = -4 * width;
	v2.y = height / 2;
	Edge *e_ll_3 = new Edge(v1, v2);
	set_Edge_Ptrs.push_back(e_ll_3);
	cell_ll_ptr->insertEdges(e_ll_3);

	//(2w, -h) with {(w/2,h/2),(w/2,-10*h)} & {(w/2,-10*h),(10*w,h/2)} & {(10*w,h/2),(w/2,h/2)}
	Cell *cell_rl_ptr = new Cell(2 * width, -height);
	cell_rl_ptr->insertEdges(e_ll_1);

	v1.x = 4 * width;
	v1.y = height / 2;
	v2.x = width / 2;
	v2.y = -4 * height;
	Edge *e_rl_2 = new Edge(v1, v2);
	set_Edge_Ptrs.push_back(e_rl_2);
	cell_rl_ptr->insertEdges(e_rl_2);

	v1.x = width / 2;
	v1.y = height / 2;
	v2.x = 4 * width;
	v2.y = height / 2;
	Edge *e_rl_3 = new Edge(v1, v2);
	set_Edge_Ptrs.push_back(e_rl_3);
	cell_rl_ptr->insertEdges(e_rl_3);

	//(2w, 2h) {(w/2,h/2),(w/2,10*h)} & {(w/2,10*h),(10*w,h/2)} & {(10*w,h/2),(w/2,h/2)}
	Cell *cell_ru_ptr = new Cell(2 * width, 2 * height);
	v1.x = width / 2;
	v1.y = height / 2;
	v2.x = width / 2;
	v2.y = 4 * height;
	Edge *e_ru_1 = new Edge(v1, v2);
	set_Edge_Ptrs.push_back(e_ru_1);
	cell_ru_ptr->insertEdges(e_ru_1);

	v1.x = 4 * width;
	v1.y = height / 2;
	v2.x = width / 2;
	v2.y = 4 * height;
	Edge *e_ru_2 = new Edge(v1, v2);
	set_Edge_Ptrs.push_back(e_ru_2);
	cell_ru_ptr->insertEdges(e_ru_2);

	cell_ru_ptr->insertEdges(e_rl_3);

	//(-w, 2h) at {(w/2,h/2),(w/2,10*h)} & {(w/2,10*h),(-10*w,h/2)} & {(-10*w,h/2),(w/2,h/2)}
	Cell *cell_lu_ptr = new Cell(-width, 2 * height);

	cell_lu_ptr->insertEdges(e_ll_3);

	v1.x = -4 * width;
	v1.y = height / 2;
	v2.x = width / 2;
	v2.y = 4 * height;
	Edge *e_lu_2 = new Edge(v1, v2);
	set_Edge_Ptrs.push_back(e_lu_2);
	cell_lu_ptr->insertEdges(e_lu_2);

	cell_lu_ptr->insertEdges(e_ru_1);

	//insert cell into Voronoi System
	//remeber that the cell and the Voronoi share the same Edge* pointer
	//means they points to the same location of Edge object
	set_Cell_Ptrs.push_back(cell_ll_ptr);
	set_Cell_Ptrs.push_back(cell_lu_ptr);
	set_Cell_Ptrs.push_back(cell_rl_ptr);
	set_Cell_Ptrs.push_back(cell_ru_ptr);


}

void Voronoi::appendCellForSite(Vector2 * s_ptr)
{
	Cell* new_cPtr = new Cell(*s_ptr);
	//for each existing cell
	for (Cell* existing_cPtr : set_Cell_Ptrs)
	{
		//find the perpendicular bisector line with pb_point and pb_direct
		Vector2 pb_point((new_cPtr->center.x + existing_cPtr->center.x) / 2,
			(new_cPtr->center.y + existing_cPtr->center.y) / 2);
		Vector2 pb_direct((-new_cPtr->center.y + existing_cPtr->center.y), (new_cPtr->center.x - existing_cPtr->center.x));
		pb_direct.normalize();
		//vector to store the points which will be turned into edges
		std::vector<Vector2*> temptPoint;
		for (Edge* e_ptr : existing_cPtr->e_Ptrs)
		{
			double existing_c2p_sqr_01 = (e_ptr->e1.x - existing_cPtr->center.x)*(e_ptr->e1.x - existing_cPtr->center.x)
				+ (e_ptr->e1.y - existing_cPtr->center.y)*(e_ptr->e1.y - existing_cPtr->center.y);
			double new_c2p_sqr_01 = (e_ptr->e1.x - new_cPtr->center.x)*(e_ptr->e1.x - new_cPtr->center.x)
				+ (e_ptr->e1.y - new_cPtr->center.y)*(e_ptr->e1.y - new_cPtr->center.y);
			double existing_c2p_sqr_02 = (e_ptr->e2.x - existing_cPtr->center.x)*(e_ptr->e2.x - existing_cPtr->center.x)
				+ (e_ptr->e2.y - existing_cPtr->center.y)*(e_ptr->e2.y - existing_cPtr->center.y);
			double new_c2p_sqr_02 = (e_ptr->e2.x - new_cPtr->center.x)*(e_ptr->e2.x - new_cPtr->center.x)
				+ (e_ptr->e2.y - new_cPtr->center.y)*(e_ptr->e2.y - new_cPtr->center.y);
			//if e_ptr is on the near side of pb (closer to existing_cPtr_center than to new_cPtr_center)
			Vector2* intersectPoint_Ptr = e_ptr->intersect_line(pb_point, pb_direct);
			if (existing_c2p_sqr_01 > new_c2p_sqr_01 && existing_c2p_sqr_02 > new_c2p_sqr_02)
			{
				//TODO: delete the existing edge from both cell and voronoi
				if(intersectPoint_Ptr != nullptr&&!intersectPoint_Ptr->isEnd)
					removeEdge(e_ptr, existing_cPtr);
				else if(intersectPoint_Ptr == nullptr)
					removeEdge(e_ptr, existing_cPtr);
			}
			else
			{
				
				//clip the far segement and add intersect point to temptPoint
				if (intersectPoint_Ptr != nullptr)
				{
					if (intersectPoint_Ptr->isEnd)
					{
						temptPoint.push_back(intersectPoint_Ptr);
					}
					else if (existing_c2p_sqr_01 <= new_c2p_sqr_01)
					{
						e_ptr->e2 = *intersectPoint_Ptr;
						temptPoint.push_back(intersectPoint_Ptr);
					}
					else if (existing_c2p_sqr_02 <= new_c2p_sqr_02)
					{
						e_ptr->e1 = *intersectPoint_Ptr;
						temptPoint.push_back(intersectPoint_Ptr);
					}
				}
			}
		}
		if (temptPoint.size() == 0)
		{
			//nothing to do
		}
		else if (temptPoint.size() == 2)
		{
			Edge *appending_edge = new Edge(*temptPoint[0], *temptPoint[1]);
			existing_cPtr->insertEdges(appending_edge);
			new_cPtr->insertEdges(appending_edge);
		}
		for (int i = 0; i < temptPoint.size(); i++)
		{
			delete temptPoint.at(i);
		}
	}
	insertCell(new_cPtr);

}

void Voronoi::removeEdge(Edge * e, Cell* c)
{
	//TODO: remove edge from edge_lists and cell_lists
	std::vector<Edge*>::iterator edge_iterators;
	for (edge_iterators = set_Edge_Ptrs.begin(); edge_iterators != set_Edge_Ptrs.end(); edge_iterators++)
	{
		if (*edge_iterators == e)
		{
			set_Edge_Ptrs.erase(edge_iterators);
			break;
		}
	}
	for (int i = 0; i < set_Cell_Ptrs.size(); i++)
	{
		set_Cell_Ptrs.at(i)->removeEdges(e);
	}
	delete e;
}

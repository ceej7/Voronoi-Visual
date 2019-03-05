#include "stdafx.h"
#include "Edge.h"

Edge::Edge(const Vector2 & ptr1, const Vector2 & ptr2)
{
	e1 = ptr1;
	e2 = ptr2;
}

void Edge::resize(const Vector2 & ptr1, const Vector2 & ptr2)
{
	e1 = ptr1;
	e2 = ptr2;
}

Vector2* Edge::intersect_line(const Vector2 & p, const Vector2 & dir)
{
	double bios = 0.00001;

	if (e1.x - e2.x <= bios && e1.x - e2.x >= -bios)
	{
		//parallel + 90 degree
		if (dir.x <= bios && dir.x >= -bios)
		{
			return nullptr;
		}
		//
		else {
			double ex1 = dir.y / dir.x*(e1.x - p.x) + p.y - e1.y;
			double ex2 = dir.y / dir.x*(e2.x - p.x) + p.y - e2.y;
			if (ex1 <= bios && ex1 >= -bios)
			{
				//intersect with e1
				Vector2* new_ePtr = new Vector2(e1.x, e1.y);
				new_ePtr->isEnd = true;
				return new_ePtr;
			}
			if (ex2 <= bios && ex2 >= -bios)
			{
				//intersect with e2
				Vector2* new_ePtr = new Vector2(e2.x, e2.y);
				new_ePtr->isEnd = true;
				return new_ePtr;
			}
			double y = dir.y / dir.x*(e1.x - p.x) + p.y;
			double lower_bound = (e1.y > e2.y) ? e2.y : e1.y;
			double upper_bound = (e1.y <= e2.y) ? e2.y : e1.y;
			if (y > upper_bound || y < lower_bound) return nullptr;
			Vector2* new_ePtr = new Vector2(e1.x, y);
			return new_ePtr;
		}
	}
	else {
		if (dir.x <= bios && dir.x >= -bios)
		{
			double y = (e1.y - e2.y) / (e1.x - e2.x)*(p.x - e1.x) + e1.y;
			double lower_bound = y - (e1.y > e2.y) ? e2.y : e1.y;
			double upper_bound = y - (e1.y <= e2.y) ? e2.y : e1.y;
			if (upper_bound <= bios && upper_bound >= -bios)
			{
				//intersect with upper
				Vector2* new_ePtr = new Vector2(p.x, y);
				new_ePtr->isEnd = true;
				return new_ePtr;
			}
			else if (lower_bound <= bios && lower_bound >= -bios)
			{
				//intersect with lower
				Vector2* new_ePtr = new Vector2(p.x, y);
				new_ePtr->isEnd = true;
				return new_ePtr;
			}
			if (upper_bound > 0 || lower_bound < 0) return nullptr;
			Vector2* new_ePtr = new Vector2(p.x, y);
			return new_ePtr;
		}
		else {
			double ex1 = dir.y / dir.x*(e1.x - p.x) + p.y - e1.y;
			double ex2 = dir.y / dir.x*(e2.x - p.x) + p.y - e2.y;
			if (ex1 <= bios && ex1 >= -bios)
			{
				//e1
				Vector2* new_ePtr = new Vector2(e1);
				new_ePtr->isEnd = true;
				return new_ePtr;
			}
			if (ex2 <= bios && ex2 >= -bios)
			{
				//e2
				Vector2* new_ePtr = new Vector2(e2);
				new_ePtr->isEnd = true;
				return new_ePtr;
			}
			double div = (e1.y - e2.y)*dir.x - (e1.x - e2.x)*dir.y;
			if (div <= bios && div >= -bios)
			{
				return nullptr;
			}
			double x = (p.y - e1.y)*(e1.x - e2.x)*dir.x + (e1.y - e2.y)*e1.x*dir.x - (e1.x - e2.x)*p.x*dir.y;
			x = x / div;
			double lower_bound = (e1.x > e2.x) ? e2.x : e1.x;
			double upper_bound = (e1.x <= e2.x) ? e2.x : e1.x;
			if (x >= upper_bound - bios || x <= lower_bound + bios) return nullptr;
			Vector2* new_ePtr = new Vector2(x, dir.y / dir.x*(x - p.x) + p.y);
			return new_ePtr;
		}

	}

}

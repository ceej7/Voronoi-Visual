#pragma once
class Vector2
{
public:
	double x;
	double y;
	bool isEnd;
	Vector2();
	Vector2(double _x, double _y);
	Vector2(const Vector2 &obj);
	Vector2 operator = (const Vector2& vec);
	void normalize();
};
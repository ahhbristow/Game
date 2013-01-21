#pragma once

class Plane
{
public:
	Plane(void);
	Plane(Vector, Vector, Vector);

	~Plane(void);
	Vector Normal();

private:
	Vector normal;
	double	constant;

	Vector p1, p2, p3;
};

#include "Vector.h"

Vector::Vector(void)
{
}

Vector::~Vector(void)
{
}

Vector::Vector(const SCALAR &a, const SCALAR &b, const SCALAR &c)
{
	x = a;
	y = b;
	z = c;
}

SCALAR Vector::Dot(Vector v) {
	SCALAR result;
	result = (this->x * v.x) + (this->y * v.y) + (this->z * v.z);

	return result;
}

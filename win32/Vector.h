#pragma once

class Vector
{
public:
	Vector(void);
	~Vector(void);


	Vector(const SCALAR &a, const SCALAR &b, const SCALAR &c);

	SCALAR Dot(Vector);

	SCALAR x, y, z;
};

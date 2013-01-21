#ifndef VECTOR_H
#define VECTOR_H


// Must always include this
//#include "Game.h"

typedef double SCALAR;

class Vector
{
public:
	Vector(void);
	~Vector(void);


	Vector(const SCALAR &a, const SCALAR &b, const SCALAR &c);

	SCALAR Dot(Vector);

	SCALAR x, y, z;
};

#endif
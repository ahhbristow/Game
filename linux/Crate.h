#ifndef CRATE_H
#define CRATE_H

// Must always include this
//#include "Game.h"

#include "Object.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

using namespace std;

class Vector;

class Crate: public Object {
public:
	Crate(void);
	Crate(Vector position, Vector velocity, Vector rotation);

	~Crate(void);

	
	void    Draw(int);
	int     Intersecting(SCALAR, SCALAR, SCALAR, SCALAR, SCALAR, SCALAR, SCALAR, SCALAR, SCALAR);
	int     intersecting;

private:
	

	//int a[] = {1, 1, 1};
};
#endif

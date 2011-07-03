#include "StdAfx.h"
#include "Plane.h"

Plane::Plane(void)
{
}

Plane::Plane(Vector p1, Vector p2, Vector p3) {
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;

	this->normal = this->Normal();
}

Plane::~Plane(void) {
}

Vector Plane::Normal() {
	
	Vector vector;


	return vector;
}




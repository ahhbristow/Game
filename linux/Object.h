#ifndef OBJECT_H
#define OBJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SDL.h"
#include <iostream>


// Must include this because Object has data member of type Vector
#include "Vector.h"

#define DRAG(V, C) (0.5*V*V*C)

/*
 *  Base class for objects.  Defines functions for physics calculations
 *
 */

class Object {
public:
	Object(void);
	Object(Vector position, Vector velocity, Vector rotation);
	~Object(void);


	void Update(double);
	void SetPosition(Vector position);
	void SetVelocity(Vector velocity);
	void SetMass(SCALAR mass);
	void SetModelview(SCALAR modelview[16]);

	GLdouble* GetModelview(void);
	
	Vector rotation;
	Vector velocity;
	Vector position;
	Vector acceleration;
	SCALAR mass;
	SCALAR drag_coefficient;
	GLdouble modelview[16];
	GLdouble *model;
	
private:
};
#endif

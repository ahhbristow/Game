#pragma once


/*
 *  Base class for objects.  Defines functions for physics calculations
 *
 */

class Object
{
public:
	Object(void);
	Object(Vector *position, Vector *velocity, Vector *rotation);
	~Object(void);


	void Update(double, int);
	void SetPosition(Vector *position);
	void SetVelocity(Vector *velocity);
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


};

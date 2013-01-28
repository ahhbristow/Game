#include "Object.h"



Object::Object(void)
{
}

Object::~Object(void)
{
}

Object::Object(Vector velocity, Vector position, Vector rotation) {
	
}

/*
 *  Calculate objects new position, velocity and acceleration based on current 
 *  position, velocity and acceleration
 */
void Object::Update(double time_elapsed)
{
	
	double distance_x, distance_y, distance_z;

	distance_x = velocity.x * time_elapsed;
	distance_y = velocity.y * time_elapsed;
	distance_z = velocity.z * time_elapsed;
	
	
	//calculate drag
	SCALAR drag_x = DRAG(velocity.x, this->drag_coefficient);
	SCALAR drag_y = DRAG(velocity.y, this->drag_coefficient);
	SCALAR drag_z = DRAG(velocity.z, this->drag_coefficient);

	acceleration.x = -drag_x/mass;
	acceleration.y = -drag_y/mass;
	acceleration.z = -drag_z/mass;

	//acceleration.y += 10.0f; //gravity;

	//gravity
	if (position.y <= 0.0f && velocity.y < 0) {
		velocity.y = 0.0f;
	} else {
		velocity.y -= 10.0f * time_elapsed;
	}

	

	//calculate new position
	position.x = position.x + distance_x;
	position.y = position.y + distance_y;
	position.z = position.z + distance_z;

	rotation.x += 1.0f;
	rotation.y += 1.0f;
	rotation.z += 1.0f;

}

void Object::SetPosition(Vector position)
{
	this->position = position;
}

void Object::SetVelocity(Vector velocity)
{
	this->velocity = velocity;
}

void Object::SetMass(SCALAR mass) {
	this->mass = mass;
}

GLdouble* Object::GetModelview() {
	return this->modelview;
}	

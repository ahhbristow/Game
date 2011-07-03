#include "stdafx.h"
#include "Ship.h"

Ship::Ship(void)
{
}

Ship::Ship(SCALAR direction, SCALAR xpos, SCALAR ypos)
{
	this->direction = direction;
	this->xpos = xpos;
	this->ypos = ypos;

	this->speed = 0.0f;
	this->acceleration = 0.0f;

}

Ship::~Ship(void)
{
}


void Ship::Initialise() {
	this->direction = 0.0f;
	this->speed = 0.0f;
	this->xpos = 0;
	this->ypos = 0;

	this->acceleration = 0.0f;
}


void Ship::Draw() {
	
	SCALAR x = this->xpos;
	SCALAR y = this->ypos;
	SCALAR dir = this->direction;
	
	glPushMatrix();
	
	glLoadIdentity();
	glTranslatef(x, y, 0.0f);
	glScalef(20.0f, 20.0f, 0.0f);
	glRotatef(dir, 0.0f, 0.0f, 1.0f);
	
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLES);
		
		glVertex2f(-1.0f, -1.0f);
		glVertex2f(1.0f, -1.0f);
		glVertex2f(0.0f, 2.0f);



	glEnd();

	if(this->speed > 0) {
		glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex2f(-1.0f, -1.0f);
			glVertex2f(1.0f, -1.0f);

			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex2f(1.0f, -1.5f);
			glVertex2f(-1.0f, -1.5f);
		glEnd();
	}

	glPopMatrix();
}


void Ship::SetPosition(SCALAR x, SCALAR y) {
	this->xpos = x;
	this->ypos = y;
}


void Ship::SetRotation(SCALAR theta) {
	this->direction = theta;
}

SCALAR Ship::GetRotation() {
	return this->direction;
}

void Ship::Thrust() {
	
	this->speed += acceleration;

	if(speed < 0) {
		speed = 0;
	}

	if(speed > 4) {
		speed = 2;
	}

	SCALAR currentX = this->xpos;
	SCALAR currentY = this->ypos;

	SCALAR newY = speed*cos(this->direction*PI/180);
	SCALAR newX = -1*speed*sin(this->direction*PI/180);

	this->SetPosition(currentX + newX, currentY + newY);

	if(this->xpos > 600) {
		this->xpos = 0;
	}

	if(this->xpos < 0) {
		this->xpos = 600;
	}

	if(this->ypos > 600) {
		this->ypos = 0;
	}

	if(this->ypos < 0) {
		this->ypos = 600;
	}

}


void Ship::CalcPosition(SCALAR xpos, SCALAR ypos, SCALAR heading, SCALAR speed) {
	
	

}



void Ship::SetAcceleration(SCALAR acceleration) {
	this->acceleration = acceleration;
}
#include "Crate.h"

Crate::Crate(void)
{
	
	this->drag_coefficient = 1.05f;
	this->mass = 10.0f; //kg
	this->rotation = *(new Vector(0, 0, 0));
	//this->intersecting = 0;
}


/*
 * Initialise this crate.  TODO: Move this into Object constructor
 */
Crate::Crate(Vector velocity, Vector position, Vector rotation)
{
	this->velocity = velocity;
	this->rotation = rotation;
	this->position = position;

	this->drag_coefficient = 1.05f;
	this->mass = 10.0f; //kg

    //Vector rotation(0,0,0);
	//this->rotation = *(new Vector(0, 0, 0));
    //this->rotation = rotation;

	this->intersecting = 0;
}

Crate::~Crate(void) {}


void Crate::Draw(int mouse_pressed) {
	glBindTexture(GL_TEXTURE_2D, 2);
	glGetDoublev(GL_MODELVIEW_MATRIX, this->modelview);
	glPushMatrix();

	// Translate to world co-ordinates
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(this->position.x, this->position.y, this->position.z);
	glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);

	if (this->intersecting == 1) {
		glColor3f(1.0f, 1.0f, 1.0f);	
	} else {
		glColor3f(0.5f, 0.5f, 0.5f);
	}

	glBegin(GL_QUADS);

		//front side
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);

		//back side
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);


		//left
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);

		//right
		glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);


		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);

		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, -1.0f, 1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);

	glEnd();
	glPopMatrix();
}


/*
 * Figure out if we've hit this object based on mouse world co-ordinates and near/far clipping plane co-ordinates
 */
int Crate::Intersecting(SCALAR x, SCALAR y, SCALAR z, SCALAR xFar, SCALAR yFar, SCALAR zFar, SCALAR objX, SCALAR objY, SCALAR objZ) {
	
	SCALAR xc, yc, zc, a, b, c, r, dx, dy, dz, mag;

	xc = position.x;
	yc = position.y;
	zc = position.z;

	//Calc ray using clipping coords (This one works)
	dx = xFar - x;
	dy = yFar - y;
	dz = zFar - z;

	mag = sqrt((dx * dx) + (dy * dy) + (dz * dz));

	dx = dx/mag;
	dy = dy/mag;
	dz = dz/mag;

	r = 1.5f;
	a = (dx*dx) + (dy*dy) + (dz*dz);
	b = (2*dx*(objX-xc)) + (2*dy*(objY-yc)) + (2*dz*(objZ-zc));
	c = (((objX-xc)*(objX-xc)) + ((objY-yc)*(objY-yc)) + ((objZ-zc)*(objZ-zc))) - (r*r);

	SCALAR dis;

	dis = (b*b) - (4*a*c);

	if (dis >= 0) {
		//this->intersecting = 1;
		return 1;
	} else {
		//this->intersecting = 0;
		return 0;
	}
}

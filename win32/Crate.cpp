#include "StdAfx.h"
#include "Crate.h"


Crate::Crate(void)
{
	
	this->drag_coefficient = 1.05f;
	this->mass = 10.0f; //kg
	this->rotation = *(new Vector(0, 0, 0));
	//this->intersecting = 0;
}

Crate::Crate(Vector *velocity, Vector *position, Vector *rotation)
{
	this->velocity = *velocity;
	this->rotation = *rotation;
	this->position = *position;

	this->drag_coefficient = 1.05f;
	this->mass = 10.0f; //kg
	this->rotation = *(new Vector(0, 0, 0));

	this->intersecting = 0;
}

Crate::~Crate(void)
{
}


void Crate::Draw(int mouse_pressed) 
{




	//==================================================
	glBindTexture(GL_TEXTURE_2D, 2);
	glGetDoublev(GL_MODELVIEW_MATRIX, this->modelview);
	glPushMatrix();
	//glScalef(0.001, 0.001, 0.001);

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

	
	//glBegin(GL_QUADS);

	//	//front side
	//	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	//	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	//	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	//	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);

	//	//back side
	//	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	//	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	//	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	//	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);


	//	//left
	//	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	//	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	//	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	//	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);

	//	//right
	//	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	//	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	//	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	//	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);


	//	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	//	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	//	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	//	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);

	//	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	//	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	//	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	//	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);



	//glEnd();

	glPopMatrix();

	glPushMatrix();
	glTranslatef(this->position.x, this->position.y, this->position.z);
	GLUquadricObj *quadratic;
	quadratic=gluNewQuadric();			// Create A Pointer To The Quadric Object ( NEW )
	gluQuadricNormals(quadratic, GLU_SMOOTH);	// Create Smooth Normals ( NEW )
	gluQuadricTexture(quadratic, GL_TRUE);		// Create Texture Coords ( NEW )
	gluSphere(quadratic,1.0f,32,32);
	glPopMatrix();

	//Draw a polygon so we can get a rough idea of where we're hitting
	//glBegin(GL_QUADS);
	//	//front side
	//	glVertex3f(position.x - 0.5f, position.y - 0.5f, position.z + 0.5f);
	//	glVertex3f(position.x + 0.5f, position.y - 0.5f, position.z + 0.5f);
	//	glVertex3f(position.x + 0.5f, position.y + 0.5f, position.z + 0.5f);
	//	glVertex3f(position.x - 0.5f, position.y + 0.5f, position.z + 0.5f);
	//glEnd();



}

int Crate::Intersecting(SCALAR x, SCALAR y, SCALAR z, SCALAR xFar, SCALAR yFar, SCALAR zFar, SCALAR objX, SCALAR objY, SCALAR objZ) {
	
	SCALAR xc, yc, zc;

	xc = position.x;
	yc = position.y;
	zc = position.z;

	SCALAR a, b, c, r, dx, dy, dz, mag;

	

	dx = objX;
	dy = objY;
	dz = objZ;

	mag = sqrt((dx * dx) + (dy * dy) + (dz * dz));

	dx = dx/mag;
	dy = dy/mag;
	dz = dz/mag;

	r = 1;
	a = (dx*dx) + (dy*dy) + (dz*dz);
	b = (2*dx*(objX-xc)) + (2*dy*(objY-yc)) + (2*dz*(objZ-zc));
	c = (((objX-xc)*(objX-xc)) + ((objY-yc)*(objY-yc)) + ((objZ-zc)*(objZ-zc))) - (r*r);

	SCALAR dis;

	dis = (b*b) - (4*a*c);

	if (this->intersecting != 1 && dis >= 0) {
		std::cout << "Intersecting!\n";
		this->intersecting = 1;
	} else if (this->intersecting == 1 && dis >= 0) {
		this->intersecting = 0;
	}

	
	return 0;
		
}
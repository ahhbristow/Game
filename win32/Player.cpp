#include "StdAfx.h"
#include "Player.h"

Player::Player(void)
{
}

Player::~Player(void)
{
}

void Player::Fire(int mouseX, int mouseY)
{

	POINT currentMouse;
	::GetCursorPos(&currentMouse);

	int x = currentMouse.x;
	int y = 800 - currentMouse.y;

	GLdouble nearX, nearY, nearZ, farX, farY, farZ;


	GLdouble	*model;
	GLdouble	projection[16];
	GLint		viewport[4];
	GLfloat	depth = 0;

		
	//get depth value
	glReadBuffer(GL_BACK);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4); 
	glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);

	model = gameController.glContext->GetModelviewMatrix();
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);


	gluUnProject(x, y, depth, model, projection, viewport, &nearX, &nearY, &nearZ);

	glColor3f(1.0f, 0.0f, 0.0f);

	glBindTexture(GL_TEXTURE_2D, 2);	
	glPushMatrix();
	//glScalef(0.001, 0.001, 0.001);

	glColor3f(0.0f, 1.0f, depth);
	glTranslatef(nearX, nearY, nearZ);

	glScalef(0.5f, 0.5f, 0.5f);

	glBegin(GL_QUADS);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
	glEnd();
	glPopMatrix();

	glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(nearX, nearY, nearZ);
	glEnd();
	//get ray

	//plane = ax + by + cz + d = 0


}

#ifndef GLCONTEXT_H
#define GLCONTEXT_H

#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SDL.h"

#include "GameController.h"

extern GameController gameController;

class Enemy;

typedef double SCALAR;

class GLContext {
public:

	SCALAR zoom;
	SCALAR xRot;
	SCALAR zRot;

	GLContext();
	~GLContext(void);

	void DrawScene(int, int, int);
	void increaseTheta();
	void setupGL();
	void setTheta(SCALAR);
	void loadTextures(const char *, int);

	void setXRotation(int);
	void setYRotation(int);
	
	void DrawSkybox();

	GLdouble * GetModelviewMatrix();

	

private:
	//GLuint textures[SLICES];//storage for different textures
	GLuint textures[100]; //storage for different textures

	int thetaX, thetaY;
	SCALAR rotateSpeed;

	GLfloat density;
	GLfloat fogColor[4];

	GLdouble model[16];

	

};
#endif
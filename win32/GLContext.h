#pragma once 

#define SLICES 109

class GLContext {
public:

	SCALAR zoom;
	SCALAR xRot;
	SCALAR zRot;

	GLContext(HWND);
	~GLContext(void);

	void setParent(HWND parent);
	HWND getParent();
	void setInstance(HINSTANCE hInstance);
	HINSTANCE getInstance();
	void DrawScene(int);
	void EnableGL();
	void DisableGL();
	void increaseTheta();
	void setupGL();
	void setVolume(Volume*);
	void setTheta(SCALAR);
	void loadTextures(const char *, int);

	void setXRotation(int);
	void setYRotation(int);
	
	void DrawSkybox();

	GLdouble * GetModelviewMatrix();

	

private:
	Volume* volume;
	GLuint textures[SLICES];//storage for different textures

	HWND parent;
	HINSTANCE hInstance;
	HDC hDC; //Device context for parent window
	HGLRC hRC;

	int thetaX, thetaY;
	SCALAR rotateSpeed;

	GLfloat density;
	GLfloat fogColor[4];

	GLdouble model[16];

	

};

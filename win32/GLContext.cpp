#include "stdafx.h"
#include "GLContext.h"

extern Ship *ship;
extern Crate *crate;

GLuint texture;			// This is a handle to our texture object
SDL_Surface *surface;	// This surface will tell us the details of the image
GLenum texture_format;
GLint  nOfColors;



//constructor
GLContext::GLContext(HWND parent)
{
	thetaX = 0;
	thetaY = 0;
	rotateSpeed = 1.5f;
	this->parent = parent;
	this->EnableGL();
	this->setupGL();

	density = 0.9f;
	zoom = 0.0f;
	xRot = 0.0f;
	zRot = 0.0f;

	fogColor[0] = 0.8f;
	fogColor[1] = 0.8f;
	fogColor[2] = 0.8f;
	fogColor[3] = 0.5f;

}

GLContext::~GLContext(void)
{
}

void GLContext::setupGL()
{
	glEnable(GL_TEXTURE_2D);

	//glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.5f,0.5f,0.5f,1.0f);					// We'll Clear To The Color Of The Fog
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations


	GLfloat LightAmbient[]=		{ 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat LightDiffuse[]=		{ 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat LightPosition[]=	{ 0.0f, 0.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		// Setup The Ambient Light
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);	// Position The Light
	//glEnable(GL_LIGHT1);								// Enable Light One

	glFogi(GL_FOG_MODE, GL_LINEAR);			// Fog Mode
	glFogfv(GL_FOG_COLOR, fogColor);					// Set Fog Color
	glFogf(GL_FOG_DENSITY, 0.3f);						// How Dense Will The Fog Be
	glHint(GL_FOG_HINT, GL_DONT_CARE);					// Fog Hint Value
	glFogf(GL_FOG_START, 1.0f);							// Fog Start Depth
	glFogf(GL_FOG_END, 7.0f);							// Fog End Depth
	//glEnable(GL_FOG);									// Enables GL_FOG



	glMatrixMode(GL_PROJECTION);
	//gluOrtho2D(0.0f, 600.0f, 600.0f, 0.0f);
	gluPerspective(45.0f, 1, 0.25f, 500000.0f);
	
}

/*
 * Create an OpenGL child window for the parent window
 */
void GLContext::EnableGL()
{
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    // get the device context (DC)
	hDC = GetDC( this->parent );

    // set the pixel format for the DC
    ZeroMemory( &pfd, sizeof( pfd ) );
    pfd.nSize = sizeof( pfd );
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
                  PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat( hDC, &pfd );
    SetPixelFormat( hDC, iFormat, &pfd );

    // create and enable the render context (RC)
    hRC = wglCreateContext( hDC );
    wglMakeCurrent( hDC, hRC );
}

void GLContext::DisableGL()
{
    wglMakeCurrent( NULL, NULL );
    wglDeleteContext( this->hRC );
    ReleaseDC( this->parent, this->hDC );
}


void GLContext::DrawSkybox() {

	glBindTexture( GL_TEXTURE_2D, 1 );

	glPushMatrix();
	glScalef(10000.0f, 6000.0f, 10000.0f);
	//glTranslatef(0.0f, -0.1f, 0.0f);
	//

	glBegin(GL_QUADS);

		glColor3f(1.0f, 1.0f, 1.0f);

		//draw ceiling
		glTexCoord2f(0.25f, 0.25f); glVertex3f(-1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.75f, 0.25f); glVertex3f(1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.75f, 0.75f); glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.25f, 0.75f); glVertex3f(-1.0f, 1.0f, 1.0f);

		//draw side walls
	
		glTexCoord2f(0.0f, 0.25f); glVertex3f(-1.0f, 0.0f, -1.0f);
		glTexCoord2f(0.25f, 0.25f); glVertex3f(-1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.25f, 0.75f); glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 0.75f); glVertex3f(-1.0f, 0.0f, 1.0f);

		glTexCoord2f(1.0f, 0.25f); glVertex3f(1.0f, 0.0f, -1.0f);
		glTexCoord2f(0.75f, 0.25f); glVertex3f(1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.75f, 0.75f); glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.75f); glVertex3f(1.0f, 0.0f, 1.0f);

		//draw end walls

		glTexCoord2f(0.25f, 0.0f); glVertex3f(-1.0f, 0.0f, -1.0f);
		glTexCoord2f(0.25f, 0.25f); glVertex3f(-1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.75f, 0.25f); glVertex3f(1.0f, 1.0f,-1.0f); 
		glTexCoord2f(0.75f, 0.0f); glVertex3f(1.0f, 0.0f, -1.0f);

		//glColor3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.25f, 1.0f); glVertex3f(-1.0f, 0.0f, 1.0f);
		glTexCoord2f(0.25f, 0.75f); glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.75f, 0.75f); glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.75f, 1.0f); glVertex3f(1.0f, 0.0f, 1.0f);

	glEnd();

	glPopMatrix();
}

void DrawFloor() {

	glBindTexture(GL_TEXTURE_2D, 2);
	glPushMatrix();
	glTranslatef(0.0f,-2.0f,0.0f);
	glScalef(10000.0f, 10000.0f, 10000.0f);
	
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);	
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 10000.0f); glVertex3f(-1.0f, 0.0f, -1.0f);
		glTexCoord2f(10000.0f, 10000.0f); glVertex3f(1.0f, 0.0f, -1.0f);
		glTexCoord2f(10000.0f, 0.0f); glVertex3f(1.0f, 0.0f, 1.0f);
	glEnd();
	glPopMatrix();

}

void GLContext::DrawScene(int mousePressed)
{

	Enemy *enemy = gameController.GetEnemy();
	
	vector<Crate>& crates = gameController.GetCrates();


	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
			
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glTranslatef(0.0f, -2.0f, 0.0f);
	glRotatef(zRot, 1.0f, 0.0f, 0.0f);
	glRotatef(xRot, 0.0f, 1.0f, 0.0f);

	DrawSkybox();
	
	//Draw world inside skybox
	DrawFloor();
	
	enemy->Draw();
	for(int i = 0; i < crates.size(); i++) {
		crates[i].Draw(mousePressed);
	}


	//Check crates for collisions
	
	POINT currentMouse;
	::GetCursorPos(&currentMouse);

	int x = currentMouse.x - 10;
	int y = (790 - currentMouse.y);

	GLdouble nearX, nearY, nearZ, farX, farY, farZ, objX, objY, objZ;

	GLdouble	projection[16];
	GLint		viewport[4];
	GLdouble    model[16];
	GLfloat	depth = 0;

		
	//get depth value
	glReadBuffer(GL_BACK);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4); 
	glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);

	glGetDoublev(GL_MODELVIEW_MATRIX, model);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);


	gluUnProject(x, y, 0.0f, model, projection, viewport, &nearX, &nearY, &nearZ);
	gluUnProject(x, y, 1.0f, model, projection, viewport, &farX, &farY, &farZ);
	gluUnProject(x, y, depth, model, projection, viewport, &objX, &objY, &objZ);
	
	if (mousePressed) {
		//Figure out if we've hit a crate
		for(int i = 0; i < crates.size(); i++) {
			crates[i].Intersecting(nearX, nearY, nearZ, farX, farY, farZ, objX, objY, objZ);
		}
	}

	glColor3f(1.0f, 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, 2);

	glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(objX, objY, objZ);
	glEnd();
	
	SwapBuffers( hDC );
}




void GLContext::increaseTheta()
{
	this->thetaY += 5;
	this->thetaY = this->thetaY % 360;
}

void GLContext::setVolume(Volume* volume)
{
	this->volume = volume;
}

void GLContext::setXRotation(int x) {
	this->thetaX = x;
}

void GLContext::setYRotation(int y) {
	this->thetaY = y;
}

void GLContext::setTheta(SCALAR theta)
{
	this->thetaY = (int)theta;
}

GLdouble* GLContext::GetModelviewMatrix() {
	return &(this->model[0]);
}

//create set of textures from volume data
void GLContext::loadTextures(const char * filename, int tex)
{

	 
	if ( (surface = SDL_LoadBMP(filename)) ) { 
	 
		// Check that the image's width is a power of 2
		if ( (surface->w & (surface->w - 1)) != 0 ) {
			printf("warning: image.bmp's width is not a power of 2\n");
		}
		
		// Also check if the height is a power of 2
		if ( (surface->h & (surface->h - 1)) != 0 ) {
			printf("warning: image.bmp's height is not a power of 2\n");
		}
	 
			// get the number of channels in the SDL surface
			nOfColors = surface->format->BytesPerPixel;
			if (nOfColors == 4)     // contains an alpha channel
			{
					if (surface->format->Rmask == 0x000000ff)
							texture_format = GL_RGBA;
					else
							texture_format = GL_BGRA;
			} else if (nOfColors == 3)     // no alpha channel
			{
					if (surface->format->Rmask == 0x000000ff)
							texture_format = GL_RGB;
					else
							texture_format = GL_BGR;
			} else {
					printf("warning: the image is not truecolor..  this will probably break\n");
					// this error should not go unhandled
			}
	        
		// Have OpenGL generate a texture object handle for us
		glGenTextures( tex, &texture );
	 
		// Bind the texture object
		glBindTexture( GL_TEXTURE_2D, texture );
	 
		// Set the texture's stretching properties
			//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
			//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
			glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
			glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	 



		//generate mip maps for loaded texture
		gluBuild2DMipmaps( GL_TEXTURE_2D, nOfColors, surface->w, surface->h, texture_format, GL_UNSIGNED_BYTE, surface->pixels );

		// Edit the texture object's image data using the information SDL_Surface gives us
		/*
		glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0,
		
						  texture_format, GL_UNSIGNED_BYTE, surface->pixels );

		glTexImage2D( GL_TEXTURE_2D, 1, nOfColors, surface->w, surface->h, 0,
						  texture_format, GL_UNSIGNED_BYTE, surface->pixels );*/
	} 
	else {
		printf("SDL could not load image.bmp: %s\n", SDL_GetError());
		SDL_Quit();
	}    
	 
	// Free the SDL_Surface only if it was successfully created
	if ( surface ) { 
		SDL_FreeSurface( surface );
	}

}

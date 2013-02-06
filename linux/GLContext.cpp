#include "GLContext.h"

using namespace std;

GLuint texture;			// This is a handle to our texture object
SDL_Surface *surface;	// This surface will tell us the details of the image
GLenum texture_format;
GLint  nOfColors;


//constructor
GLContext::GLContext()
{
	thetaX = 0;
	thetaY = 0;
	rotateSpeed = 1.5f;

	this->setupGL();
	glGenTextures( 10, &texture );
	
	this->loadTextures("textures/stormydays_large.bmp", 1);
	this->loadTextures("textures/crate.bmp", 2);
	this->loadTextures("textures/grass.bmp", 3);

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
	cout << "GLContext setup...\n";
	glEnable(GL_TEXTURE_2D);

	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
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
    glLoadIdentity();
	//gluOrtho2D(0.0f, 600.0f, 600.0f, 0.0f);
	gluPerspective(45.0f, 1.0f, 0.25f, 50.0f);
	
	cout << "GLContext setup complete.\n";
	
}



void GLContext::DrawSkybox() {

	glBindTexture( GL_TEXTURE_2D, 1 );

	//glPushMatrix();
	//glScalef(10000.0f, 6000.0f, 10000.0f);
	//glTranslatef(0.0f, -0.1f, 0.0f);
	//

    //glDisable(GL_DEPTH_TEST);
	glBegin(GL_QUADS);

		//glColor3f(1.0f, 0.0f, 1.0f);
        //glScalef(10.0f, 10.0f, 10.0f);


		// Draw far wall
        
        //bottom right
		glTexCoord2f(0.5f, 0.66f);
        glVertex3f(1.0f, -1.0f, -1.0f);
        //bottom left
		glTexCoord2f(0.25f, 0.66f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        //top left
		glTexCoord2f(0.25f, 0.33f);
        glVertex3f(-1.0f, 1.0f, -1.0f);
        //top right
        glTexCoord2f(0.5f, 0.33f);
        glVertex3f(1.0f, 1.0f, -1.0f);

        // Draw left wall
        //front top
		glTexCoord2f(0.25f, 0.33f);
        glVertex3f(-1.0f, 1.0f, -1.0f);
        //behind top
		glTexCoord2f(0.0f, 0.33f);
        glVertex3f(-1.0f, 1.0f, 1.0f);
        //behind bottom
		glTexCoord2f(0.0f, 0.66f);
        glVertex3f(-1.0f, -1.0f, 1.0f);
        //front bottom
        glTexCoord2f(0.25f, 0.66f);
        glVertex3f(-1.0f, -1.0f, -1.0f);

        // Draw right wall
        //front top
		glTexCoord2f(0.5f, 0.33f);
        glVertex3f(1.0f, 1.0f, -1.0f);
        //behind top
		glTexCoord2f(0.75f, 0.33f);
        glVertex3f(1.0f, 1.0f, 1.0f);
        //behind bottom
		glTexCoord2f(0.75f, 0.66f);
        glVertex3f(1.0f, -1.0f, 1.0f);
        //front bottom
        glTexCoord2f(0.5f, 0.66f);
        glVertex3f(1.0f, -1.0f, -1.0f);

	glEnd();
    //glEnable(GL_DEPTH_TEST);
    
    //glColor3f(1.0f, 1.0f, 1.0f);
	//glBegin(GL_QUADS);
	 //   glVertex3f(-0.005f, 0.005f, -0.26f);
	  //  glVertex3f(0.005f, 0.005f, -0.26f);
	 //   glVertex3f(0.005f, -0.005f, -0.26f);
	 //   glVertex3f(-0.005f, -0.005f, -0.26f);
	//glEnd();
}

void DrawFloor() {

	glBindTexture(GL_TEXTURE_2D, 2);
	//glPushMatrix();
	//glTranslatef(0.0f,-2.0f,0.0f);
	//glScalef(10000.0f, 10000.0f, 10000.0f);
	
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);	
	    glVertex3f(-1.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, 0.0f, -1.0f);
		glVertex3f(1.0f, 0.0f, -1.0f);
		glVertex3f(1.0f, 0.0f, 1.0f);
	glEnd();
	//glPopMatrix();

}

void DrawCursor() {
	
    glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
		glTexCoord2f(0.25f, 0.25f); glVertex3f(-0.005f, 0.005f, -0.26f);
		glTexCoord2f(0.75f, 0.25f); glVertex3f(0.005f, 0.005f, -0.26f);
		glTexCoord2f(0.75f, 0.75f); glVertex3f(0.005f, -0.005f, -0.26f);
		glTexCoord2f(0.25f, 0.75f); glVertex3f(-0.005f, -0.005f, -0.26f);
	glEnd();
	

}


/* Draw scene, passing in a list of objects to draw */
void GLContext::DrawScene(Player player, vector<Crate> crates) {
	
	//Enemy *enemy = game_controller.GetEnemy();

    // Get a reference to the list of crates
    // Don't get a copy because when you click on a crate it won't be modified.
    // Copy should work though because we're redrawing each time
	//vector<Crate> crates = game_controller.GetCrates();

 
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    //DrawCursor();
	
	// Transform world according to player orientation
	//Player player = game_controller.GetPlayer();
//	glTranslatef(0.0f, 0.0f, -10.0f);
    glRotatef(player.rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(player.rotation.y, 0.0f, 1.0f, 0.0f);

    //printf("DRAW: Player rotation: %lf,%lf,%lf\n", player.rotation.x, player.rotation.y, player.rotation.z);

	DrawSkybox();
    //DrawFloor();

	//enemy->Draw();
	for(int i = 0; i < crates.size(); i++) {
		//crates[i].Draw();
	}
	

	//Check crates for collisions
	//mouse_y = (800 - mouse_y);

	//GLdouble nearX, nearY, nearZ, farX, farY, farZ, objX, objY, objZ;

	//GLdouble    projection[16];
	//GLint       viewport[4];
	//GLdouble    model[16];
	//GLfloat     depth = 0;

		
	//get depth value
	//glReadBuffer(GL_BACK);
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 4); 
	//glReadPixels(mouse_x, mouse_y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);

	//glGetDoublev(GL_MODELVIEW_MATRIX, model);
	//glGetDoublev(GL_PROJECTION_MATRIX, projection);
	//glGetIntegerv(GL_VIEWPORT, viewport);


	//gluUnProject(mouse_x, mouse_y, 0.0f, model, projection, viewport, &nearX, &nearY, &nearZ);
	//gluUnProject(mouse_x, mouse_y, 1.0f, model, projection, viewport, &farX, &farY, &farZ);
	//gluUnProject(mouse_x, mouse_y, depth, model, projection, viewport, &objX, &objY, &objZ);
	
	// Check all objects for intersection.  TODO: Move this out of here.  This class should
	// just be used for rendering.
//	if (mousePressed) {
//		int intersecting = 0;
//		double nearest_z = -500000;
//		Crate nearest_crate;
//		int hit = 0;
//
//
//		//Figure out if we've hit a crate
//		for(int i = 0; i < crates.size(); i++) {
//			intersecting = crates[i].Intersecting(nearX, nearY, nearZ, farX, farY, farZ, objX, objY, objZ);
//			
//			//TODO: Fix segmentation fault here with pointer to nearest_crate
//			if (intersecting && crates[i].position.z > nearest_z) {
//				nearest_z = crates[i].position.z;
//				nearest_crate = crates[i];
//				hit = 1;
//				//crates[i].intersecting = 1;
//			}
//		}
//		
//		// Only set to intersecting if we've actually hit something
//        // We need a reference to the crate so we actually write back
//        // to the crate list, and not to a copy of it
//		if (hit == 1) {
//			nearest_crate.intersecting = 1;
//		}
//	}

	SDL_GL_SwapBuffers( );
}


void GLContext::increaseTheta()
{
	this->thetaY += 5;
	this->thetaY = this->thetaY % 360;
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
void GLContext::loadTextures(const char * filename, int tex) {
	 
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
		// Bind the texture object
		glBindTexture( GL_TEXTURE_2D, tex );
		// Set the texture's stretching properties
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		//generate mip maps for loaded texture
		gluBuild2DMipmaps( GL_TEXTURE_2D, nOfColors, surface->w, surface->h, texture_format, GL_UNSIGNED_BYTE, surface->pixels );
	} 
	else {
		printf("SDL could not load image.bmp: %s\n", SDL_GetError());
		SDL_Quit();
	}    
	 
	// Free the SDL_Surface only if it was successfully created
	if ( surface ) { 
		SDL_FreeSurface( surface );
	}
	cout << "Complete!\n";
}

/*
 * TODO: Move into GLContext class
 */
double* GLContext::GetObjectCoordinates(int mouse_x, int mouse_y) {
    
	//Check crates for collisions
	mouse_y = (800 - mouse_y);

	GLdouble nearX, nearY, nearZ, farX, farY, farZ, objX, objY, objZ;

	GLdouble    projection[16];
	GLint       viewport[4];
	GLdouble    model[16];
	GLfloat     depth = 0;

		
	//get depth value
	glReadBuffer(GL_BACK);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4); 
	glReadPixels(mouse_x, mouse_y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);

	glGetDoublev(GL_MODELVIEW_MATRIX, model);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);

    /* This is OpenGL specific.  Move this into a function in a different class */
	gluUnProject(mouse_x, mouse_y, 0.0f, model, projection, viewport, &nearX, &nearY, &nearZ);
	gluUnProject(mouse_x, mouse_y, 1.0f, model, projection, viewport, &farX, &farY, &farZ);
	gluUnProject(mouse_x, mouse_y, depth, model, projection, viewport, &objX, &objY, &objZ);

    double* object_coordinates;

    object_coordinates [0] = nearX;
    object_coordinates [1] = nearY;
    object_coordinates [2] = nearZ;

    object_coordinates [3] = farX;
    object_coordinates [4] = farY;
    object_coordinates [5] = farZ;

    object_coordinates [6] = objX;
    object_coordinates [7] = objY;
    object_coordinates [8] = objZ;


}

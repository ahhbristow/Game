#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SDL.h"

#include "Game.h"

GameController gameController;

const int FRAMES_PER_SECOND = 50;
const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;


// Forward declarations
void CreateInterface();
void handleKeyPress(SDL_keysym*);

/*
 *  Main procedure.  Creates game controller, user interface and OpenGL context.
 */
int main(int argc, char *argv[]) {

	// Create window
	CreateInterface();
	
	//Create OpenGL Context
	
	
	
	return 0;

}

void Quit( int returnCode )
{
    /* clean up the window */
    SDL_Quit( );

    /* and exit appropriately */
    exit( returnCode );
}

void CreateInterface () {

  SDL_Surface *surface;
  
      /* Flags to pass to SDL_SetVideoMode */
    int videoFlags;
    /* main loop variable */
    int done = 0;
    /* used to collect events */
    SDL_Event event;
    /* this holds some info about our display */
    const SDL_VideoInfo *videoInfo;
    /* whether or not the window is active */
    int isActive = 1;

  if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
    fprintf( stderr, "Video initialization failed: %s\n",
             SDL_GetError( ) );
    //Quit( 1 );
    return;
  }

  /* Fetch the video info */
  videoInfo = SDL_GetVideoInfo( );

  if ( !videoInfo ) {
    fprintf( stderr, "Video query failed: %s\n",
             SDL_GetError( ) );
    //Quit( 1 );
    return;
  }
    
  videoFlags  = SDL_OPENGL;          /* Enable OpenGL in SDL */
  videoFlags |= SDL_GL_DOUBLEBUFFER; /* Enable double buffering */
  videoFlags |= SDL_HWPALETTE;       /* Store the palette in hardware */
  videoFlags |= SDL_RESIZABLE;       /* Enable window resizing */

  /* This checks to see if surfaces can be stored in memory */
  if ( videoInfo->hw_available )
	videoFlags |= SDL_HWSURFACE;
    else
	videoFlags |= SDL_SWSURFACE;

    /* This checks if hardware blits can be done */
    if ( videoInfo->blit_hw )
	videoFlags |= SDL_HWACCEL;

    /* Sets up OpenGL double buffering */
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    /* get a SDL surface */
    surface = SDL_SetVideoMode( 1000, 800, 16,
				videoFlags );

    /* Verify there is a surface */
    if ( !surface )
	{
	    fprintf( stderr,  "Video mode set failed: %s\n", SDL_GetError( ) );
	    //Quit( 1 );
	    return;
	}
	    
       
	// Create GL Context
	GLContext g;
	
	int next_game_tick;
	double time_elapsed;
	next_game_tick = SDL_GetTicks();
	int mouse_pressed;
	int mouse_x = 0;
	int mouse_y = 0;
	
	Player& player = gameController.GetPlayer();
	SDL_ShowCursor(SDL_DISABLE);
 
    /* wait for events */         
 	while ( !done ) {
		
		mouse_pressed = 0;
		
		int sleep_time = 0;
		next_game_tick += SKIP_TICKS;
		sleep_time = next_game_tick - SDL_GetTicks();

		if( sleep_time >= 0 ) {
			//cout << "Sleep time: " << sleep_time << "\n";
			usleep( sleep_time * 1000 );
		} else {
			// Shit, we are running behind!
		}
		
		time_elapsed = sleep_time / 1000.0f;
		//cout << "Time elapsed: " << time_elapsed << "\n";
		
		
		//get mouse position
		SDL_GetMouseState(&mouse_x, &mouse_y);
		
            /* handle the events in the queue */
		while ( SDL_PollEvent( &event ) ) {
			switch( event.type ) {
				case SDL_ACTIVEEVENT:
					/* Something's happend with our focus
					 * If we lost focus or we are iconified, we
					 * shouldn't draw the screen
					 */
					if ( event.active.gain == 0 )
						isActive = 1;
					else
						isActive = 0;
					break;
				case SDL_VIDEORESIZE:
					/* handle resize event */
					surface = SDL_SetVideoMode( event.resize.w,
												event.resize.h,
												16, videoFlags );
					if ( !surface )
					{
						fprintf( stderr, "Could not get a surface after resize: %s\n", SDL_GetError( ) );
						Quit( 1 );
					}
					//resizeWindow( event.resize.w, event.resize.h );
					break;
				case SDL_KEYDOWN:
					/* handle key presses */
					handleKeyPress( &event.key.keysym );
					break;
				case SDL_MOUSEBUTTONDOWN:
					printf("Mouse button %d pressed at (%d,%d)\n",event.button.button, event.button.x, event.button.y);
					mouse_pressed = 1;
					//mouse_x = event.button.x;
					//mouse_y = event.button.y;
					break;
				case SDL_MOUSEMOTION:
					printf("Mouse moved by %d,%d to (%d,%d)\n", 
					    event.motion.xrel, event.motion.yrel,
					    event.motion.x, event.motion.y);
					
						//player.rotation.y -= (event.motion.xrel);
						//player.rotation.x -= (event.motion.yrel);
						//SDL_WarpMouse(500,400);
					
					break;
				case SDL_QUIT:
					/* handle quit requests */
					done = 1;
					break;
				default:
					break;
			}
		}
		gameController.UpdateObjects(mouse_pressed, time_elapsed);
		g.DrawScene(mouse_pressed, mouse_x, mouse_y);

	}

	/* clean ourselves up and exit */
	Quit( 0 );
	
	/* Should never get here */
	return;
    
}

void handleKeyPress(SDL_keysym* key) {
	
	Player& player = gameController.GetPlayer();
	
	switch (key->sym) {
		case SDLK_LEFT:
			player.rotation.y -= 5.0f;
			break;
		case SDLK_RIGHT:
			player.rotation.y += 5.0f;
			break;
		case SDLK_UP:
			player.velocity.z = -5.0f;
			break;
		case SDLK_DOWN:
			player.velocity.z = 5.0f;
			break;
	}
}
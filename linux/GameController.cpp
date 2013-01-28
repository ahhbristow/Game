#include "GameController.h"


/*****************************************
 * Constructors
 */
GameController::~GameController(void) {}

GameController::GameController(GLContext gl_context) {
	
    this->gl_context = gl_context;

	Crate crate;
	
	Vector position(0.0f, 0.0f, -50.0f);
	Vector velocity(-1.0f, 10.0f, 15.0f);

	// Why does crate only store a reference to a velocity?
	// Probably should be a copy as the local Vector
	// will be destroyed
	crate.SetPosition(position);
	crate.SetVelocity(velocity);

	//AddCrate(crate);

    // Initial crate throw
    Crate enemy_crate = en.ThrowObject();
	this->AddCrate(en.ThrowObject());

}


/*****************************************
 * Public functions
 */

/*
 * Generic function to handle a mouse click
 */
void GameController::LeftMouseClicked(int mouse_x, int mouse_y) {
    this->CheckObjectsForSelection(mouse_x, mouse_y);
}

void GameController::AddObject(Object object) {}

/*
 * Getters and setters
 */

Enemy* GameController::GetEnemy() {
	return &en;
}

Player GameController::GetPlayer() {
	return player;
}

vector<Crate> GameController::GetCrates() {
	return crates;
}

/*****************************************
 * Private functions
 */


/*
 * Adds a crate to the game world
 *
 */
void GameController::AddCrate(Crate cr) {
	this->crates.push_back(cr);
}

/*
 * This is the main game loop.  All logic should go in here.
 */
void GameController::UpdateObjects(double time_elapsed) {

	time_t current_time = time(NULL);
	last_time = current_time;

	
	//aiming code
	int mouse_x, mouse_y;
	SDL_GetMouseState(&mouse_x, &mouse_y);
	int xrel = 500 - mouse_x;
	int yrel = 400 - mouse_y;
	
	player.rotation.y -= (xrel * 0.1f);
	player.rotation.x -= (yrel * 0.1f);
	SDL_WarpMouse(500,400);
	
	// Update the enemy object
	en.Update(time_elapsed);
	player.Update(time_elapsed, 0);
	

	time_remaining -= time_elapsed;
	if (time_remaining <= 0) {
		//this->AddCrate(en.ThrowObject());
		time_remaining = 1;
		
		frame_rate = frames / 2;
		frames = 0;
		std::cout << "Frame rate\n: " << frame_rate << "\n";
	}

	// Update all objects in object array
	for(unsigned int i = 0; i < crates.size(); i++) {
		crates[i].Update(time_elapsed);
	}
	
	frames++;
}


/*
 * Loops through the object list and check if
 * that object has been selected with the mouse.
 *
 *
 * Algorithm:
 * 
 * 1) Get 
 *
 *
 *
 *
 *
 */
void GameController::CheckObjectsForSelection(int mouse_x, int mouse_y) {

    int    intersecting, hit;
    double nearest_z;
    Crate  nearest_crate;

    intersecting = 0;
	hit          = 0;
	nearest_z    = -500000;


    // Transform mouse co-ordinates to object space.
    // The intersection comparison should be done in
    // object space
    double* object_coordinates = gl_context.GetObjectCoordinates(mouse_x, mouse_y);

    double nearX, nearY, nearZ, farX, farY, farZ, objX, objY, objZ;
    nearX = object_coordinates[0];
    nearY = object_coordinates[1];
    nearZ = object_coordinates[2];
    farX = object_coordinates[3];
    farY = object_coordinates[4];
    farZ = object_coordinates[5];
    objX = object_coordinates[6];
    objY = object_coordinates[7];
    objZ = object_coordinates[8];

	//Figure out if we've hit a crate
	for(int i = 0; i < crates.size(); i++) {
		intersecting = crates[i].Intersecting(nearX, nearY, nearZ, farX, farY, farZ, objX, objY, objZ);
			
		//TODO: Fix segmentation fault here with pointer to nearest_crate
		if (intersecting && crates[i].position.z > nearest_z) {
			nearest_z = crates[i].position.z;
			nearest_crate = crates[i];
			hit = 1;
			//crates[i].intersecting = 1;
		}
	}
		
	// Only set to intersecting if we've actually hit something
    // We need a reference to the crate so we actually write back
    // to the crate list, and not to a copy of it
    if (hit == 1) {
    	nearest_crate.intersecting = 1;
	}
}


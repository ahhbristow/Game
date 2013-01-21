#include "GameController.h"

GameController::~GameController(void) {
;
}

GameController::GameController() {
	
	Crate crate;
	
	Vector position(0.0f, 0.0f, -50.0f);
	Vector velocity(-1.0f, 10.0f, 15.0f);

	// Why does crate only store a reference to a velocity?
	// Probably should be a copy as the local Vector
	// will be destroyed
	crate.SetPosition(position);
	crate.SetVelocity(velocity);


	//AddCrate(crate);
}

void GameController::AddObject(Object object) {}







/*
 * Adds a crate to the game world
 *
 */
void GameController::AddCrate(Crate &cr) {
	this->crates.push_back(cr);
}

/*
 * This is the main game loop.  All logic should go in here.
 */
void GameController::UpdateObjects(int mousePressed, double time_elapsed) {

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
	
// 	cout << "Player velocity: " << player.velocity.x;
// 	cout << ", " << player.velocity.y;
// 	cout << ", " << player.velocity.z << "\n";
// 	cout << "Player position: " << player.position.x;
// 	cout << ", " << player.position.y;
// 	cout << ", " << player.position.z << "\n";
// 	cout << "Player rotation: " << player.rotation.x;
// 	cout << ", " << player.rotation.y;
// 	cout << ", " << player.rotation.z << "\n";
	
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
		crates[i].Update(time_elapsed, mousePressed);
	}
	
	frames++;
}

Enemy* GameController::GetEnemy() {
	return &en;
}

Player& GameController::GetPlayer() {
	return player;
}

vector<Crate>& GameController::GetCrates() {
	return crates;
}


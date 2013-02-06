#include "Player.h"

Player::Player(void) {
	this->position = Vector(0, 0, 0);
	this->rotation = Vector(0, 0, 0);
	this->velocity = Vector(0, 0, 0);
    
}

Player::~Player(void) {}

void Player::Fire(int mouseX, int mouseY) {}


// Override from Object
void Player::Update(double time_elapsed, int mouse_pressed) {
	double distance_x, distance_y, distance_z;

	distance_x = velocity.x * time_elapsed;
	distance_y = velocity.y * time_elapsed;
	distance_z = velocity.z * time_elapsed;

	//calculate drag
	SCALAR drag_x = DRAG(velocity.x, this->drag_coefficient);
	SCALAR drag_y = DRAG(velocity.y, this->drag_coefficient);
	SCALAR drag_z = DRAG(velocity.z, this->drag_coefficient);

	acceleration.x = -drag_x/mass;
	acceleration.y = -drag_y/mass;
	acceleration.z = -drag_z/mass;

	//calculate new position
	position.x = position.x + distance_x;
	position.y = position.y + distance_y;
	position.z = position.z + distance_z;
}

void Player::LookMove(int x, int y) {
    this->rotation.x += (y * 0.1f);
    this->rotation.y += (x * 0.1f);
//    SDL_WarpCursor(500,400);
}

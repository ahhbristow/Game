#include "StdAfx.h"
#include "GameController.h"

GameController::~GameController(void) {

}

void GameController::AddObject(Object object) {
	
}

void GameController::AddCrate(Crate cr) {
	this->crates.push_back(cr);
}

void GameController::UpdateObjects(int mousePressed) {

	time_t current_time = time(NULL);
	time_t time_passed = current_time - last_time;
	last_time = current_time;

	en.Update(time_passed);

	//update all objects in object array
	for(int i = 0; i < crates.size(); i++) {
		crates[i].Update(time_passed, mousePressed);
	}
	
	

	glContext->DrawScene(mousePressed);
}

void GameController::SetGLContext(GLContext* glContext) {
	this->glContext = glContext;
}	

Enemy* GameController::GetEnemy() {
	return &en;
}

Player* GameController::GetPlayer() {
	return &player;
}

vector<Crate>& GameController::GetCrates() {
	return crates;
}


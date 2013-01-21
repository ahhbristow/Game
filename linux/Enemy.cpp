#include "Enemy.h"

Enemy::Enemy() {

	//set enemy position to 30 metres away
	this->position = Vector(0, 0, -50.0f);
	this->ThrowObject();
}

Enemy::~Enemy(void) {}

double Enemy::ChooseTime() {
	//choose random time
	return 0;
}

void Enemy::Update(time_t time_passed) {}




Crate& Enemy::ThrowObject() {
	
	Crate crate;

	Vector position(0.0f, 0.0f, -50.0f);
	Vector velocity(-1.0f, 10.0f, 15.0f);

	//crate.SetPosition(&Vector(0.0f, 0.0f, -50.0f));
	//crate.SetVelocity(&Vector(-1.0f, 10.0f, 15.0f));
	
	crate.SetPosition(position);
	crate.SetVelocity(velocity);


	return crate;
}

void Enemy::Draw() {
	glBindTexture(GL_TEXTURE_2D, 2);
	glPushMatrix();
	

	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(this->position.x, this->position.y, this->position.z);
	glScalef(5.0f, 5.0f, 5.0f); //set object to 10 metres high and wide
	
	glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);

	
	glBegin(GL_QUADS);

		//front side
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);


	glEnd();
	glPopMatrix();
}

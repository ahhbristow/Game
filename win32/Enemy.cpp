#include "StdAfx.h"
#include "Enemy.h"




Enemy::Enemy(void)
{
}

Enemy::Enemy(GameController *gc) {
	this->gc = gc;

	//set enemy position to 30 metres away
	this->position = Vector(0, 0, -50.0f);
	this->ThrowObject();
}

Enemy::~Enemy(void)
{
}

double Enemy::ChooseTime() {
	//choose random time
	return 0;
}

void Enemy::Update(time_t time_passed) {

	time_remaining -= time_passed;

	if (time_remaining <= 0) {
		this->ThrowObject();
		time_remaining = 2;
	}

}

void Enemy::ThrowObject() {
	
	Crate crate1, crate2, crate3;
	crate1.SetPosition(&Vector(0.0f, 0.0f, -50.0f));
	crate1.SetVelocity(&Vector(0.0f, 0.1f, 0.25f));

	//crate2.SetPosition(&Vector(-4.0f, 10.0f, -30.0f));
	//crate2.SetVelocity(&Vector(0.0f, 0.0f, 0.0f));

	//crate3.SetPosition(&Vector(4.0f, 10.0f, 40.0f));
	//crate3.SetVelocity(&Vector(0.0f, 0.0f, 0.0f));
	
	gameController.AddCrate(crate1);
	//gameController.AddCrate(crate2);
	//gameController.AddCrate(crate3);
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

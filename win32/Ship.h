#pragma once

class Ship
{
public:
	Ship(void);
	Ship(SCALAR, SCALAR, SCALAR);
	~Ship(void);


	void Draw();
	void Initialise();

	void SetPosition(SCALAR, SCALAR);
	void SetRotation(SCALAR theta);
	SCALAR GetRotation();

	void Thrust();
	void CalcPosition(SCALAR, SCALAR, SCALAR, SCALAR);
	void SetAcceleration(SCALAR);

private:

	SCALAR xpos, ypos;
	SCALAR speed;
	SCALAR acceleration;
	SCALAR mass;
	SCALAR direction;
	

};

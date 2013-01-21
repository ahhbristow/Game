#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"

class Player: public Object
{

private: 
	int health;

public:
	Player(void);
	~Player(void);

	void Fire(int, int);
	void Update(double, int);
};
#endif
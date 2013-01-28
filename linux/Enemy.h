#ifndef ENEMY_H
#define ENEMY_H

// Must include this because Enemy extends Object
#include "Object.h"
#include "Vector.h"
#include "Crate.h"

class GameController;


class Enemy: public Object {
public:
	Enemy();
	~Enemy(void);
	double ChooseTime();
	void Draw();
	void Update(time_t);
	Crate ThrowObject();

private:
	
};

#endif

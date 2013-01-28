#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "Object.h"
#include "Crate.h"
#include "Enemy.h"
#include "Player.h"
#include "GLContext.h"


#include <vector>


using namespace std;

class GameController {

public:


	GameController(GLContext gl_context);
	~GameController(void);
	
	void           AddObject(Object);
	void           AddCrate(Crate);
	void           UpdateObjects(double);

	Player         GetPlayer();
	Enemy*         GetEnemy();
	vector<Crate>  GetCrates();

    void LeftMouseClicked(int, int);


private:

	//game state variables
	bool		game_finished;
	time_t		last_time;
	vector<Crate> crates;

    GLContext gl_context;

	//game objects
	Enemy		en;
	Player		player;
	Crate		crate;
	
	double time_remaining;
	double frame_rate;
	int frames;

    /* Check all the world objects for mouse selection */
    void           CheckObjectsForSelection(int, int);

};

#endif

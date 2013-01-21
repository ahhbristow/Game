#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

// Must include this because GameController has a data member of type Crate
#include "Object.h"
#include "Crate.h"
#include "Enemy.h"
#include "Player.h"


#include <vector>


using namespace std;

class GameController
{
public:


	GameController(void);
	~GameController(void);
	
	void			AddObject(Object);
	void			AddCrate(Crate &);
	void			UpdateObjects(int, double);

	Player&         GetPlayer();
	Enemy*          GetEnemy();
	vector<Crate>&  GetCrates();

private:

	//game state variables
	bool		game_finished;
	time_t		last_time;
	vector<Crate> crates;

	//game objects
	Enemy		en;
	Player		player;
	Crate		crate;
	
	double time_remaining;
	double frame_rate;
	int frames;

	//rendering context;
};

#endif

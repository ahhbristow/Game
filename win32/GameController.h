#pragma once

class GameController
{
public:


	GameController(void) : crate(&Vector(0,0,0), &Vector(0,0,0), &Vector(0,0,0)), en(this) {
	};

	~GameController(void);
	
	void			AddObject(Object);
	void			AddCrate(Crate);
	void			UpdateObjects(int);
	void			SetGLContext(GLContext*);
	

	Player*			GetPlayer();
	Enemy*			GetEnemy();
	vector<Crate>&	GetCrates();

	GLContext	*glContext;
private:

	//game state variables
	bool		game_finished;
	time_t		last_time;
	vector<Crate> crates;

	//game objects
	Enemy		en;
	Player		player;
	Crate		crate;

	//rendering context;
	
	
	
	


	

};

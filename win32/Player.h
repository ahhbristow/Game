#pragma once

class Player
{

private: 
	int health;

public:
	Player(void);
	~Player(void);

	void Fire(int, int);
};

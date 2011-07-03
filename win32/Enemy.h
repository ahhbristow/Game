#pragma once

class Enemy: public Object
{
public:
	Enemy(void);
	~Enemy(void);
	Enemy(GameController*);
	double ChooseTime();
	void Draw();
	void Update(time_t);
	void ThrowObject();

private:
	double time_remaining;
	GameController *gc;
};

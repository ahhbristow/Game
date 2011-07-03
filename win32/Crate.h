#pragma once

class Crate: public Object
{
public:
	Crate(void);
	Crate(Vector *position, Vector *velocity, Vector *rotation);

	~Crate(void);

	
	void	Draw(int);
	int		Intersecting(SCALAR, SCALAR, SCALAR, SCALAR, SCALAR, SCALAR, SCALAR, SCALAR, SCALAR);	
private:
	int intersecting;

	//int a[] = {1, 1, 1};
};

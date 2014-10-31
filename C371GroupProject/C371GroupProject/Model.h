#pragma once
class Model
{
public:
	Model(void);
	~Model(void);
	void draw();
	void idle();
	void moveTo();

	enum State
	{
		Idle,
		Moving,
		Dying,
	};


private:
	double x,y,z;
	State currentState;

	//model variable however it's done

	bool lightAvailability[4]; // true if that light available, false otherwise -- if needed
};


#ifndef C_VECTOR_2D_TEST
#define C_VECTOR_2D_TEST
#include "Vector2D.h"
class Vector2DTest {
public: 
	//Default constructor
	Vector2DTest() {};

	int runTests();


private: //Functions
	int testReflectLeft();
	int testReflectRight();
	int testReflectDown();
	int testReflectUp();
	int testClampSpeed();
	int testClampPositionTopLeft();
	int testClampPositionBottomRight();

	bool isVeryCloseTo(float value, float target);

private://Data
};

#endif
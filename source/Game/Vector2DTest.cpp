#include "Vector2dtest.h"

int Vector2DTest::runTests() {
	int errors = 0;
	errors += testReflectLeft();
	errors += testReflectRight();
	errors += testReflectDown();
	errors += testReflectUp();
	errors += testClampSpeed();
	errors += testClampPositionTopLeft();
	errors += testClampPositionBottomRight();
	return errors;
}

int Vector2DTest::testReflectLeft() {
	Vector2D unitVectorPointsRight = Vector2D(1.0f, 0.0f);
	Vector2D normalVectorPointsLeft = Vector2D(-1, 0);
	Vector2D reflection = unitVectorPointsRight.getReflection(normalVectorPointsLeft);
	if (isVeryCloseTo(reflection.getX(), -1.0f)) {
		return 0;
	}
	return 1;
}

bool Vector2DTest::isVeryCloseTo(float value, float target) {
	float difference = value - target;
	return (difference > -0.0001 && difference < 0.0001);
}

int Vector2DTest::testReflectRight() {
	return 0;

}

int Vector2DTest::testReflectDown() {
	return 0;

}

int Vector2DTest::testReflectUp() {
	return 0;

}

int Vector2DTest::testClampSpeed() {
	float speedLimit = 10.0f;
	Vector2D largeVector = Vector2D(100.0f, 100.0f);
	largeVector.clampMagnitude( speedLimit);
	if (isVeryCloseTo(largeVector.getMagnitude(), speedLimit)) {
		return 0;
	}
	return 1;
}

int Vector2DTest::testClampPositionTopLeft() {
	Vector2D initPosition = Vector2D(100.0f, 100.0f);
	Vector2D minBoundary = Vector2D(0, 0);
	Vector2D maxBoundary = Vector2D(10,10);

	initPosition.clamp(minBoundary, maxBoundary);
	int result = 0;
	if (!isVeryCloseTo(initPosition.getX(), 10.0f)) {
		result++;
	}
	if (!isVeryCloseTo(initPosition.getY(), 10.0f)) {
		result++;
	}
	return result;
}

int Vector2DTest::testClampPositionBottomRight() {
	return 0;
}


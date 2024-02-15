#include "CartesianCoordinate.h"
#include "../MathUtils.h"
#include "SDL/SDL.h"

//Constructor
CartesianCoordinate::CartesianCoordinate(
	int x, 
	int y
) {
	this->x = x;
	this->y = y;
}

CartesianCoordinate::CartesianCoordinate() {
	this->x = 0;
	this->y = 0;
}

CartesianCoordinate CartesianCoordinate::operator+(const CartesianCoordinate& other) const {
	return CartesianCoordinate(this->x + other.x, this->y + other.y);
}

CartesianCoordinate CartesianCoordinate::operator*(const CartesianCoordinate& other) const {
	return CartesianCoordinate(this->x * other.x, this->y * other.y);
}

CartesianCoordinate operator*(float scalar, const CartesianCoordinate& vector) {
	return vector * scalar;
}

CartesianCoordinate CartesianCoordinate::operator*(const float scalar) const {
	return CartesianCoordinate(x * scalar, y * scalar);
}

CartesianCoordinate CartesianCoordinate::operator-(const CartesianCoordinate& other) const {
	return CartesianCoordinate(this->x - other.x, this->y - other.y);
}

unsigned int CartesianCoordinate::manhattanDistance(const CartesianCoordinate& destination) const {
	CartesianCoordinate distanceVector = (destination - (*this)).abs();
	return distanceVector.x + distanceVector.y;
}

unsigned int CartesianCoordinate::rectilinearDistance(const CartesianCoordinate& destination) const {
	return manhattanDistance(destination);
}

CartesianCoordinate CartesianCoordinate::abs() const {
	return CartesianCoordinate(std::abs(x), std::abs(y));
}

void CartesianCoordinate::clamp(const CartesianCoordinate& minimum, const CartesianCoordinate& maximum) {
	CartesianCoordinate deltaVector = vectorToBounds(minimum, maximum);
	x = x + deltaVector.x;
	y = y + deltaVector.y;
}

CartesianCoordinate& CartesianCoordinate::operator=(const CartesianCoordinate& other) {
	if (this != &other) {
		this->x = other.x;
		this->y = other.y;
	}
	return *this;
}

CartesianCoordinate CartesianCoordinate::vectorToBounds(const CartesianCoordinate& minimum, const CartesianCoordinate& maximum) const {
	float deltaX = 0.0f;
	float deltaY = 0.0f;

	if (x > maximum.x) {
		deltaX = maximum.x - x;
	}

	if (y > maximum.y) {
		deltaY = maximum.y - y;
	}

	if (x < minimum.x) {
		deltaX = minimum.x - x;
	}

	if (y < minimum.y) {
		deltaY = minimum.y - y;
	}

	if (minimum.x > maximum.x ) {
		deltaX = 0;
	}
	if (minimum.y > maximum.y ) {
		deltaY = 0;
	}

	return CartesianCoordinate(deltaX, deltaY);
}

CartesianCoordinate CartesianCoordinate::getAxisAligned() const {
	int xAxis = 0, yAxis = 0;
	CartesianCoordinate min = CartesianCoordinate(-1, -1);
	CartesianCoordinate max = CartesianCoordinate(1, 1);
	CartesianCoordinate self = CartesianCoordinate(x, y);
	self.clamp(min, max);
	return self;
}
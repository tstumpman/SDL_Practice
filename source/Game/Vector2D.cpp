#include "Vector2D.h"
#include "../MathUtils.h"
#include "SDL/SDL.h"

//Constructor
Vector2D::Vector2D(
	float x, 
	float y
) {
	this->x = x;
	this->y = y;
}

Vector2D::Vector2D() {
	this->x = 0.0f;
	this->y = 0.0f;
}

float Vector2D::dotProduct(const Vector2D& other) const {
	return x * other.x + y * other.y;
}

Vector2D Vector2D::operator+(const Vector2D& other) const {
	return Vector2D(this->x + other.x, this->y + other.y);
}

Vector2D Vector2D::operator*(const Vector2D& other) const {
	return Vector2D(this->x * other.x, this->y * other.y);
}

Vector2D operator*(float scalar, const Vector2D& vector) {
	return vector * scalar;
}

Vector2D Vector2D::operator*(const float scalar) const {
	return Vector2D(x * scalar, y * scalar);
}

Vector2D Vector2D::operator-(const Vector2D& other) const {
	return Vector2D(this->x - other.x, this->y - other.y);
}

float Vector2D::distanceTo(const Vector2D& destination) const {
	Vector2D source = Vector2D(x, y);
	Vector2D distanceVector = destination - source;
	return distanceVector.getMagnitude();
}

Vector2D Vector2D::abs() const {
	return Vector2D(std::abs(x), std::abs(y));
}

void Vector2D::clamp(const Vector2D& minimum, const Vector2D& maximum) {
	Vector2D deltaVector = vectorToBounds(minimum, maximum);
	x = x + deltaVector.x;
	y = y + deltaVector.y;
}

Vector2D& Vector2D::operator=(const Vector2D& other) {
	if (this != &other) {
		this->x = other.x;
		this->y = other.y;
	}
	return *this;
}

Vector2D Vector2D::vectorToBounds(const Vector2D& minimum, const Vector2D& maximum) const {
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

	return Vector2D(deltaX, deltaY);
}

void Vector2D::clampMagnitude(const float maximum) {
	if (maximum < 0) {
		return;
	}
	const float magnitude = getMagnitude();
	if (magnitude < 0) {
		return;
	}
	if (magnitude >  maximum ) {
		Vector2D normal = getNormal();
		x = normal.x * maximum;
		y = normal.y * maximum;
	}
}

Vector2D Vector2D::getProjection(const Vector2D& other) const {
	float dot = dotProduct(other);
	float magnitude = other.getMagnitude();
	double lengthSquared = magnitude * magnitude;
	double scalar = dot / lengthSquared;
	return other * scalar;

}

Vector2D Vector2D::getReflection(const Vector2D& lineNormal) const {
	Vector2D normal = lineNormal.getNormal();
	Vector2D vPerp = getProjection(lineNormal);
	return (*this) - vPerp * 2.0f;
}

Vector2D Vector2D::getNormal() const {
	float length = getMagnitude();
	if (length != 0.0) {
		return Vector2D(x / length, y / length);
	}
	return Vector2D(0.0f, 0.0f);
}

Vector2D Vector2D::getAxisAligned() const {
	float xAxis = 0.0f, yAxis = 0.0f;

	if (x > 0) xAxis = 1;
	if (x < 0) xAxis = -1;
	if (y > 0) yAxis = 1;
	if (y < 0) yAxis = -1;

	return Vector2D(xAxis, yAxis);
}

Vector2D Vector2D::getRotation(const float degrees) const {
	float radians = Math::toRadians(degrees);

	float rotatedX = x * cos(radians) - y * sin(radians);
	float rotatedY = x * sin(radians) + y * cos(radians);

	return Vector2D(rotatedX, rotatedY);
}

float Vector2D::getMagnitude() const {
	return sqrt(x * x + y * y);
}
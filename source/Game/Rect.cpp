#include "Rect.h"
#include "../MathUtils.h"
#include "SDL/SDL.h"

//Constructor
Rect::Rect(
	Vector2D origin,
	Vector2D size
) {
	this->origin = origin;
	this->size = size.abs();
}

Rect::Rect(
	float left,
	float top,
	float width,
	float height
) {
	this->origin = Vector2D(left, top);
	this->size = Vector2D(abs(width), abs(height));
}

Rect::Rect() {
	Rect(0, 0, 0, 0);
}

float Rect::area() const {
	return size.x * size.y;
}

float Rect::perimeter() const {
	return 2 * size.x + 2 * size.y;
}

Rect& Rect::operator=(const Rect& other) {
	if (this != &other) {
		this->origin= other.origin;
		this->size= other.size;
	}
	return *this;
}

float Rect::getDiagonal() const {
	return size.getMagnitude();
}

void Rect::scale(float newScale) {
	Vector2D normalizedDiagonal = size.getNormal();
	this->size = normalizedDiagonal * newScale;
}

void Rect::correctIntersection(const Rect& other) {

	Rect intersection = getIntersection(other);

	Vector2D adjustmentVector = origin - intersection.origin;

	float absX = std::abs(adjustmentVector.x);
	float absY = std::abs(adjustmentVector.y);

	if (absX <= absY) {
		origin = Vector2D(origin.x + adjustmentVector.x, origin.y);
	} else {
		origin = Vector2D(origin.x, origin.y + adjustmentVector.y);
	}
}

Rect Rect::getIntersection(const Rect& other) const {
	// Calculate the max of the left coordinates and the min of the right coordinates
	float left = std::max(this->origin.x, other.origin.x);
	float right = std::min(this->origin.x + this->size.x, other.origin.x + other.size.x);

	// Calculate the max of the top coordinates and the min of the bottom coordinates
	float top = std::max(this->origin.y, other.origin.y);
	float bottom = std::min(this->origin.y + this->size.y, other.origin.y + other.size.y);

	// Check if there is no intersection
	if (left >= right || top >= bottom) {
		return Rect(); // Return an empty Rect (default constructed)
	}

	// Create and return the intersection rectangle
	return Rect(top, left, bottom - top, right - left);
}

Vector2D Rect::getCenterPoint() const {
	return this->origin + this->size * 0.5f;
}

Vector2D Rect::getOrigin() const {
	return this->origin;
}

Vector2D Rect::getSize() const {
	return this->size.abs();
}
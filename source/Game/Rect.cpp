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
	this->origin = Vector2D(top, left);
	this->size = Vector2D(abs(width), abs(height));
}

Rect::Rect() {
	Rect(0, 0, 0, 0);
}

float Rect::area() const {
	return size.getWidth() * size.getHeight();
}

float Rect::perimeter() const {
	return 2 * size.getWidth() + 2 * size.getHeight();
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

	float absX = std::abs(adjustmentVector.getX());
	float absY = std::abs(adjustmentVector.getY());

	if (absX <= absY) {
		origin = Vector2D(origin.getX() + adjustmentVector.getX(), origin.getY());
	} else {
		origin = Vector2D(origin.getX(), origin.getY() + adjustmentVector.getY());
	}
}

Rect Rect::getIntersection(const Rect& other) const {
	// Calculate the max of the left coordinates and the min of the right coordinates
	float left = std::max(this->origin.getX(), other.origin.getX());
	float right = std::min(this->origin.getX() + this->size.getWidth(), other.origin.getX() + other.size.getWidth());

	// Calculate the max of the top coordinates and the min of the bottom coordinates
	float top = std::max(this->origin.getY(), other.origin.getY());
	float bottom = std::min(this->origin.getY() + this->size.getHeight(), other.origin.getY() + other.size.getHeight());

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

Vector2D Rect::getSize() {
	return this->size;
}
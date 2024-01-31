#ifndef C_RECT_2D
#define C_RECT_2D

#include "Vector2D.h"
#include "SDL/SDL_rect.h"

class Rect {
public: 
	Rect(
		Vector2D origin,
		Vector2D size
	);
	Rect(
		float top, 
		float left,
		float height,
		float width
	);
	Rect();

	Rect& operator=(const Rect& other);

	Rect getIntersection(const Rect& other) const;
	void correctIntersection(const Rect& other);
	float area() const;
	float perimeter() const;
	Vector2D getCenterPoint() const;
	Vector2D getOrigin() const;
	Vector2D getSize();
	float getDiagonal() const;
	void scale(float diagonal);


private: 

private://Data
	Vector2D origin, size;
};

#endif
#ifndef C_VECTOR_2D
#define C_VECTOR_2D

class Vector2D {
public: 
	//Default constructor
	Vector2D(
		float x,
		float y
	);
	Vector2D();

	Vector2D& operator=(const Vector2D& other);
	Vector2D operator+(const Vector2D& other) const;
	Vector2D operator-(const Vector2D& other) const;
	Vector2D operator*(const float scalar) const;
	Vector2D operator*(const Vector2D& other) const;
	friend Vector2D operator*( float scalar, const Vector2D& vector);

	void clamp(const Vector2D& minimum, const Vector2D& maximum);
	Vector2D vectorToBounds(const Vector2D& minimum, const Vector2D& maximum) const;
	void clampMagnitude(const float maximum);

	float dotProduct(const Vector2D& other) const;
	Vector2D abs() const;
	Vector2D getProjection(const Vector2D& other) const;
	Vector2D getReflection(const Vector2D& lineNormal) const;
	Vector2D getRotation(const float degrees) const;
	Vector2D getNormal() const;
	Vector2D getAxisAligned() const;
	float getMagnitude() const;
	float getX() const;
	float getY() const;
	float getHeight() const;
	float getWidth() const;
	float distanceTo(const Vector2D& destination) const;

private: //Functions

private://Data
	float x, y;
};

#endif
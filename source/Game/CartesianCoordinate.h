#ifndef C_CARTESIAN_COORDINATE_H
#define C_CARTESIAN_COORDINATE_H

class CartesianCoordinate {
public: 
	int x, y;

	//Default constructor
	CartesianCoordinate(
		int x,
		int y
	);
	CartesianCoordinate();

	CartesianCoordinate& operator=(const CartesianCoordinate& other);
	CartesianCoordinate operator+(const CartesianCoordinate& other) const;
	CartesianCoordinate operator-(const CartesianCoordinate& other) const;
	CartesianCoordinate operator*(const float scalar) const;
	CartesianCoordinate operator*(const CartesianCoordinate& other) const;
	friend CartesianCoordinate operator*( float scalar, const CartesianCoordinate& vector);

	void clamp(const CartesianCoordinate& minimum, const CartesianCoordinate& maximum);
	CartesianCoordinate vectorToBounds(const CartesianCoordinate& minimum, const CartesianCoordinate& maximum) const;

	CartesianCoordinate abs() const;
	CartesianCoordinate getAxisAligned() const;
	unsigned int manhattanDistance(const CartesianCoordinate& destination) const;
	unsigned int rectilinearDistance(const CartesianCoordinate& destination) const;

private: //Functions

private://Data
};

#endif
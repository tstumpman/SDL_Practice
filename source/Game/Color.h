#ifndef C_COLOR_H
#define C_COLOR_H
#include <stdint.h>
class Color {
public: 
	//Default constructor
	Color(
		uint8_t a = 255,
		uint8_t r = 255,
		uint8_t g = 255,
		uint8_t b = 255
	);

	Color& operator=(const Color& other);
	Color operator+(const Color& other) const;
	Color operator-(const Color& other) const;
	Color operator*(const Color& other) const;

private: //Functions

private://Data
	uint8_t a, r, g, b;
};

#endif
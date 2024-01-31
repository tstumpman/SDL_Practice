#include "Color.h"
#include "../MathUtils.h"

// Constructor
Color::Color(uint8_t a, uint8_t r, uint8_t g, uint8_t b) : a(a), r(r), g(g), b(b) {}

// Copy assignment operator
Color& Color::operator=(const Color& other) {
    if (this != &other) {
        a = other.a;
        r = other.r;
        g = other.g;
        b = other.b;
    }
    return *this;
}

// Addition operator
Color Color::operator+(const Color& other) const {
    // Clamping each component to 255
    return Color(
        std::min(255, static_cast<int>(a) + other.a),
        std::min(255, static_cast<int>(r) + other.r),
        std::min(255, static_cast<int>(g) + other.g),
        std::min(255, static_cast<int>(b) + other.b)
    );
}

// Subtraction operator
Color Color::operator-(const Color& other) const {
    // Ensuring each component doesn't go below 0
    return Color(
        std::max(0, static_cast<int>(a) - other.a),
        std::max(0, static_cast<int>(r) - other.r),
        std::max(0, static_cast<int>(g) - other.g),
        std::max(0, static_cast<int>(b) - other.b)
    );
}

// Multiplication operator
Color Color::operator*(const Color& other) const {
    // Clamping each component to 255
    return Color(
        std::min(255, static_cast<int>(a) * other.a / 255),
        std::min(255, static_cast<int>(r) * other.r / 255),
        std::min(255, static_cast<int>(g) * other.g / 255),
        std::min(255, static_cast<int>(b) * other.b / 255)
    );
}

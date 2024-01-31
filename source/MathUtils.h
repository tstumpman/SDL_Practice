#ifndef STUMP_ENGINE_MATH_UTILS_H
#define STUMP_ENGINE_MATH_UTILS_H

#include <algorithm>

namespace Math {

	constexpr float PI = 3.14159265f;
	constexpr float RADIANS_PER_CIRCLE = PI * 2;

	inline constexpr float clamp(float input, float min, float max) {
		// Handle error condition or assert here if min > max
		return std::max(min, std::min(input, max));
	}

	inline constexpr float toRadians(float degrees) {
		return degrees * PI / 180;
	}

	inline constexpr float toDegrees(float radians) {
		return radians * 180 / PI;
	}

} // namespace ProjectMath

#endif // PROJECTNAME_PATH_MATH_UTILS_H

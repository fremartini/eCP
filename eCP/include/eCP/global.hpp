#ifndef GLOBALS_H
#define GLOBALS_H

#include <limits>

/**
 * Global variables
 */
namespace global 
{

inline constexpr float FLOAT_MAX = std::numeric_limits<float>::max();
inline constexpr float FLOAT_MIN = std::numeric_limits<float>::min();

extern unsigned int g_vector_dimensions;

}

#endif  // GLOBALS_H
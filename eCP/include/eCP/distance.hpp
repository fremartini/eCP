#ifndef DISTANCE_H
#define DISTANCE_H

#include <cmath>

/**
 * Distance functions defined for global use here. Can be imported and used 
 * and will only be
 */
namespace distance {

/**
 * Globally scoped pointer to the used distance function.
 */
extern float (*g_distance_function)(const float*, const float*);

enum METRIC { EUCLIDEAN, ANGULAR };

float euclidean_distance(const float* a, const float* b);
float angular_distance(const float* a, const float* b);

/**
 * Set the used distance function.
 */
void set_distance_function(METRIC func);

}

#endif  // DISTANCE_H
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
extern float (*g_distance_function)(float*&, float*&);

enum METRIC { EUCLIDEAN, ANGULAR };

float euclidean_distance(float*& a, float*& b);
float angular_distance(float*& a, float*& b);

/**
 * Set the used distance function.
 */
void set_distance_function(METRIC func);

}

#endif  // DISTANCE_H
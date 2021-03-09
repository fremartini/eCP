#ifndef DISTANCE_H
#define DISTANCE_H

#include <cmath>
#include <vector>

#include <eCP/index/data_structure.hpp>

/**
 * Distance functions defined for global use here. Can be imported and used.
 */
namespace distance 
{

/**
 * External linkage. Globally scoped pointer to the used distance function.
 */
extern float (*g_distance_function)(const float*, const float*);

Node* get_closest_node(std::vector<Node>& nodes, float* query);
float euclidean_distance(const float* a, const float* b);
float angular_distance(const float* a, const float* b);

enum class Metrics { EUCLIDEAN, ANGULAR };

/**
 * Set the used distance function.
 */
void set_distance_function(Metrics);

}

#endif  // DISTANCE_H

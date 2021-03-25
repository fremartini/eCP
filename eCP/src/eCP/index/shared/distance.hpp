#ifndef DISTANCE_H
#define DISTANCE_H

#include <eCP/index/shared/data_structure.hpp>
#include <cmath>
#include <vector>

/**
 * Distance functions defined for global use here. Can be imported and used.
 */
namespace distance {

/**
 * External linkage. Globally scoped pointer to the used distance function.
 */
extern float (*g_distance_function)(const float*, const float*, const float&);

Node* get_closest_node(std::vector<Node*>& nodes, float* query);
float euclidean_distance(const float* a, const float* b, const float&);
float euclidean_distance_halt(const float* a, const float* b, const float&);
float euclidean_distance_unroll_halt(const float* a, const float* b, const float&);
float angular_distance(const float* a, const float* b, const float&);
float annoy_distance(const float* a, const float* b, const float&);

enum class Metrics { EUCLIDEAN, ANGULAR, EUCLIDEAN_UNROLL, EUCLIDEAN_HALT, EUCLIDEAN_UNROLL_HALT, ANNOY_DISTANCE };

/**
 * Set the globally used distance function.
 * @param Metrics distance function
 */
void set_distance_function(Metrics);
}  // namespace distance

#endif  // DISTANCE_H

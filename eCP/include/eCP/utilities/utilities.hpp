#ifndef UTILITY_H
#define UTILITY_H

#include <vector>
#include <eCP/index/eCP.hpp>

/**
 * Namespace contains utility functions used by the eCP implementation.
 */
namespace utility {

/**
 * @brief generate_descriptors generates a set of multidimensional feature vectors.
 * @param count is number of feature vectors to generate.
 * @param dimension is the number of dimensions each vector should have (length)
 * @param upper_bound is the maximum value contained in any feature vector.
 * @return
 */
std::vector<std::vector<float>> generate_descriptors(unsigned int count, unsigned int dimension, unsigned int upper_bound);
}

#endif // UTILITY_H

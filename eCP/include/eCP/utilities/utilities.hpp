#ifndef UTILITY_H
#define UTILITY_H

#include <vector>
#include <unordered_set>

/**
 * Namespace contains utility functions used by the eCP implementation.
 */
namespace utilities {

/**
 * @brief get_random_unique_indexes returns a set of uniquely sampled indexes from
 * the range 0..container_size.
 * It is assumed that amount < container_size. An empty unordered_list is returned if
 * an errors occurs.
 * @param amount number of samples to get.
 * @param container_size limit of the range of samples to pick from.
 */
std::unordered_set<unsigned> get_random_unique_indexes(unsigned amount, unsigned container_size);

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

#ifndef UTILITY_H
#define UTILITY_H

#include <unordered_set>
#include <vector>
#include <string>

/**
 * Namespace contains utility functions used by the eCP implementation.
 */
namespace utilities {

/**
 * @brief get_random_unique_indexes returns a set of uniquely sampled indexes from
 * the range 0..container_size.
 * It is assumed that amount is non-negative and greater than container_size.
 * @param amount number of samples to get.
 * @param container_size limit of the range of samples to pick from.
 */
std::unordered_set<int> get_random_unique_indexes(int amount, int container_size);

/**
 * @brief generate_descriptors generates a set of multidimensional feature vectors.
 * @param count is number of feature vectors to generate.
 * @param dimension is the number of dimensions each vector should have (length)
 * @param upper_bound is the maximum value contained in any feature vector.
 * @return
 */
std::vector<std::vector<float>> generate_descriptors(unsigned int count, unsigned int dimension, unsigned int upper_bound);

/**
 * @brief Opens .hdf5 or .h5 files and outputs the specified dataset as multidimensional vectors
 * @param path path for hdf5 file
 * @param dataset name
 * @return  multidimensional vectors of type float
 */
std::vector<std::vector<float>> load_hdf5_file(std::string& path, std::string& dataset);
}  // namespace utilities

#endif  // UTILITY_H

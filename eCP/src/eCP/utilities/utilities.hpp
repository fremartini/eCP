#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <unordered_set>
#include <vector>

/**
 * Namespace contains utility functions used by the eCP implementation.
 */
namespace utilities {

/**
 * @brief get_random_unique_indexes returns a set of uniquely sampled indexes from
 * the range 0..container_size.
 * It is assumed that amount is greater than zero but less than or equal to container_size.
 * @param amount is the number of samples to get.
 * @param container_size is the limit of the range of samples to pick from.
 * @return a vector containing the unique samples obtained from container_size.
 */
std::vector<unsigned> get_random_unique_indexes(int amount, int container_size);

/**
 * @brief generate_descriptors generates a set of multidimensional feature vectors.
 * @param count is number of feature vectors to generate.
 * @param dimension is the number of dimensions each vector should have (length)
 * @param upper_bound is the maximum value contained in any feature vector.
 * @return
 */
std::vector<std::vector<float>> generate_descriptors(unsigned int count, unsigned int dimension,
                                                     unsigned int upper_bound);

/**
 * @brief Opens .hdf5 or .h5 files and outputs the specified dataset as multidimensional vectors
 * @param path path for hdf5 file
 * @param dataset name
 * @return  multidimensional vectors of type float
 */
std::vector<std::vector<float>> load_hdf5_file(std::string& path, std::string& dataset);
}  // namespace utilities

#endif  // UTILITY_H

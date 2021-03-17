#include <queue>
#include <cmath>
#include <iostream>
#include <random>
#include <cassert>

#include <eCP/utilities/utilities.hpp>
#include <eCP/utilities/H5Easy/H5Easy.h>

namespace utilities {

// Uses a set when checking for seen samples but returns a vector for convenience.
// Time complexity is O(amount), space complexity is 2*amount due to the convenience
// vector as return type.
std::vector<unsigned> get_random_unique_indexes(int amount, int container_size)
{
  assert(amount > 0 && "Amount must be greater than zero.");
  assert(amount <= container_size && "Amount must be less than or equal to container_size");

  std::vector<unsigned> collected_samples;
  collected_samples.reserve(amount);

  std::unordered_set<int> visited_samples;
  std::random_device random_seed;   // Will be used to obtain a seed for the random number engine.
  std::mt19937 generator(random_seed());  // Standard mersenne_twister_engine seeded with rd().
  int start = container_size - amount;

  for (int j = start; j < container_size; ++j) {
    std::uniform_int_distribution<> distribution(0, j);  // To-from inclusive.
    unsigned t = distribution(generator);

    std::unordered_set<int>::const_iterator iter = visited_samples.find(t);
    if (iter == visited_samples.end()) {  // Not found.
      visited_samples.insert(t);
      collected_samples.emplace_back(t);
    }
    else {
      visited_samples.insert(j);    // Found.
      collected_samples.emplace_back(j);
    }
  }
  return collected_samples;
}

std::vector<std::vector<float>> generate_descriptors(const unsigned int count, const unsigned int dimension, const unsigned int upper_bound)
{
	std::vector<std::vector<float>> vector_list;
	for (unsigned int i = 0; i < count; i++) {
		std::vector<float> point_vector;

		for (unsigned int j = 0; j < dimension; j++) {
			point_vector.push_back(static_cast<float>(rand() % upper_bound));
		}
		vector_list.push_back(point_vector);
	}

	vector_list.shrink_to_fit();
	return vector_list;
}

std::vector<std::vector<float>> load_hdf5_file(std::string& path, std::string& dataset) {
    LoadH5 data;
    data.setFileName(path);
    data.setVarName(dataset);
    return data.getData();
}



}

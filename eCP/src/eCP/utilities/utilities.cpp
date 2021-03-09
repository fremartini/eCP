#include <queue>
#include <cmath>
#include <iostream>
#include <random>

#include <eCP/utilities/utilities.hpp>

namespace utilities {

std::unordered_set<unsigned> get_random_unique_indexes(unsigned amount, unsigned container_size)
{
  if (amount < 0) return std::unordered_set<unsigned>{};
  if (container_size < amount) return std::unordered_set<unsigned>{};

  std::unordered_set<unsigned> samples;
  std::random_device random_seed;   // Will be used to obtain a seed for the random number engine
  std::mt19937 generator(random_seed());  // Standard mersenne_twister_engine seeded with rd()
  int start = container_size - amount;

  for (unsigned j = start; j < container_size; ++j) {
    std::uniform_int_distribution<> distribution(0, j);  // To-from inclusive
    unsigned t = distribution(generator);

    std::unordered_set<unsigned>::const_iterator iter = samples.find(t);
    if (iter == samples.end()) {  // not found
      samples.insert(t);
    }
    else {
      samples.insert(j);    // found
    }
  }
  return samples;
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

}

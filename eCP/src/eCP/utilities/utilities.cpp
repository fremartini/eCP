#include <queue>
#include <cmath>
#include <iostream>

#include <eCP/utilities/utilities.hpp>
#include <eCP/index/globals.hpp>

namespace utility {

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

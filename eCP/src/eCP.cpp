#include <cmath>

#include <eCP/eCP.hpp>
#include <eCP/pre-processing.hpp>
#include <eCP/query-processing.hpp>
#include <eCP/distance.hpp>
#include <eCP/data_structure.hpp>
#include <eCP/globals.hpp>

namespace eCP 
{
/*
 * Entry point for ANN-Benchmarks fit function. Partitions the data set before creating
 * the empty index. The distance function is also set globally.
 */
Index* eCP_Index(const std::vector<std::vector<float>> &descriptors, unsigned int L, unsigned int metric)
{
	//set dimension globally to avoid duplication
	globals::g_vector_dimensions = descriptors[0].size();

	//internal data structure uses pointers, translate floats from ANN-Benchmarks to something usable
	std::vector<Point> descriptor_points;
  descriptor_points.reserve(descriptors.size());

//	for (unsigned int i = 0; i < descriptors.size(); i++) {
//    float* desc_p = new float[globals::g_vector_dimensions];

//		for (unsigned int d = 0; d < globals::g_vector_dimensions; d++) {
//			desc_p[d] = descriptors[i][d];
//		}

//		descriptor_points.emplace_back(desc_p, i);
//	}

  unsigned id{0};
  for (auto &desc : descriptors) {
    descriptor_points.emplace_back(Point{desc.data(), id++});
  }

	//set metric function
  if (metric == 1) {
        distance::set_distance_function(distance::Metrics::ANGULAR);
  } else {
        distance::set_distance_function(distance::Metrics::EUCLIDEAN);
  }

	//initial sample size for building index - n^L/L+1 for initial representatives
	const auto sample_size = std::ceil(std::pow(descriptors.size(), ((L / (L + 1.00)))));               // The first 'sample_size' elems is used as leaders for the bottom level

  std::vector<Node> empty_index_root = pre_processing::create_index(descriptor_points, L);

  auto index_root = pre_processing::insert_points(empty_index_root, descriptor_points, sample_size);

  return new Index(L, index_root, descriptor_points);
}

/*
 * Entry point for ANN-Benchmarks query function. SWIG converts python list to std::vector
 */
std::pair<std::vector<unsigned int>, std::vector<float>> query(Index* index, std::vector<float> query, unsigned int k, unsigned int b)
{
	//internal data structure uses float pointer instead of vectors
  float* q = query.data();

	auto nearest_points = query_processing::k_nearest_neighbors(index->top_level, q, k, b, index->L);

	//unzip since id are only needed for ANN-Benchmarks
	std::vector<unsigned int> nearest_indexes = {};
	std::vector<float> nearest_dist = {};

	for (auto it = std::make_move_iterator(nearest_points.begin()),
		end = std::make_move_iterator(nearest_points.end()); it != end; ++it)
	{
		nearest_indexes.push_back(it->first);
		nearest_dist.push_back(it->second);
	}

	return make_pair(nearest_indexes, nearest_dist);
}

}

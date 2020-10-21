#include <cmath>

#include <eCP/eCP.hpp>
#include <eCP/pre-processing.hpp>
#include <eCP/query-processing.hpp>

// global variables
unsigned int g_vector_dimensions;
float (*g_distance_function)(float*&, float*&);

/*
 * entry point for ANN-Benchmarks fit function. Partitions the data set before creating
 * the empty index. The distance function is also set globally.
 */
Index* eCP_Index(const std::vector<std::vector<float>> descriptors, unsigned int L, unsigned int metric)
{
	//set dimension globally to avoid duplication
	g_vector_dimensions = descriptors[0].size();

	//internal data structure uses pointers, translate floats from ANN-Benchmarks to something usable
	std::vector<Point> descriptor_points;
	for (unsigned int i = 0; i < descriptors.size(); i++) {
		float* desc_p = new float[g_vector_dimensions];

		for (unsigned int d = 0; d < g_vector_dimensions; d++) {
			desc_p[d] = descriptors[i][d];
		}

		descriptor_points.emplace_back(desc_p, i);
	}

	//set metric function
	if (metric == 1) {
		g_distance_function = &angular_distance;
	}
	else
	{
		g_distance_function = &euclidean_distance;
	}
	//initial sample size for building index - n^L/L+1 for initial representatives
	const auto sample_size = std::ceil(std::pow(descriptors.size(), ((L / (L + 1.00)))));   // TODO: Consider refac out of this func to test

	std::vector<Node*> empty_index_root = Pre_Processing::create_index(descriptor_points, L);

	auto index_root = Pre_Processing::insert_points(empty_index_root, descriptor_points, sample_size);

	return new Index(L, index_root, descriptor_points);
}

/*
 * entry point for ANN-Benchmarks query function. SWIG converts python list to std::vector
 */
std::pair<std::vector<unsigned int>, std::vector<float>> query(Index* index, std::vector<float> query,
    unsigned int k, unsigned int b)
{
	//internal data structure uses float pointer instead of vectors
	float* q = &query[0];

	auto nearest_points = Query_Processing::k_nearest_neighbors(index->top_level, q, k, b, index->L);

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
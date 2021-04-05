#include <cmath>
#include <eCP/index/eCP.hpp>
#include <eCP/index/pre-processing.hpp>
#include <eCP/index/query-processing.hpp>
#include <eCP/index/shared/data_structure.hpp>
#include <eCP/index/shared/distance.hpp>
#include <eCP/index/shared/globals.hpp>
#include <stdexcept>

namespace eCP {

/*
 * Entry point for ANN-Benchmarks fit function.
 */
Index* eCP_Index(const std::vector<std::vector<float>>& descriptors, unsigned int L, unsigned int metric_)
{
  if (L < 1) {
    throw std::invalid_argument("L >= 1 to build a valid index.");
  }

  // Set descriptor dimension globally.
  globals::g_vector_dimensions = descriptors[0].size();

  // Set distance function globally
  auto metric = static_cast<distance::Metric>(metric_);
  distance::set_distance_function(metric);

  // Build index
  std::vector<Node> index = pre_processing::create_index(descriptors, L);

  return new Index(L, index);
}

/*
 * Entry point for ANN-Benchmarks query function. SWIG converts python list to std::vector
 */
std::pair<std::vector<unsigned int>, std::vector<float>> query(Index* index, std::vector<float> query,
                                                               unsigned int k, unsigned int b)
{
  // internal data structure uses float pointer instead of vectors
  float* q = query.data();

  auto nearest_points = query_processing::k_nearest_neighbors(index->top_level, q, k, b, index->L);

  // unzip since id are only needed for ANN-Benchmarks
  std::vector<unsigned int> nearest_indexes = {};
  std::vector<float> nearest_dist = {};

  for (auto it = std::make_move_iterator(nearest_points.begin()),
            end = std::make_move_iterator(nearest_points.end());
       it != end; ++it) {
    nearest_indexes.push_back(it->first);
    nearest_dist.push_back(it->second);
  }

  return make_pair(nearest_indexes, nearest_dist);
}

}  // namespace eCP

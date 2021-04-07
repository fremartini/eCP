#ifndef DEBUG_H
#define DEBUG_H

#include <eCP/index/shared/data_structure.hpp>
#include <vector>

/**
 * Namespace contains functions to investigate the implementation and to help verify behaviour of the index.
 */
namespace debugging {

void print_query_results(std::pair<std::vector<unsigned int>, std::vector<float>>& res,
                         std::vector<float>& query, unsigned int k, const std::vector<std::vector<float>>& S);

void print_point(Point& p);

void print_points(std::vector<Point>& points);

void print_cluster(Node& c, unsigned int d);

void print_clusters(std::vector<Node>& clusters);

void print_index_levels(std::vector<Node>& root);

}  // namespace debugging

#endif  // DEBUG_H

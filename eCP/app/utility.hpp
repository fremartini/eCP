#ifndef UTILITY_H
#define UTILITY_H

#include <vector>
#include <eCP/eCP.hpp>

namespace utility {

void print_query_results(std::pair<std::vector<unsigned int>, std::vector<float>>& res, std::vector<float>& query, unsigned int k, const std::vector<Point>& S);

std::vector<std::vector<float>> generate_descriptors(unsigned int count, unsigned int dimension, unsigned int upper_bound);

void print_point(Point& p);

void print_points(std::vector<Point>& points);

void print_cluster(Node& c, unsigned int d);

void print_clusters(std::vector<Node>& clusters);

void print_index_levels(std::vector<Node>& root);

}

#endif // UTILITY_H

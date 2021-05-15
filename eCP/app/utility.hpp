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

void print_clusters(std::vector<Node*>& clusters);

void print_index_levels(std::vector<Node*>& root);

/**
 * @brief Opens .hdf5 or .h5 files and outputs the specified dataset as multidimensional vectors
 * @param path path for hdf5 file
 * @param dataset name
 * @return  multidimensional vectors of type float
 */
std::vector<std::vector<float>> load_hdf5_file(std::string& path, std::string& dataset);

}

#endif // UTILITY_H
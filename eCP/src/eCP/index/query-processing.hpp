#ifndef QUERY_PROCESSING_H
#define QUERY_PROCESSING_H

#include <eCP/index/shared/data_structure.hpp>
#include <vector>

namespace query_processing {

/**
 * search the index for k nearest neighbors
 * @param root index top level
 * @param query query point
 * @param k amount of nearest neighbors to look for
 * @param b amount of leaves to search
 * @return vector of (index,distance) pairs sorted by lowest distance
 */
std::vector<std::pair<unsigned int, float>> k_nearest_neighbors(std::vector<Node>& root, float*& query,
                                                                unsigned int k, unsigned int b,
                                                                unsigned int L);

/**
 * find the index of the pair with the largest distance
 * @param point_pairs vector of tuples of (index,distance)
 * @return index to element with largest distance
 */
unsigned int index_to_max_element(std::vector<std::pair<unsigned int, float>>& point_pairs);

/**
 * find the b nearest leaves
 * @param L index depth
 * @param root index top_level
 * @param query query point
 * @param b number of leaf clusters to return
 * @return b leaf clusters
 */
std::vector<Node*> find_b_nearest_clusters(std::vector<Node>& root, float*& query, unsigned int b,
                                           unsigned int L);

/*
 * scan nodes for b nearest clusters
 * @param query query point
 * @param nodes nodes to be searched
 * @param b number of clusters to obtain
 * @param node_accumulator accumulator for b nearest nodes
 */
void scan_node(float*& query, std::vector<Node>& nodes, unsigned int& b,
               std::vector<Node*>& node_accumulator);

/**
 * find the furthest cluster to a query point
 * @param query query point
 * @param nodes vector of nodes to search
 */
std::pair<int, float> find_furthest_node(float*& query, std::vector<Node*>& nodes);

/**
 * find k the nearest (point,distances) to the query point
 * @param query query point
 * @param points vector of points to search
 * @param k amount of nearest points to return
 * @param nearest_points accumulator of k nearest neighbors
 */
void scan_leaf_node(float*& query, std::vector<Point>& points, unsigned int k,
                    std::vector<std::pair<unsigned int, float>>& nearest_points);

/*
 * comparator for sorting
 * @param a tuple a (index, distance)
 * @param b tuple b (index, distance)
 */
bool smallest_distance(std::pair<unsigned int, float>& a, std::pair<unsigned int, float>& b);
}  // namespace query_processing

#endif  // QUERY_PROCESSING_H

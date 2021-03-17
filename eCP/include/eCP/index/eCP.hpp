#ifndef ECP_H
#define ECP_H

#include <vector>
#include <eCP/index/shared/data_structure.hpp>

/**
 * @file eCP.cpp
 * Library for the extended cluster pruning algorithm.
 *
 * @author Nikolaj Mertz
 * @author Frederik Martini
 * @author Morten Skøtt
 * @date 09/03/2021
 */
namespace eCP
{

 /**
  * create an L level index from a data set
  * @param descriptors is a vector of feature descriptors that the index should be built from.
  * @param L is the number of levels in the index. L = cluster level.
  * @param metric is the used distance function for the metric space. 0 = euclidean, 1 = angular
  * @return a pointer to the created index
  */
Index* eCP_Index(const std::vector<std::vector<float>> &descriptors, unsigned int L, unsigned int metric);

/**
 * ANN search in index
 * @param index is the index structure used to make queries on.
 * @param query is the query point we are looking for k-nn for.
 * @param k is the number of k-nn to return.
 * @param b is the number of clusters to search.
 * @return collection of tuples containing index in data set and distance to query point
 */
std::pair<std::vector<unsigned int>, std::vector<float>> query(Index* index, std::vector<float> query, unsigned int k, unsigned int b);

}

#endif // ECP_H

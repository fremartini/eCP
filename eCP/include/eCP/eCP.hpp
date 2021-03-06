#ifndef ECP_H
#define ECP_H

/**
 * @file eCP.cpp
 * Static library for the extended cluster pruning algorithm
 *
 * @author Nikolaj Mertz
 * @author Frederik Martini
 * @date 15/5/2020
 */

#include <vector>
#include <eCP/data_structure.hpp>

namespace eCP 
{

 /**
  * create an L level index from a data set
  * @param descriptors floating point numbers data set
  * @param L number of levels in the index
  * @param metric distance function for index creation and querying. 0 = euclidean, 1 = angular
  * @return pointer to created index
  */
Index* eCP_Index(const std::vector<std::vector<float>> &descriptors, unsigned int L, unsigned int metric);

/**
 * ANN search in index
 * @param index index for querying
 * @param query query point
 * @param k number of approximate nearest neighbors to return
 * @param b number of clusters to search
 * @return collection of tuples containing index in data set and distance to query point
 */
std::pair<std::vector<unsigned int>, std::vector<float>> query(Index* index, std::vector<float> query, unsigned int k, unsigned int b);

}

#endif // ECP_H

#ifndef PRE_PROCESSING_H
#define PRE_PROCESSING_H

#include <eCP/index/shared/data_structure.hpp>
#include <vector>

/*
 * contains functions used during the preprocessing phase.
 */
namespace pre_processing {
/**
 * @brief create_index creates the index from a given dataset and a parameter L denoting number of levels.
 * @param dataset is the collection of points to be placed in the created index.
 * @param L is the number of levels the index should have.
 * @returns the topmost vector of Nodes equal to level 1 in the index.
 */
std::vector<Node> create_index(const std::vector<std::vector<float>>& descriptors, unsigned L);

}  // namespace pre_processing

#endif  // PRE_PROCESSING_H

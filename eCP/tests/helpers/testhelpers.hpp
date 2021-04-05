#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#include <eCP/index/shared/data_structure.hpp>

/**
 * This namespace contains various test helper functions.
 */
namespace testhelpers {

/**
 * @brief measure_depth measures the depth of a series of vectors with children.
 * @param root is the root element containing level 1 child list.
 * @return unsigned integer depicting how many levels starting from 1.
 */
unsigned measure_depth_from(Node root);

/**
 * @param root is the root element containing level 1 child list.
 * @return unsigned integer depicting how many points the index contains.
 */
unsigned count_points_in_clusters(Node root);

/**
 * @param root is the root element containing level 1 child list.
 * @return unsigned integer depicting how many clusters the index contains.
 */
unsigned count_clusters(Node root, unsigned parent_children = 0);

}  // namespace testhelpers

#endif  // TEST_HELPERS_H

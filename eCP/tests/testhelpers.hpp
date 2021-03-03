#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#include <eCP/data_structure.hpp>

/**
 * This namespace contains various test helper functions.
 */
namespace testhelpers {

/**
 * @brief measure_depth measures the depth of a series of vectors with children.
 * @param root is the topmost element.
 * @return unsigned integer depicting how many levels starting from 1.
 */
unsigned measure_depth(Node root);
}

#endif // TEST_HELPERS_H

#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

#include <iostream>
#include <cstring>
#include <utility>
#include <vector>
#include <limits>
#include <eCP/index/shared/globals.hpp>

/*
 * Internal data structures and distance functions for the eCP algorithm.
 */

/**
 * Represents a point in high-dimensional space.
 * @param descriptor pointer to first element of feature vector>
 * @param id index in data set.
 */
struct Point {
  float* descriptor;
  unsigned id;

  /**
   * @brief Point default constructor. NB: Assumes that g_vector_dimensions is set.
   * @param descriptor_ is a pointer to the descriptor the Point should contain.
   * @param id_ is the id of the Point.
   */
  explicit Point(const float* descriptor_, unsigned id_);

  ~Point();

  // Copy constructor.
  Point(const Point& other);

  // Move constructor.
  Point(Point&& other) noexcept;

  // Copy+Move assignment operator. Notice takes concrete instance.
  Point& operator=(Point other) noexcept;

  /**
   * @brief swap follows copy-and-swap idiom. Swaps pointers instead of allocating
   * and copying the entire array.
   * See https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom.
   * @param fst is Point to swap contents to.
   * @param snd is Point to swap contents from.
   */
  friend void swap(Point& fst, Point& snd);
};

/**
 * Represents nodes and clusters in index. Will not have children at bottom level.
 * First element of points is always the representative.
 * @param children nodes at next level.
 * @param points in high-dimensional space. First element is always the node representative.
 */
struct Node {
  std::vector<Node> children;
  std::vector<Point> points;
  explicit Node(Point p);
};

/**
 * Represent the index of nodes built from the data set
 * @param L depth of the index
 * @param top_level top level of the index
 * @param dataset dataset of points the index was built from
 */
struct Index {
  unsigned L;
  std::vector<Node> top_level;
  Index(unsigned L_, std::vector<Node>& top_level_);
};

#endif // DATA_STRUCTURE_H

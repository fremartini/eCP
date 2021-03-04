#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

#include <iostream>
#include <cstring>
#include <utility>
#include <vector>
#include <limits>
#include <eCP/globals.hpp>

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
  explicit Point(const float* descriptor_, unsigned id_)
    : descriptor(new float[globals::g_vector_dimensions]), id(id_)
  {
//    std::cout << "default ctor called" << std::endl;
    std::memcpy(descriptor, descriptor_, globals::g_vector_dimensions);
  }

  ~Point()
  {
//    std::cout << "destructor called" << std::endl;
    delete[] descriptor;
  }

  // Copy constructor.
  Point(const Point& other)
    : Point(other.descriptor, other.id)
  {
//    std::cout << "copy ctor called" << std::endl;
  }

  // Copy assingment operator.
  Point& operator=(const Point& other)
  {
//    std::cout << "copy assignement called" << std::endl;
    return *this = Point(other);
  }

  // Move constructor.
  Point(Point&& other) noexcept
//    : descriptor(std::exchange(other.descriptor, nullptr)), id(std::exchange(other.id, 0))
    : descriptor(nullptr), id(0)
  {
//    std::cout << "move ctor called" << std::endl;
    swap(*this, other);
  }

  // Move assignment operator.
  Point& operator=(Point&& other) noexcept
  {
//    std::cout << "move assignement called" << std::endl;
    swap(*this, other);
    return *this;
  }


  // Copy assingment operator. Point passed by-value gives us a copied local version of 'other'.
//  Point& operator=(Point other)
//  {
//    std::cout << "copy assignement called" << std::endl;
//    swap(*this, other);
//    return *this;
//  }

  // Move constructor.
//  Point(Point&& other) noexcept
//    : Point{nullptr, 0}
//  {
//    std::cout << "move ctor called" << std::endl;
//    swap(*this, other);
//  }

  /**
 * @brief swap follows copy-and-swap idiom. Swaps pointers instead of allocating
 * and copying the entire array.
 * See https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom.
 * @param fst is Point to swap contents to.
 * @param snd is Point to swap contents from.
 */
  friend void swap(Point& fst, Point& snd)
  {
    using std::swap;
    swap(fst.id, snd.id);
    swap(fst.descriptor, snd.descriptor);
  }
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

  Node(Point p)
    : points{p} {}
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
  std::vector<Point> dataset;

  Index(unsigned L_, std::vector<Node>& top_level_, std::vector<Point>& dataset_)
    : L(L_), top_level(top_level_), dataset(dataset_) {}
};

#endif // DATA_STRUCTURE_H

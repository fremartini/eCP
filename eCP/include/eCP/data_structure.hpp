#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

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

  Point(float* descriptor_, unsigned id_)
    : descriptor(descriptor_), id(id_) {}

  ~Point()
  {
    delete[] descriptor;
  }

  // Copy constructor.
  Point(const Point& other)
    : descriptor(globals::g_vector_dimensions ? new float[globals::g_vector_dimensions] : throw("asshole")), // FIXME: This line is probably major issue b/c vector dimensions is a global var.
      id(other.id)
  {
    std::copy(other.descriptor, other.descriptor + globals::g_vector_dimensions, descriptor);
  }

  // Move constructor. Used when Point initialize with rvalues.
  Point(Point&& other) noexcept
    : Point{nullptr, 0}
  {
    swap(*this, other);
  }

  // Copy assingment operator. Point passed by-value gives us a copied local version of 'other'.
  Point& operator=(Point other)
  {
    swap(*this, other);
    return *this;
  }

  // Move assignment operator.
  Point& operator=(Point&& other) noexcept
  {
    swap(*this, other);
    return *this;
  }

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

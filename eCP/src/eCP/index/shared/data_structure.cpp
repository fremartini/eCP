#include <iostream>
#include <cstring>
#include <utility>
#include <vector>
#include <limits>
#include <eCP/index/shared/data_structure.hpp>
#include <eCP/index/shared/globals.hpp>

/*
 * Point data type
 */
Point::Point(const float* descriptor_, unsigned id_)
  : descriptor(new float[globals::g_vector_dimensions]), id(id_)
{
  std::copy(descriptor_, descriptor_ + globals::g_vector_dimensions, descriptor);
}

Point::~Point()
{
  delete[] descriptor;
}

// Copy constructor.
Point::Point(const Point& other)
  : Point(other.descriptor, other.id)
{}

// Move constructor.
Point::Point(Point&& other) noexcept
  : descriptor(nullptr), id(0)
{
  swap(*this, other);
}

// Copy+Move assignment operator. Notice takes concrete instance.
Point& Point::operator=(Point other) noexcept
{
  swap(*this, other);
  return *this;
}

void swap(Point& fst, Point& snd)
{
  using std::swap;
  swap(fst.id, snd.id);
  swap(fst.descriptor, snd.descriptor);
}

/*
 * Node data type
 */
Node::Node(Point p)
  : points{p}
{}

/*
 * Index data type
 */
Index::Index(unsigned L_, std::vector<Node>& top_level_, std::vector<Point>& dataset_)
  : L(L_), top_level(top_level_), dataset(dataset_)
{}

#pragma once
/**
 * @file distance.cpp
 * Internal data structures and distance functions for the eCP algorithm
 *
 * @author Nikolaj Mertz
 * @author Frederik Martini
 * @date 15/5/2020
 */

 // distance functions
 /**
  * computes the euclidean distance between 2 vectors
  * @param a pointer to first element in array a
  * @param b pointer to first element in array b
  * @return euclidean distance between a and b
  */
float euclidean_distance(float*& a, float*& b);
/**
 * computes the angular distance between 2 vectors
 * @param a pointer to first element in array a
 * @param b pointer to first element in array b
 * @return angular distance between a and b
 */
float angular_distance(float*& a, float*& b);

// structs
#define FLOAT_MAX std::numeric_limits<float>::max();
#define FLOAT_MIN std::numeric_limits<float>::min();

// global variables
extern float (*g_distance_function)(float*&, float*&);
extern unsigned int g_vector_dimensions;

// data structures

/**
 * represents a point in high-dimensional space
 * @param descriptor pointer to first element of feature vector
 * @param id index in data set
 */
struct Point {
	unsigned int id;
	float* descriptor;

	Point(float* _descriptor, unsigned int _id) {
		id = _id;
		descriptor = _descriptor;
	}

	~Point() = default;

	//only used for unit testing
	friend inline bool operator==(const Point& lhs, const Point& rhs)
	{
		return
			*lhs.descriptor == *rhs.descriptor &&
			lhs.id == rhs.id;
	}
};
/*
 * represents nodes and clusters in index. Will not have children at bottom level.
 * First element of points is always the representative
 * @param children nodes at next level
 * @param points points in high-dimensional space. First element is always the node representative
 */
struct Node {
	std::vector<Node*> children;
	std::vector<Point> points;

	Node(Point& p) {
		points.reserve(1);
		points.push_back(p);
	}

	~Node()
	{
		for (Node* child : children)
		{
			delete child;
		}
	}

	//only used for unit testing
	friend inline bool operator==(const Node& lhs, const Node& rhs)
	{
		return
			lhs.children == rhs.children &&
			lhs.points == rhs.points;
	}

	bool is_leaf() const
	{
		return children.empty();
	}

	float*& get_representative()
	{
		return points[0].descriptor;
	}
};

/**
 * represent the index of nodes built from the data set
 * @param L depth of the index
 * @param top_level top level of the index
 * @param dataset dataset of points the index was built from
 */
struct Index
{
	unsigned int L;
	std::vector<Node*> top_level;
	std::vector<Point> dataset;

	Index(unsigned int _L, std::vector<Node*>& _top_level, std::vector<Point>& _dataset)
	{
		L = _L;
		top_level = _top_level;
		dataset = _dataset;
	}

	~Index()
	{
		for (Node* node : top_level)
		{
			delete node;
		}
		for (auto point : dataset)
		{
			delete[] point.descriptor;
		}
	}
};
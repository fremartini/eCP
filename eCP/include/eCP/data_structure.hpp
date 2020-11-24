#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

#include <limits>

/**
 * Internal data structures and distance functions for the eCP algorithm
 */

/**
 * Represents a point in high-dimensional space.
 * @param descriptor pointer to first element of feature vector>
 * @param id index in data set.
 */
struct Point {
	unsigned int id;
	float* descriptor;

	Point(float* _descriptor, unsigned int _id) {
		id = _id;
		descriptor = _descriptor;
	}

	~Point() = default;
};

/*
 * Represents nodes and clusters in index. Will not have children at bottom level.
 * First element of points is always the representative.
 * @param children nodes at next level.
 * @param points points in high-dimensional space. First element is always the node representative.
 */
struct Node {
	std::vector<Node*> children;
	std::vector<Point> points;

	Node(const Point& p) {
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
};

/**
 * Represent the index of nodes built from the data set
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

#endif // DATA_STRUCTURE_H
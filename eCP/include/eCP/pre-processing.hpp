#ifndef PRE_PROCESSING_H
#define PRE_PROCESSING_H

/**
 * @file distance.cpp
 * static functions for the eCP algorithm preprocessing phase
 *
 * @author Nikolaj Mertz
 * @author Frederik Martini
 * @date 15/5/2020
 */

#include <vector>
#include <eCP/data_structure.hpp>

 /*
  * contains static functions for the preprocessing phase of the eCP algorithm.
  *
  */
class Pre_Processing {
public:
	/**
	* creates the cluster index from dataset and level parameter L
	* @param dataset collection of all points to be placed in the created index
	* @param L levels of the index
	* @returns top_level nodes of the top level of the index
	*/
	static std::vector<Node*> create_index(std::vector<Point>& dataset, unsigned int L);

	/**
	* insert a collection of points into the cluster index
	* @param index_top_level index to insert points into
	* @param points collection of points to be inserted into the index
	* @param from_index index insertion starts from
	*/
	static std::vector<Node*> insert_points(std::vector<Node*>& index_top_level, std::vector<Point>& points, unsigned int from_index = 0);

	/**
	* find the nearest node to a query point
	* @param nodes vector of nodes to search through
	* @param query query point
	* @return pointer to the nearest node to the query point
	*/
	static Node* find_nearest_node(std::vector<Node*>& nodes, float*& query);

private:

	/**
	* recursively finds the nearest leaf to a query point from a level
	* @param query query point
	* @param node nearest node in current level
	* @param depth levels to go down
	* @return nearest leaf to query point
	*/
	static Node* find_nearest_leaf_from_level(float*& query, Node*& node, unsigned int depth);
};

#endif // PRE_PROCESSING_H
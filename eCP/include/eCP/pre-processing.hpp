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
  * Dontains functions for the preprocessing phase of the eCP algorithm.
  */
namespace pre_processing 
{
	/**
	* creates the cluster index from dataset and level parameter L
	* @param dataset collection of all points to be placed in the created index
	* @param L levels of the index
	* @returns top_level nodes of the top level of the index
	*/
  std::vector<Node> create_index(std::vector<Point>& dataset, unsigned L);

	/**
	* recursively finds the nearest leaf to a query point from a level
	* @param query query point
	* @param node nearest node in current level
	* @param depth levels to go down
	* @return nearest leaf to query point
	*/
  Node* find_nearest_leaf_from_level(float*& query, Node* node, unsigned depth);

	/**
	* find the nearest leaf given a query point regardless of level
	* @param query query point
	* @param nodes nodes
	* @return nearest leaf node to the query point
	*/
  Node* find_nearest_leaf(float*& query, std::vector<Node>& nodes);

	/**
	* insert a collection of points into the cluster index
	* @param index_top_level index to insert points into
	* @param points collection of points to be inserted into the index
	* @param from_index index insertion starts from
	*/
  std::vector<Node>& insert_points(std::vector<Node>& index_top_level, std::vector<Point>& points, unsigned from_index = 0);

}

#endif // PRE_PROCESSING_H

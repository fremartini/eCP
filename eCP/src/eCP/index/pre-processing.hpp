#ifndef PRE_PROCESSING_H
#define PRE_PROCESSING_H

#include <vector>
#include <eCP/index/shared/data_structure.hpp>

 /*
  * Dontains functions for the preprocessing phase of the eCP algorithm.
  */
namespace pre_processing 
{
	/**
	* creates the cluster index from dataset and level parameter L
  * @param dataset is the collection of all points to be placed in the created index
  * @param L the number of levels of the index
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
  * traverses index structure to find the leaf closest to the given query vector.
  * @param query is the query vector looking for a closest cluster.
  * @param nodes is the children list of any internal node in the index.
	* @return nearest leaf node to the query point
	*/
  Node* find_nearest_leaf(float*& query, std::vector<Node>& nodes);

  /**
   * @brief get_closest_node compares each node in nodes to query
   * and returns the one that is closest.
   * The function assumes that the vector of nodes is not empty.
   * @param nodes is a vector nodes.
   * @param query is the query feacture vector.
   * @return a pointer to the closest node.
   */
  Node* get_closest_node(std::vector<Node>& nodes, float* query);

	/**
	* insert a collection of points into the cluster index
	* @param index_top_level index to insert points into
	* @param points collection of points to be inserted into the index
	* @param from_index index insertion starts from
	*/
  std::vector<Node>& insert_points(std::vector<Node>& index_top_level, std::vector<Point>& points, unsigned from_index = 0);

}

#endif // PRE_PROCESSING_H

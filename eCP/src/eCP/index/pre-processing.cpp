#include <cmath>
#include <algorithm>

#include <iostream>
#include <eCP/index/pre-processing.hpp>
#include <eCP/index/query-processing.hpp>
#include <eCP/index/distance.hpp>
#include <eCP/index/globals.hpp>

namespace pre_processing 
{

/**
 * The data set is partitioned bottom up and the levels connected top down from the top level.
 */
std::vector<Node> create_index(std::vector<Point>& dataset, unsigned int L)
{
    unsigned int level_sizes[L];

    // Create levels from L..1 such that 0=root, 1=L2 etc.
    for (unsigned int i = L ; i > 0 ; --i) {
		unsigned int clusters = ceil(pow(dataset.size(), (i / (L + 1.00))));
        level_sizes[i - 1] = clusters;
    }

  // Build top level, using first n^(1/(L+1)) points of data set                                // Possible issue - leaders not picked randomly
  std::vector<Node> top_level;
	top_level.reserve(level_sizes[0]);                                                 

	for (unsigned int i = 0; i < level_sizes[0]; ++i)
	{
    top_level.emplace_back(Node{dataset[i]});                                                   // Should be picking random leaders here
	}
	top_level.shrink_to_fit();

  // Insert representatives in each level below L=1, i.e. forall L>1
  for (unsigned int level = 1; level < L; ++level) {
    const unsigned int avg_representatives = ceil(pow(dataset.size(), (1.00 / (L + 1.00))));                        // Each leaf cluster always represents, on average, n^( 1/(L+1) ) point

    for (unsigned int i = 0; i < level_sizes[level]; ++i) {                                                         // Add each representative for current level
      auto* top_level_nearest = distance::get_closest_node(top_level, dataset[i].descriptor);
      auto* lower_level_nearest = find_nearest_leaf_from_level(dataset[i].descriptor, top_level_nearest, level-1);  // -1 since top level has to be compared with

      auto node = Node{dataset[i]};                                                                                 // Setting representative to be dataset[i] here

      if (level == L-1) {
        node.points.reserve(avg_representatives);                                                                   // At bottom/leaf level
			}
			else {
        node.children.reserve(avg_representatives);                                                                 // Internal node in index
      }

      lower_level_nearest->children.emplace_back(node);
		}
	}

	return top_level;
}

/*
 * Only used during index creation. Current level is required since index is still being built.
 */
Node* find_nearest_leaf_from_level(float*& query, Node *node, unsigned int depth)
{
	//If at bottom level
  if (depth == 0) {
		return node;
	}

	// continue down to next level
  Node* nearest = distance::get_closest_node(node->children, query);
	return find_nearest_leaf_from_level(query, nearest, depth - 1);
}

// TODO: This simpler and more effective function is not correct while the tree is not constructed correctly.
// Correct would be: For every node there is a path through the tree that leads to a cluster.
Node* find_nearest_leaf(float*& query, std::vector<Node>& nodes)
{
  Node* closest_cluster = distance::get_closest_node(nodes, query);

  if (!closest_cluster->children.empty()) {
    return find_nearest_leaf(query, closest_cluster->children);
  }

  return closest_cluster;
}

/**
 * 
 */
//Node* find_nearest_leaf(float*& query, std::vector<Node>& nodes)
//{
//  Node* closest_cluster = distance::get_closest_node(nodes, query);
//  float closest_distance = globals::FLOAT_MAX;

//  for (Node node : closest_cluster->children) {
//    if (node.children.empty()) {
//      return distance::get_closest_node(closest_cluster->children, query);
//    }
//  std::cout << "GOTHERE" << std::endl;

//    const auto dist = distance::g_distance_function(query, node.points[0].descriptor);

//    if (dist < closest_distance)
//    {
//      closest_distance = dist;
//      closest_cluster = find_nearest_leaf(query, node.children);
//    }
//  }
//  return closest_cluster;
//}

std::vector<Node>& insert_points(std::vector<Node>& index_top_level, std::vector<Point>& points, unsigned int from_index)
{
  for (unsigned int i = from_index; i < points.size(); ++i) {
    Node* nearest = find_nearest_leaf(points[i].descriptor, index_top_level);
    nearest->points.emplace_back(points[i]);
	}
  return index_top_level;
}

}

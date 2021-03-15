#include <cmath>
#include <algorithm>

#include <eCP/pre-processing.hpp>
#include <eCP/query-processing.hpp>
#include <eCP/distance.hpp>
#include <eCP/globals.hpp>

namespace pre_processing 
{

/**
 * The data set is partitioned bottom up and the levels connected top down from the top level.
 */
std::vector<Node*> create_index(std::vector<Point>& dataset, unsigned int L)
{
    unsigned int level_sizes[L];

    // Create levels from L..1 such that 0=root, 1=L2 etc.
    for (unsigned int i = L ; i > 0 ; --i) {
		unsigned int clusters = ceil(pow(dataset.size(), (i / (L + 1.00))));
        level_sizes[i - 1] = clusters;
    }

  // Build top level, using first n^(1/(L+1)) points of data set                                // Possible issue - leaders not picked randomly
	std::vector<Node*> top_level;
	top_level.reserve(level_sizes[0]);                                                 

	for (unsigned int i = 0; i < level_sizes[0]; ++i)
	{
    top_level.emplace_back(new Node(dataset[i]));                                               // Should be picking random leaders here
	}
	top_level.shrink_to_fit();

  // Insert representatives in each level below L=1, i.e. forall L>1
	for (unsigned int level = 1; level < L; ++level) 
	{
    for (unsigned int i = 0; i < level_sizes[level]; ++i)                                       // Add each representative for current level
		{
			auto* top_level_nearest = distance::get_closest_node(top_level, dataset[i].descriptor);
      auto* lower_level_nearest =
          find_nearest_leaf_from_level(dataset[i].descriptor, top_level_nearest, level - 1);    // -1 since top level has to be compared with

      auto* node = new Node(dataset[i]);                                                        // Setting representative to be dataset[i] here
      const unsigned int avg_representatives = ceil(pow(dataset.size(), (1.00 / (L + 1.00))));  // Each leaf cluster always represents, on average, n^( 1/(L+1) ) point

			if (level == L - 1)                                     
			{
        node->points.reserve(avg_representatives);                                              // At bottom/leaf level
			}
			else 
			{
        node->children.reserve(avg_representatives);                                           // Internal node in index
			}

            lower_level_nearest->children.emplace_back(node);
		}
	}

	return top_level;
}

/*
 * Only used during index creation. Current level is required since index is still being built.
 */
Node* find_nearest_leaf_from_level(float*& query, Node*& node, unsigned int depth)
{
	//If at bottom level
	if (depth == 0)
	{
		return node;
	}

	// continue down to next level
	Node* nearest = distance::get_closest_node(node->children, query);
	return find_nearest_leaf_from_level(query, nearest, depth - 1);
}

/**
 * 
 */
Node* find_nearest_leaf(float*& query, std::vector<Node*>& nodes)
{
	Node* best_cluster = distance::get_closest_node(nodes, query);
	float closest = globals::FLOAT_MAX;

	for (Node* cluster : best_cluster->children)
	{
		if (cluster->children.empty())
		{
			return distance::get_closest_node(best_cluster->children, query);
		}

		const auto dist = distance::g_distance_function(query, cluster->points[0].descriptor);

		if (dist < closest)
		{
			closest = dist;
			best_cluster = find_nearest_leaf(query, cluster->children);
		}
	}
	return best_cluster;
}

std::vector<Node*> insert_points(std::vector<Node*>& index_top_level, std::vector<Point>& points, unsigned int from_index)
{
	for (unsigned int i = from_index; i < points.size(); ++i) 
	{
		Node* nearest = find_nearest_leaf(points[i].descriptor, index_top_level);

		nearest->points.push_back(points[i]);
	}
	return index_top_level;
}

}

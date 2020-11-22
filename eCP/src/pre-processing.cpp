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
    // Create levels from L..1 such that 0=root, 1=L2 etc.
    unsigned int level_sizes[L];

    for (unsigned int i = L ; i > 0 ; --i) {
		unsigned int clusters = ceil(pow(dataset.size(), (i / (L + 1.00))));               // Each level above
        level_sizes[i - 1] = clusters;
    }

	// Build top level, using first n^(1/(L+1)) points of data set                              // Possible issue - leaders not picked randomly
	std::vector<Node*> top_level;
	top_level.reserve(level_sizes[0]);                                                 

	for (unsigned int i = 0; i < level_sizes[0]; ++i)
	{
		top_level.emplace_back(new Node(dataset[i]));                                           // Should be picking random leaders here  
	}
	top_level.shrink_to_fit();

	// Insert empty clusters in each level to form index - skip already built top level
	for (unsigned int level = 1; level < L; ++level)
	{
		// Go through each level
		for (unsigned int i = 0; i < level_sizes[level]; ++i)
		{
			auto* upper_level_nearest = find_nearest_node(top_level, dataset[i].descriptor);    // Should be picking random leaders below where dataset[i] used

			// -1 since top level has been compared with
			auto* lower_level_nearest =
                find_nearest_leaf_from_level(dataset[i].descriptor, upper_level_nearest, level - 1);    

			//at bottom level
			if (level == L - 1)
			{
				auto* leaf = new Node(dataset[i]);
				//each leaf cluster always represents, on average, n^( 1/(L+1) ) point
				const unsigned int avg_rep = ceil(pow(dataset.size(), (1.00 / (L + 1.00))));
				leaf->points.reserve(avg_rep);
				lower_level_nearest->children.emplace_back(leaf);
			}
			else 
			{
				auto* node = new Node(dataset[i]);
				const unsigned int avg_rep = ceil(pow(dataset.size(), (1.00 / (L + 1.00))));
				node->children.reserve(avg_rep);
				lower_level_nearest->children.emplace_back(node);
			}
		}
	}

	return top_level;
}

std::vector<Node*> insert_points(std::vector<Node*>& index_top_level, std::vector<Point>& points, unsigned int from_index)
{
	for (unsigned int i = from_index; i < points.size(); ++i) 
	{
		Node* nearest = query_processing::find_nearest_leaf(points[i].descriptor, index_top_level);

		nearest->points.push_back(points[i]);
	}
	return index_top_level;
}

Node* find_nearest_node(std::vector<Node*>& nodes, float*& query)
{
	float nearest = globals::FLOAT_MAX;
	Node* best = nullptr;

	//compare distance to every representative
	for (auto* node : nodes)
	{
		const float distance = distance::g_distance_function(query, node->get_representative());
		if (distance <= nearest)
		{
			nearest = distance;
			best = node;
		}
	}
	return best;
}

/*
 * only used during index creation. Current level is required since index is still being built
 */
Node* find_nearest_leaf_from_level(float*& query, Node*& node, unsigned int depth)
{
	//If at bottom level
	if (depth == 0)
	{
		return node;
	}

	//continue down to next level
	Node* nearest = find_nearest_node(node->children, query);
	return find_nearest_leaf_from_level(query, nearest, depth - 1);
}

}
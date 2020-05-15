#include "eCP.hpp"
#include "pre-processing.hpp"
#include "query-processing.hpp"

/**
 * the data set is partitioned bottom up and the levels connected top down from the top level.
 */
std::vector<Node*> Pre_Processing::create_index(std::vector<Point>& dataset, unsigned int L)
{
	//get level size for each level
	std::vector<unsigned int> level_sizes;
	level_sizes.reserve(L);

	const auto initial_l = ceil(pow(dataset.size(), ((L / (L + 1.00)))));
	level_sizes.push_back(initial_l);

	for (unsigned int i = 1; i < L; ++i)
	{
		const auto level_l = ceil(pow(level_sizes[i - 1], (((L - i) / (L + 1.00)))));
		level_sizes.push_back(level_l);
	}
	level_sizes.shrink_to_fit();

	//build top level, using first n^(1/(L+1)) points of data set
	std::vector<Node*> top_level;

	top_level.reserve(level_sizes[level_sizes.size() - 1]);
	for (unsigned int i = 0; i < level_sizes[level_sizes.size() - 1]; ++i)
	{
		top_level.emplace_back(new Node(dataset[i]));
	}
	top_level.shrink_to_fit();

	//reverse level list for increasing level numbering
	reverse(level_sizes.begin(), level_sizes.end());

	//insert each level of clusters to form index - skip already built top level
	for (unsigned int level = 1; level < L; ++level)
	{
		//go through each level
		for (unsigned int i = 0; i < level_sizes[level]; ++i)
		{
			auto* upper_level_nearest = find_nearest_node(top_level, dataset[i].descriptor);
			// -1 since top level has been compared with
			auto* lower_level_nearest = find_nearest_leaf_from_level(dataset[i].descriptor, upper_level_nearest, level - 1);

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

std::vector<Node*> Pre_Processing::insert_points(std::vector<Node*>& index_top_level, std::vector<Point>& points, unsigned int from_index)
{
	for (unsigned int i = from_index; i < points.size(); ++i)
	{
		Node* nearest = Query_Processing::find_nearest_leaf(points[i].descriptor, index_top_level);

		nearest->points.push_back(points[i]);
	}
	return index_top_level;
}

Node* Pre_Processing::find_nearest_node(std::vector<Node*>& nodes, float*& query)
{
	float nearest = FLOAT_MAX;
	Node* best = nullptr;
	//compare distance to every representative
	for (auto* node : nodes)
	{
		const float distance = g_distance_function(query, node->get_representative());
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
Node* Pre_Processing::find_nearest_leaf_from_level(float*& query, Node*& node, unsigned int depth)
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
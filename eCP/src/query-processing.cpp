#include <climits>

#include <eCP/eCP.hpp>
#include <eCP/query-processing.hpp>
#include <eCP/pre-processing.hpp>

/*
 * recursively traverse the index to find the nearest leaf at the bottom level
 */
Node* Query_Processing::find_nearest_leaf(float*& query, std::vector<Node*>& nodes)
{
	Node* best_cluster = Pre_Processing::find_nearest_node(nodes, query);
	float closest = FLOAT_MAX;

	for (Node* cluster : best_cluster->children)
	{
		if (cluster->is_leaf())
		{
			return Pre_Processing::find_nearest_node(best_cluster->children, query);
		}

		const auto dist = g_distance_function(query, cluster->get_representative());
		if (dist < closest)
		{
			closest = dist;
			best_cluster = find_nearest_leaf(query, cluster->children);
		}
	}
	return best_cluster;
}

std::vector<std::pair<unsigned int, float>> Query_Processing::k_nearest_neighbors(std::vector<Node*>& root,
    float*& query, const unsigned int k, const unsigned int b = 1, unsigned int L = 1)
{
	//find b nearest clusters
	std::vector<Node*> b_nearest_clusters; //accumulator for b clusters
	b_nearest_clusters.reserve(b);
	b_nearest_clusters = find_b_nearest_clusters(root, query, b, L);

	//go trough b clusters to obtain k nearest neighbors
	std::vector<std::pair<unsigned int, float>> k_nearest_points;
	k_nearest_points.reserve(k);
	for (Node* b_nearest_cluster : b_nearest_clusters)
	{
		scan_leaf_node(query, b_nearest_cluster->points, k, k_nearest_points);
	}

	//sort by distance - O(N * log(N)) where N = smallest_distance(a,b) comparisons
	sort(k_nearest_points.begin(), k_nearest_points.end(), smallest_distance);

	return k_nearest_points;
}

/*
 * traverses node children one level at a time to find b nearest
 */
std::vector<Node*> Query_Processing::find_b_nearest_clusters(std::vector<Node*>& root, float*& query, unsigned int b, unsigned int L)
{
	std::vector<Node*> b_best;
	b_best.reserve(b);
	scan_node(query, root, b, b_best);

	//if L > 1 go down index, if L == 1 simply return the b_best
	while (L > 1)
	{
		std::vector<Node*> new_best_nodes;
		new_best_nodes.reserve(b);
		for (auto* node : b_best)
		{
			scan_node(query, node->children, b, new_best_nodes);
		}
		L = L - 1;
		b_best = new_best_nodes;
	}

	return b_best;
}

/*
 * scans a node, adding the nearer nodes to an accumulator
 */
void Query_Processing::scan_node(float*& query, std::vector<Node*>& nodes, unsigned int& b, std::vector<Node*>& next_level_nodes)
{
	std::pair<int, float> furthest_node = std::make_pair(-1, -1);

	//if we already have enough nodes to start replacing, find the furthest node
	if (next_level_nodes.size() >= b) furthest_node = find_furthest_node(query, next_level_nodes);

	for (Node* node : nodes)
	{
		//not enough nodes yet, just add
		if (next_level_nodes.size() < b)
		{
			next_level_nodes.emplace_back(node);

			//next iteration we will start replacing, compute the furthest cluster
			if (next_level_nodes.size() == b) furthest_node = find_furthest_node(query, next_level_nodes);
		}
		else
		{
			//only replace if better
			if (g_distance_function(query, node->get_representative()) < furthest_node.second) {
				next_level_nodes[furthest_node.first] = node;

				//the furthest node has been replaced, find the new furthest
				furthest_node = find_furthest_node(query, next_level_nodes);
			}
		}
	}
}

std::pair<int, float> Query_Processing::find_furthest_node(float*& query, std::vector<Node*>& nodes)
{
	std::pair<int, float> worst = std::make_pair(-1, -1);
	for (unsigned int i = 0; i < nodes.size(); i++) {
		const float dst = g_distance_function(query, nodes[i]->get_representative());

		if (dst > worst.second) {
			worst.first = i;
			worst.second = dst;
		}
	}

	return worst;
}

/*
 * uses an accumulator nearest_points to store the result
 */
void Query_Processing::scan_leaf_node(float*& query, std::vector<Point>& points, const unsigned int k,
    std::vector<std::pair<unsigned int, float>>& nearest_points)
{
	float max_distance = FLOAT_MAX;

	//if we already have enough points to start replacing, find the furthest point
	if (nearest_points.size() >= k) {
		max_distance = nearest_points[index_to_max_element(nearest_points)].second;
	}

	for (Point& point : points) {
		//not enough points yet, just add
		if (nearest_points.size() < k) {
			float dist = g_distance_function(query, point.descriptor);
			nearest_points.emplace_back(point.id, dist);

			//next iteration we will start replacing, compute the furthest cluster
			if (nearest_points.size() == k) {
                max_distance = nearest_points[index_to_max_element(nearest_points)].second;
            }
		}
		else {
			//only replace if nearer
			float dist = g_distance_function(query, point.descriptor);
			if (dist < max_distance) {
				const unsigned int max_index = index_to_max_element(nearest_points);
				nearest_points[max_index] = std::make_pair(point.id, dist);

				//the furthest point has been replaced, find the new furthest
				max_distance = nearest_points[index_to_max_element(nearest_points)].second;
			}
		}
	}
}

unsigned int Query_Processing::index_to_max_element(std::vector<std::pair<unsigned int, float>>& point_pairs)
{
    if (point_pairs.size() < 1) { throw std::range_error("Vector must contain at least one element."); }

    // Compare with first element
	int index = 0;
	int min = point_pairs[0].second;

    if (point_pairs.size() > 1) {
        for (unsigned int i = 1; i < point_pairs.size(); ++i) {
            if (point_pairs[i].second > min) {
                min = point_pairs[i].second;
                index = i;
            }
        }
    }

	return index;
}

/**
* used as predicate to sort for smallest distances
*/
bool Query_Processing::smallest_distance(std::pair<unsigned int, float>& a, std::pair<unsigned int, float>& b)
{
	return a.second < b.second;
}
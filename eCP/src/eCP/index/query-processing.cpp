#include <algorithm>
#include <stdexcept>

#include <eCP/index/query-processing.hpp>
#include <eCP/index/pre-processing.hpp>
#include <eCP/index/shared/distance.hpp>
#include <eCP/index/shared/globals.hpp>

/*
 * Traverse the index to find the nearest leaf at the bottom level.
 */
namespace query_processing 
{

std::vector<std::pair<unsigned int, float>> k_nearest_neighbors(std::vector<Node>& root, float*& query, const unsigned int k, const unsigned int b = 1, unsigned int L = 1)
{
  //find b nearest clusters
//  std::vector<Node> b_nearest_clusters; //accumulator for b clusters
//  b_nearest_clusters.reserve(b);
  std::vector<Node*> b_nearest_clusters = find_b_nearest_clusters(root, query, b, L);

  //go trough b clusters to obtain k nearest neighbors
  std::vector<std::pair<unsigned int, float>> k_nearest_points;
  k_nearest_points.reserve(k);
  for (Node* cluster : b_nearest_clusters)
  {
    scan_leaf_node(query, cluster->points, k, k_nearest_points);
  }

  //sort by distance - O(N * log(N)) where N = smallest_distance(a,b) comparisons
  sort(k_nearest_points.begin(), k_nearest_points.end(), smallest_distance);

  return k_nearest_points;
}

/*
 * Traverses node children one level at a time to find b nearest
 */
std::vector<Node*> find_b_nearest_clusters(std::vector<Node>& root, float*& query, unsigned int b, unsigned int L)
{
  // Scan nodes in root
  std::vector<Node*> b_best;
  b_best.reserve(b);
  scan_node(query, root, b, b_best);

  //if L > 1 go down index, if L == 1 simply return the b_best
  while (L > 1)
  {
    std::vector<Node*> new_best_nodes;
    new_best_nodes.reserve(b);
    for (auto *node : b_best)
    {
      scan_node(query, node->children, b, new_best_nodes);
    }
    L = L - 1;
    b_best = new_best_nodes;
  }

  return b_best;
}

/*
 * Compares vector of nodes to query and returns b closest nodes in given accumulator vector.
 */
void scan_node(float*& query, std::vector<Node>& nodes, unsigned int& b, std::vector<Node*>& nodes_accumulated)
{
  std::pair<int, float> furthest_node = std::make_pair(-1, -1.0);                                             // (index, distance from q to node)

  if (nodes_accumulated.size() >= b) {
    furthest_node = find_furthest_node(query, nodes_accumulated);   //if we already have enough nodes to start replacing, find the furthest node
  }

  for (Node& node : nodes) {
    if (nodes_accumulated.size() < b) {
      nodes_accumulated.emplace_back(&node);   //not enough nodes yet, just add

      if (nodes_accumulated.size() == b) {
        furthest_node = find_furthest_node(query, nodes_accumulated);   //next iteration we will start replacing, compute the furthest cluster
      }
    }

    else {
      //only replace if better
      if (distance::g_distance_function(query, node.points[0].descriptor) < furthest_node.second) {
        nodes_accumulated[furthest_node.first] = &node;
        furthest_node = find_furthest_node(query, nodes_accumulated);   //the furthest node has been replaced, find the new furthest
      }
    }
  }
}

/**
 * Goes through vector of nodes and returns the one furthest away from given query vector.
 * O(b) where b is requested number of clusters to do k-nn on.
 * Returns tuple containing (index, worst_distance)
 */
std::pair<int, float> find_furthest_node(float*& query, std::vector<Node*>& nodes)
{
  std::pair<int, float> worst = std::make_pair(-1, -1.0);

  for (unsigned int i = 0; i < nodes.size(); i++) {
    const float dst = distance::g_distance_function(query, nodes[i]->points[0].descriptor);

    if (dst > worst.second) {
      worst.first = i;
      worst.second = dst;
    }
  }

  return worst;
}

/*
 * Compares query point to each point in cluster and accumulates the k nearest points in 'nearest_points'.
 */
void scan_leaf_node(float*& query, std::vector<Point>& points, const unsigned int k, std::vector<std::pair<unsigned int, float>>& nearest_points)
{
  float max_distance = globals::FLOAT_MAX;

  //if we already have enough points to start replacing, find the furthest point
  if (nearest_points.size() >= k) {
    max_distance = nearest_points[index_to_max_element(nearest_points)].second;
  }

  for (Point& point : points) {
    //not enough points yet, just add
    if (nearest_points.size() < k) {
      float dist = distance::g_distance_function(query, point.descriptor);
      nearest_points.emplace_back(point.id, dist);

      //next iteration we will start replacing, compute the furthest cluster
      if (nearest_points.size() == k) {
        max_distance = nearest_points[index_to_max_element(nearest_points)].second;
      }
    }
    else {
      //only replace if nearer
      float dist = distance::g_distance_function(query, point.descriptor);
      if (dist < max_distance) {
        const unsigned int max_index = index_to_max_element(nearest_points);
        nearest_points[max_index] = std::make_pair(point.id, dist);

        //the furthest point has been replaced, find the new furthest
        max_distance = nearest_points[index_to_max_element(nearest_points)].second;
      }
    }
  }
}

// Assumes point_pairs contains at least 1 point.
unsigned index_to_max_element(std::vector<std::pair<unsigned int, float>>& point_pairs)
{
  int index = 0;
  float current_max = point_pairs[0].second;

  for (unsigned int i = 1; i < point_pairs.size(); ++i) {
    if (point_pairs[i].second > current_max) {
      current_max = point_pairs[i].second;
      index = i;
    }
  }

  return index;
}

/**
* Used as predicate to sort for smallest distances.
*/
bool smallest_distance(std::pair<unsigned int, float>& a, std::pair<unsigned int, float>& b)
{
  return a.second < b.second;
}

}

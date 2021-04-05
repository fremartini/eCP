#include <algorithm>
#include <cmath>
#include <eCP/index/pre-processing.hpp>
#include <eCP/index/query-processing.hpp>
#include <eCP/index/shared/distance.hpp>
#include <eCP/index/shared/globals.hpp>
#include <eCP/utilities/utilities.hpp>
#include <iostream>

/*
 * Namespace containing testable helpers used to build the index.
 */
namespace pre_processing_helpers {

/**
 * @brief generate_leaders_indexes generates a set of random indexes used to pick leaders
 * from each level. Since each level will use Nodes from the level below it, the indexes
 * for level L-1 is based on the size of level L.
 * @param dataset_size is the number of feature vectors in the the input dataset.
 * @param L is the number of levels to generate leader indexes for.
 * @return a vector of vectors containing randomly picked unsigned ints in the range
 * 0..size(level below).
 */
std::vector<std::vector<unsigned>> generate_leaders_indexes(std::size_t dataset_size, unsigned L)
{
  // Indexes picked randomly from input dataset used as leaders for each level
  std::vector<std::vector<unsigned>> random_leader_indexes(L);

  // Computing random indexes bottom-up, leader_indexes[0] is level 1.
  unsigned container_size = dataset_size;
  for (unsigned i = L; i > 0; --i) {
    // Calculate level sizes (i.e. how many clusters for level L)
    unsigned level_size = ceil(pow(dataset_size, (i / (L + 1.00))));

    // Pick random leaders for current level
    random_leader_indexes[i - 1].reserve(level_size);
    // FIXME: Time this to see if RVO or move/copy ctors are being utilized
    random_leader_indexes[i - 1] = utilities::get_random_unique_indexes(level_size, container_size);

    // Set to the size of current level, because indexes are found from the level below
    container_size = level_size;
  }

  return random_leader_indexes;
}

/**
 * @brief get_closest_node compares each node in nodes to query and returns a pointer to the closest one.
 * It is assumed that the vector of nodes is not empty.
 * @param nodes is a vector nodes.
 * @param query is the query feacture vector.
 * @return a pointer to the closest node.
 */
Node* get_closest_node(std::vector<Node>& nodes, const float* query)
{
  float max = globals::FLOAT_MAX;
  Node* closest = nullptr;

  for (Node& node : nodes) {
    const float distance = distance::g_distance_function(query, node.get_leader()->descriptor, max);

    if (distance < max) {
      max = distance;
      closest = &node;
    }
  }
  return closest;
}

/**
 * @brief find_nearest_leaf traverses the index recursively to find the leaf closest to the given query
 * vector.
 * @param query is the query vector looking for a closest cluster.
 * @param nodes is the children vector of any internal node in the index.
 * @return the nearest leaf (Node) to the given query point.
 */
Node* find_nearest_leaf(const float* query, std::vector<Node>& nodes)
{
  Node* closest_cluster = get_closest_node(nodes, query);

  if (!closest_cluster->children.empty()) {
    return find_nearest_leaf(query, closest_cluster->children);
  }

  return closest_cluster;
}

}  // namespace pre_processing_helpers

namespace pre_processing {
/*
 * This function will create an index by a 3-step process:
 * 1) Random indexes used to pick leaders are generated for each level.
 * 2) The index is built bottom-up. Each level is constructed from the level below.
 * Initially the bottom level L is constructed from the input dataset. Then level L-1 is constructed
 * similarly, but from nodes from level L. Now all nodes from level L are added to level L-1 using
 * the distance function to place them correctly. This process repeats for all levels up to and
 * inclusive level 1.
 * 3) All input vectors are added to the index except those that are already there due to
 * the Node ctor adding the leader to the Points vector.
 */
std::vector<Node> create_index(const std::vector<std::vector<float>>& dataset, unsigned int L)
{
  // ** 1)
  // Each cluster will represent on average, n^( 1/(L+1) ) points
  const unsigned int average_cluster_size = ceil(pow(dataset.size(), (1.00 / (L + 1.00))));
  // FIXME: Assert that RVO is being used
  const auto random_leader_indexes = pre_processing_helpers::generate_leaders_indexes(dataset.size(), L);

  // ** 2)
  std::vector<Node> previous_level;  // Used to maintain the level below when building current level
  // Using reverse_iterator because we need to start with bottom level
  for (auto it = random_leader_indexes.rbegin(); it != random_leader_indexes.rend(); ++it) {
    std::vector<Node> current_level;
    current_level.reserve(it->size());  // Allocate for already known number of leaders

    // Only for bottom level L
    if (previous_level.size() == 0) {
      for (auto index : *it) {
        // Pick from input dataset using index as Id of Point
        auto cluster = Node{Point{dataset[index].data(), index}};
        cluster.points.reserve(average_cluster_size);  // Allocate initial size of cluster
        current_level.emplace_back(std::move(cluster));
      }
    }

    // For all levels above L (i.e. L-1...1)
    else {
      for (auto index : *it) {
        // Pick previously randomly found nodes from level below to construct current level
        auto* node = &previous_level[index];
        // Reconstruct Node to not copy children/points into current level
        current_level.emplace_back(Node{Point{*node->get_leader()}});
      }

      // Add all nodes from below level as children of current level
      for (auto node : previous_level) {
        pre_processing_helpers::get_closest_node(current_level, node.get_leader()->descriptor)
            ->children.emplace_back(std::move(node));
      }
    }

    previous_level.swap(current_level);
  }

  // ** 3)
  // Add all points from input dataset to the index incl those duplicated in the index construction.
  unsigned id{0};
  for (auto& descriptor : dataset) {
    // FIXME: Optional optimization: Use a set to contain all leader id's. Then we don't have to call distance
    // function for those.
    auto* leaf = pre_processing_helpers::find_nearest_leaf(descriptor.data(), previous_level);
    // Because the leader was added to the cluster when the index was built
    if (id != leaf->get_leader()->id) {
      leaf->points.emplace_back(Point{descriptor.data(), id});
    }
    id++;
  }

  return previous_level;
}

}  // namespace pre_processing

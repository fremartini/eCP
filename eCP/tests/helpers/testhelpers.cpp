#include <helpers/testhelpers.hpp>

namespace testhelpers {

unsigned measure_depth_from(Node root)
{
  if (!root.children.empty()) {
    return 1 + measure_depth_from(root.children[0]);
  }
  return 0;
}

unsigned count_points_in_clusters(Node root)
{
  unsigned total{0};

  if (root.children.empty()) {
    return root.points.size();
  }
  else {
    for (auto& node : root.children) {
      total += count_points_in_clusters(node);
    }
  }
  return total;
}

unsigned count_clusters(Node root, unsigned parent_children)
{
  if (!root.children.empty()) {
    for (auto& node : root.children) {
      return 0 + count_clusters(node, root.children.size());
    }
  }
  return parent_children;
}

}  // namespace testhelpers

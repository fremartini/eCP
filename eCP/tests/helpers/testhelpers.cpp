#include <helpers/testhelpers.hpp>

namespace testhelpers {

unsigned measure_depth(Node root) {
  if (!root.children.empty()) {
    return 1 + measure_depth(root.children[0]);
  }
  return 1;
}

}

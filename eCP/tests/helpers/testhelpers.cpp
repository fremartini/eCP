#include <helpers/testhelpers.hpp>

namespace testhelpers {

unsigned measure_depth(Node root) {
  if (!root.children.empty()) {
    return 1 + measure_depth(root.children[0]);
  }

//  while (!root[0].children.empty()) {
//    ++d;
//    root = root[0].children;
//  }
  return 1;
}

}

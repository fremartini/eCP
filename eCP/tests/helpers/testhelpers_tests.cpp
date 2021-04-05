#include <gtest/gtest.h>
#include <helpers/testhelpers.hpp>
#include <eCP/index/shared/data_structure.hpp>

TEST(testhelpers_tests, measure_depth_given_vector_containing_1_levels_returns_1) {
  globals::g_vector_dimensions = 3;
  auto dummy = Point{new float[3] {2,2,2}, 2};

  Node root{dummy};

  auto result = testhelpers::measure_depth_from(root);

  EXPECT_EQ(result, 0);   // unrealistic as a root node will contain a vector of children == level 1
}

TEST(testhelpers_tests, measure_depth_given_vector_containing_2_levels_returns_2) {
  globals::g_vector_dimensions = 3;
  auto dummy = Point{new float[3] {2,2,2}, 2};

  Node node{dummy};
  Node root{dummy};
  root.children.emplace_back(node);

  auto result = testhelpers::measure_depth_from(root);

  EXPECT_EQ(result, 1);   // 1 children vector == level 1
}

TEST(testhelpers_tests, measure_depth_given_vector_containing_3_levels_returns_3) {
  globals::g_vector_dimensions = 3;
  auto dummy = Point{new float[3] {2,2,2}, 2};

  Node root{dummy};
  Node node1{dummy};
  Node node2{dummy};

  node1.children.emplace_back(node2);
  root.children.emplace_back(node1);

  auto result = testhelpers::measure_depth_from(root);

  EXPECT_EQ(result, 2);   // 2 levels b/c 2 levels of children vectors
}

TEST(testhelpers_tests, count_points_in_clusters_with_L2_with_2_cluster_with_1_point_each_returns_2) {
  globals::g_vector_dimensions = 3;
  auto p1 = Point{new float[3] {1,1,1}, 1};
  auto pa = Point{new float[3] {2,2,2}, 2};
  auto pb = Point{new float[3] {3,4,3}, 3};

  Node root{p1};
  Node level2a{pa};
  Node level2b{pb};
  level2a.points.emplace_back(pa);  // duplicate point in cluster
  level2b.points.emplace_back(pb);  // duplicate point in cluster
  root.children.emplace_back(level2a);
  root.children.emplace_back(level2b);

  auto result = testhelpers::count_points_in_clusters(root);

  EXPECT_EQ(result, 4);
}

TEST(testhelpers_tests, count_points_in_clusters_given_single_element_child_list_with_2_points_in_clusters_return_2) {
  globals::g_vector_dimensions = 3;
  auto p1 = Point{new float[3] {1,1,1}, 1};
  auto p2= Point{new float[3] {2,2,2}, 2};

  Node root{p1};
  root.points.emplace_back(p2);

  auto result = testhelpers::count_points_in_clusters(root);

  EXPECT_EQ(result, 2);
}

TEST(testhelpers_tests, count_points_in_clusters_given_L_3_index_with_4_points_return_4) {
  // arrange
  globals::g_vector_dimensions = 3;
  auto dummy = Point{new float[3] {2,2,2}, 2};

  Node level1{dummy};
  Node level2{dummy};
  Node level3{dummy};

  level3.points.emplace_back(Point{dummy}); // add 3 points
  level3.points.emplace_back(Point{dummy});
  level3.points.emplace_back(Point{dummy});

  level2.children.emplace_back(level3);   // add lvl 3
  level1.children.emplace_back(level2);   // add lvl 2

  // act
  // Result = leader + 3 added points = 4
  auto result = testhelpers::count_points_in_clusters(level1);

  // assert
  EXPECT_EQ(result, 4);
}

TEST(testhelpers_tests, count_clusters_given_index_with_3_nodes_at_bottom_level_returns_3) { // bottom level == clusters
  // arrange
  globals::g_vector_dimensions = 3;
  auto dummy = Point{new float[3] {2,2,2}, 2};

  Node level1{dummy};
  Node level2{dummy};
  Node level3{dummy};

  level2.children.emplace_back(Node{level3});   // add cluster
  level2.children.emplace_back(Node{level3});   // add cluster
  level2.children.emplace_back(Node{level3});   // add cluster
  level1.children.emplace_back(level2);   // add lvl 2

  // act
  auto result = testhelpers::count_clusters(level1);

  // assert
  EXPECT_EQ(result, 3);
}

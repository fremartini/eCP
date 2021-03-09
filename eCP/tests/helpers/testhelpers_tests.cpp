#include <gtest/gtest.h>
#include <helpers/testhelpers.hpp>
#include <eCP/index/shared/data_structure.hpp>

TEST(testhelpers_tests, measure_depth_given_vector_containing_1_levels_returns_1) {
  globals::g_vector_dimensions = 3;
  Point dummy{Point{new float[3] {2,2,2}, 2}};

  Node root{dummy};

  auto result = testhelpers::measure_depth(root);

  EXPECT_EQ(result, 1);
}

TEST(testhelpers_tests, measure_depth_given_vector_containing_2_levels_returns_2) {
  globals::g_vector_dimensions = 3;
  Point dummy{Point{new float[3] {2,2,2}, 2}};

  Node node{dummy};
  Node root{dummy};
  root.children.emplace_back(node);

  auto result = testhelpers::measure_depth(root);

  EXPECT_EQ(result, 2);
}

TEST(testhelpers_tests, measure_depth_given_vector_containing_3_levels_returns_3) {
  globals::g_vector_dimensions = 3;
  Point dummy{Point{new float[3] {2,2,2}, 2}};

  Node node1{dummy};
  Node node2{dummy};
  node1.children.emplace_back(node2);

  Node root{dummy};
  root.children.emplace_back(node1);

  auto result = testhelpers::measure_depth(root);

  EXPECT_EQ(result, 3);
}


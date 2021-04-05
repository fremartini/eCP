#include <gtest/gtest.h>

#include <eCP/index/shared/distance.hpp>
#include <eCP/index/shared/globals.hpp>
#include <helpers/testhelpers.hpp>

// Because we need to test functions only part of the compilation unit
#include <eCP/index/pre-processing.cpp>

/*
 * pre_processing_tests
 */

TEST(pre_processing_tests, create_index_given_dataset_and_L_2_leaders_returns_correct_depth_of_index)
{
  // arrange
  auto dataset_size = 4;
  unsigned L = 2;
  distance::set_distance_function(distance::Metric::EUCLIDEAN_OPT_UNROLL);
  globals::g_vector_dimensions = 3;

  // act
  std::vector<std::vector<float>> dataset{
      {1, 2, 3},
      {4, 5, 6},
      {7, 8, 9},
      {10, 11, 12},
  };

  auto leader_indexes = pre_processing_helpers::generate_leaders_indexes(dataset_size, L);
  auto first_level = pre_processing::create_index(dataset, L);

  auto root =
      Node{Point{{3, 3, 3}, 100}};  // FIXME: Remove this when the index uses a single Node as root node
  root.children.swap(first_level);

  auto result = testhelpers::measure_depth_from(root);

  // assert
  ASSERT_EQ(result, 2);
}

TEST(pre_processing_tests,
     create_index_given_dataset_with_L_2_leaders_4_points_builds_index_and_fills_clusters_with_4_points)
{
  // arrange
  auto dataset_size = 4;
  unsigned L = 2;
  distance::set_distance_function(distance::Metric::EUCLIDEAN_OPT_UNROLL);
  globals::g_vector_dimensions = 3;

  std::vector<std::vector<float>> dataset{
      {1, 2, 3},
      {4, 5, 6},
      {7, 8, 9},
      {10, 11, 12},
  };

  // act
  auto leader_indexes = pre_processing_helpers::generate_leaders_indexes(dataset_size, L);
  auto first_level = pre_processing::create_index(dataset, L);

  auto root =
      Node{Point{{3, 3, 3}, 100}};  // FIXME: Remove this when the index uses a single Node as root node
  root.children.swap(first_level);

  auto result = testhelpers::count_points_in_clusters(root);

  // assert
  ASSERT_EQ(result, 4);
}

// FIXME: All of these tests need to be re-implemented

/* Helpers */
// std::vector<Node> get_empty_index(unsigned int L = 2)
//{
//    std::vector<Point> S = {
//        Point(new float[3] {1, 1, 1}, 0),
//        Point(new float[3] {4, 4, 4}, 1),
//        Point(new float[3] {2, 2, 2}, 2),
//        Point(new float[3] {12, 12, 12}, 3),
//        Point(new float[3] {3, 3, 3}, 4),
//        Point(new float[3] {9, 9, 9}, 5),
//        Point(new float[3] {5, 5, 5}, 6),
//        Point(new float[3] {20, 20, 20}, 7),
//        Point(new float[3] {17, 17, 17}, 8),
//        Point(new float[3] {7, 7, 7}, 9),
//        Point(new float[3] {10, 10, 10}, 10),
//    };

//    return pre_processing::create_index(S, L);
//};

/* Tests */

// TEST(pre_processing_tests, create_index_bottom_up_creates_empty_datastructure) {
//    distance::set_distance_function(distance::Metrics::EUCLIDEAN_OPT_UNROLL);
//    globals::g_vector_dimensions = 3;

//    std::vector<Point> S = {
//        Point(new float[3] {1, 1, 1}, 0),
//        Point(new float[3] {4, 4, 4}, 1),
//        Point(new float[3] {2, 2, 2}, 2),
//        Point(new float[3] {3, 3, 3}, 3),
//        Point(new float[3] {9, 9, 9}, 4),
//        Point(new float[3] {6, 6, 6}, 5)
//    };
//    unsigned int L = 1;

//    auto root = pre_processing::create_index(S, L);

//    EXPECT_TRUE(root.size() != 0);

//    for (Node &cluster : root) {
//        EXPECT_TRUE(cluster.children.size() == 0);
//        EXPECT_TRUE(cluster.points.size() == 1);
//    }
//}

// FIXME: Rewrite this test
// TEST(pre_processing_tests, insert_points_given_empty_index_inserts_points) {
//    distance::set_distance_function(distance::Metrics::EUCLIDEAN_OPT_UNROLL);
//    globals::g_vector_dimensions = 3;

//    std::vector<Node> root = get_empty_index(1);

//    std::vector<Point> descriptors = {
//        Point(new float[3] {2, 2, 2}, 0),
//        Point(new float[3] {9, 9, 9}, 1),
//        Point(new float[3] {4, 4, 4}, 2),
//        Point(new float[3] {1, 1, 1}, 3),
//        Point(new float[3] {12, 12, 12}, 4),
//        Point(new float[3] {17, 17, 17}, 5),
//        Point(new float[3] {5, 5, 5}, 6),
//        Point(new float[3] {3, 3, 3}, 7),
//        Point(new float[3] {20, 20, 20}, 8),
//        Point(new float[3] {7, 7, 7}, 9),
//        Point(new float[3] {10, 10, 10}, 10)
//    };

//    std::vector<Node> actual = pre_processing::insert_points(root, descriptors);

//    for (auto cluster : actual) {
//        for (auto leaf : cluster.children) {
//            EXPECT_TRUE(leaf.points.size() != 0);
//        }
//    }
//}

/*
 * pre-processing_helpers_tests
 */

TEST(pre_processing_helpers_tests,
     generate_leaders_indexes_given_dataset_12_L_3_returns_correct_number_for_each_level)
{
  auto dataset_size = 12;
  auto L = 3;

  auto leader_indexes = pre_processing_helpers::generate_leaders_indexes(dataset_size, L);

  ASSERT_EQ(leader_indexes[0].size(), 2);  // 1st level
  ASSERT_EQ(leader_indexes[1].size(), 4);  // 2nd level
  ASSERT_EQ(leader_indexes[2].size(), 7);  // 3rd level
}

TEST(pre_processing_helpers_tests, get_closest_node_returns_closest_cluster)
{
  distance::set_distance_function(distance::Metric::EUCLIDEAN_OPT_UNROLL);
  globals::g_vector_dimensions = 3;

  std::vector<Node> clusters{
      Node{Point(new float[3]{1, 1, 1}, 0)},
      Node{Point(new float[3]{4, 4, 4}, 1)},
      Node{Point(new float[3]{7, 7, 7}, 2)},
      Node{Point(new float[3]{8, 8, 8}, 3)},
  };

  float* query = new float[3]{3, 3, 3};

  float expected[3] = {4, 4, 4};
  Node* actual = pre_processing_helpers::get_closest_node(clusters, query);

  EXPECT_EQ(*actual->points[0].descriptor, *expected);
}

TEST(pre_processing_helpers_tests, get_closest_node_given_query_in_clusters_returns_same)
{
  distance::set_distance_function(distance::Metric::EUCLIDEAN_OPT_UNROLL);
  globals::g_vector_dimensions = 3;

  std::vector<Node> clusters = {
      Node{Point{new float[3]{1, 1, 1}, 0}},
      Node(Point(new float[3]{4, 4, 4}, 1)),
      Node(Point(new float[3]{7, 7, 7}, 2)),
      Node(Point(new float[3]{8, 8, 8}, 3)),
  };

  float* query = new float[3]{8, 8, 8};

  float expected[3] = {8, 8, 8};
  Node* actual = pre_processing_helpers::get_closest_node(clusters, query);

  EXPECT_EQ(*actual->points[0].descriptor, *expected);
}

TEST(pre_processing_helpers_tests, find_nearest_leaf_finds_nearest_cluster_in_2_level_index)
{
  distance::set_distance_function(distance::Metric::EUCLIDEAN_OPT_UNROLL);
  globals::g_vector_dimensions = 3;

  std::vector<Node> clusters = {
      Node{Point{new float[3]{10, 10, 10}, 10}},
      Node(Point(new float[3]{100, 100, 100}, 100)),
      Node(Point(new float[3]{1000, 1000, 1000}, 1000)),
      Node(Point(new float[3]{10'000, 10'000, 10'000}, 10'000)),
  };

  Point p1{Point{new float[3]{2, 2, 2}, 2}};
  Point p2{Point{new float[3]{900, 900, 900}, 900}};
  Node node1{p1};
  Node node2{p2};

  node2.children = clusters;
  std::vector<Node> l1 = {node1, node2};

  float* query = new float[3]{999, 999, 999};
  float* expected = clusters[2].points[0].descriptor;

  Node* actual = pre_processing_helpers::find_nearest_leaf(query, l1);

  EXPECT_EQ(*actual->points[0].descriptor, *expected);
}

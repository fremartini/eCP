#include <gtest/gtest.h>

#include <eCP/eCP.hpp>
#include <eCP/query-processing.hpp>
#include <eCP/distance.hpp>
#include <eCP/globals.hpp>

/* Helpers */
Index *get_index(unsigned int L, int descriptors_amount = 10)
{
    std::vector<std::vector<float>> descriptors;

    for (int i = 0; i < descriptors_amount + 1; i++)
    {
        descriptors.push_back({(float)i, (float)i, (float)i});
    }

    Index *index = eCP::eCP_Index(descriptors, L, 0);
    return index;
};

/* Tests */

TEST(query_processing_tests, index_to_max_element_given_positive_valued_single_pair_returns_pair_index)
{
    // (idx, value)
    std::vector<std::pair<unsigned int, float>> point_pairs{
        {2, 2.0}};

    auto result = query_processing::index_to_max_element(point_pairs);

    auto expected_index{0};
    auto actual_index = result;

    EXPECT_EQ(expected_index, actual_index);
}

TEST(query_processing_tests, index_to_max_element_given_int_zero_returns_correct_index)
{
    // (idx, value)
    std::vector<std::pair<unsigned int, float>> point_pairs{
        {0, 0.0}};

    auto result = query_processing::index_to_max_element(point_pairs);

    int expected_index{0};
    int actual_index = result;

    EXPECT_TRUE(expected_index == actual_index);
}

TEST(query_processing_tests, index_to_max_element_given_morethan_elem_returns_index_with_highest_value)
{
    // (idx, value)
    std::vector<std::pair<unsigned int, float>> point_pairs{
        {0, 0.0},
        {0, 3.0},
        {0, 2.0},
        {0, 1.0}};

    auto result = query_processing::index_to_max_element(point_pairs);

     int expected_index{1};
     int actual_index = result;

    EXPECT_TRUE(expected_index == actual_index);
}

TEST(query_processing_tests, index_to_max_element_given_vector_with_zero_elems_throws)
{
    std::vector<std::pair<unsigned int, float>> point_pairs;
    EXPECT_THROW(query_processing::index_to_max_element(point_pairs), std::range_error);
}

TEST(query_processing_tests, find_k_nearest_points_given_k_1_returns_k_closest_points)
{
    distance::set_distance_function(distance::Metrics::EUCLIDEAN);
    globals::g_vector_dimensions = 3;

    std::vector<Node> root = {
        Node{Point(new float[3]{1, 1, 1}, 0)},
        Node{Point(new float[3]{3, 3, 3}, 1)},
        Node{Point(new float[3]{4, 4, 4}, 2)},
        Node{Point(new float[3]{6, 6, 6}, 3)},
        Node{Point(new float[3]{9, 9, 9}, 4)},
    };

    float *q = new float[3]{4, 4, 4};
    unsigned int k = 1;
    unsigned int b = 1;
    unsigned int L = 1;

    auto actual = query_processing::k_nearest_neighbors(root, q, k, b, L);

    EXPECT_TRUE(actual.size() == 1);
    EXPECT_TRUE(actual[0].first == 2);
    EXPECT_TRUE(actual[0].second == 0);
}

TEST(query_processing_tests, find_k_nearest_points_given_k_2_returns_k_closest_points)
{
    distance::set_distance_function(distance::Metrics::EUCLIDEAN);
    globals::g_vector_dimensions = 3;

    std::vector<Node> root = {
        Node{Point(new float[3]{1, 1, 1}, 0)},
        Node{Point(new float[3]{3, 3, 3}, 1)},
        Node{Point(new float[3]{4, 4, 4}, 2)},
        Node{Point(new float[3]{6, 6, 6}, 3)},
        Node{Point(new float[3]{9, 9, 9}, 4)},
    };

    float *q = new float[3]{4, 4, 4};
    unsigned int k = 2;
    unsigned int b = root.size();
    unsigned int L = 1;

    auto actual = query_processing::k_nearest_neighbors(root, q, k, b, L);

    EXPECT_TRUE(actual.size() == 2);
    EXPECT_TRUE(actual[0].first == 2);
    EXPECT_TRUE(actual[0].second == 0);
    EXPECT_TRUE(actual[1].first == 1);
    EXPECT_TRUE(actual[1].second == 3);
}

TEST(query_processing_tests, find_b_nearest_clusters_given_l_b_1_returns_single_closest_cluster)
{
    float *query = new float[3]{3, 3, 3};
    unsigned int b = 1;
    unsigned int L = 1;

    std::vector<Node> root = {
        Node{Point(new float[3]{1, 1, 1}, 0)},
        Node{Point(new float[3]{3, 3, 3}, 1)},
        Node{Point(new float[3]{4, 4, 4}, 2)},
        Node{Point(new float[3]{6, 6, 6}, 3)},
        Node{Point(new float[3]{9, 9, 9}, 4)},
    };

    auto actual = query_processing::find_b_nearest_clusters(root, query, b, L);

    EXPECT_TRUE(actual.size() == b);
    EXPECT_TRUE(*actual[0]->points[0].descriptor == *query);
}

TEST(query_processing_tests, find_b_nearest_clusters_given_l_2_b_2_returns_2_closest_cluster)
{
    float *query = new float[3]{9, 9, 9};
    unsigned int b = 2;
    unsigned int L = 2;

    std::vector<Node> top_level = get_index(L, 42)->top_level;

    auto actual = query_processing::find_b_nearest_clusters(top_level, query, b, L);

    EXPECT_TRUE(actual.size() == b);
    EXPECT_TRUE(*actual[1]->points[0].descriptor == *query);
}

TEST(query_processing_tests, scan_node_children_given_b_1_returns_identical_closest_element)
{
    distance::set_distance_function(distance::Metrics::EUCLIDEAN);
    globals::g_vector_dimensions = 3;

    float *query = new float[3]{3, 3, 3};
    unsigned int b = 1;

    std::vector<Node> root = {
        Node{Point(new float[3]{1, 1, 1}, 0)},
        Node{Point(new float[3]{3, 3, 3}, 1)},
        Node{Point(new float[3]{4, 4, 4}, 2)},
        Node{Point(new float[3]{6, 6, 6}, 3)},
        Node{Point(new float[3]{9, 9, 9}, 4)},
    };

    std::vector<Node*> next_level_best_nodes = {};

    query_processing::scan_node(query, root, b, next_level_best_nodes);

    float *expected = new float[3]{3, 3, 3};

    EXPECT_TRUE(next_level_best_nodes.size() == b);
    EXPECT_TRUE(*next_level_best_nodes[0]->points[0].descriptor == *expected);
    delete[] expected;  // circumventing possible leak-warning.
}

TEST(query_processing_tests, scan_node_given_children_less_than_b_returns_everything)
{
    distance::set_distance_function(distance::Metrics::EUCLIDEAN);
    globals::g_vector_dimensions = 3;

    float *query = new float[3]{3, 3, 3};
    unsigned int b = 4;

    std::vector<Node> root = {
        Node{Point(new float[3]{1, 1, 1}, 0)},
        Node{Point(new float[3]{3, 3, 3}, 1)},
        Node{Point(new float[3]{4, 4, 4}, 2)},
    };

    std::vector<Node*> next_level_best_nodes = {};

    query_processing::scan_node(query, root, b, next_level_best_nodes);

    EXPECT_TRUE(next_level_best_nodes.size() == root.size());
}

TEST(query_processing_tests, scan_node_given_b_2_returns_two_closest_elements)
{
    distance::set_distance_function(distance::Metrics::EUCLIDEAN);
    globals::g_vector_dimensions = 3;

    float *query = new float[3]{1, 1, 1};
    unsigned int b = 2;

    std::vector<Node> root = {
        Node{Point(new float[3]{1, 1, 1}, 0)},
        Node{Point(new float[3]{3, 3, 3}, 1)},
        Node{Point(new float[3]{4, 4, 4}, 2)},
        Node{Point(new float[3]{6, 6, 6}, 3)},
        Node{Point(new float[3]{9, 9, 9}, 4)},
    };

    std::vector<Node*> next_level_best_nodes = {};

    query_processing::scan_node(query, root, b, next_level_best_nodes);

    float *first_element = new float[3]{1, 1, 1};
    float *second_element = new float[3]{3, 3, 3};

    EXPECT_TRUE(next_level_best_nodes.size() == b);
    EXPECT_TRUE(*next_level_best_nodes[0]->points[0].descriptor == *first_element);
    EXPECT_TRUE(*next_level_best_nodes[1]->points[0].descriptor == *second_element);
}

#include <gtest/gtest.h>

#include <eCP/eCP.hpp>
#include <eCP/query-processing.hpp>

/* Helpers */
Index get_index(unsigned int L) {
    std::vector<std::vector<float>> descriptors;

    for (unsigned int i = 0; i < 100; i++) {
        descriptors.push_back({ (float)i, (float)i, (float)i });
    }

    return *eCP_Index(descriptors, L, 0);
};

/* Tests */

TEST(query_processing_tests, index_to_max_element_given_positive_valued_single_pair_returns_pair_index)
{
    // (idx, value)
    std::vector<std::pair<unsigned int, float>> point_pairs {
        {2, 2.0}
    };

    auto result = Query_Processing::index_to_max_element(point_pairs);

    auto expected_index {0};
    auto actual_index = result;

    EXPECT_EQ(expected_index, actual_index);
}

TEST(query_processing_tests, index_to_max_element_given_int_zero_returns_correct_index)
{
    // (idx, value)
    std::vector<std::pair<unsigned int, float>> point_pairs {
        {0, 0.0}
    };

    auto result = Query_Processing::index_to_max_element(point_pairs);

    auto expected_index {0};
    auto actual_index = result;

    EXPECT_TRUE(expected_index == actual_index);
}

TEST(query_processing_tests, index_to_max_element_given_morethan_elem_returns_index_with_highest_value)
{
    // (idx, value)
    std::vector<std::pair<unsigned int, float>> point_pairs {
        {0, 0.0},
        {0, 3.0},
        {0, 2.0},
        {0, 1.0}
    };

    auto result = Query_Processing::index_to_max_element(point_pairs);

    auto expected_index {1};
    auto actual_index = result;

    EXPECT_TRUE(expected_index == actual_index);
}

TEST(query_processing_tests, index_to_max_element_given_vector_with_zero_elems_throws)
{
    std::vector<std::pair<unsigned int, float>> point_pairs;
    EXPECT_THROW(Query_Processing::index_to_max_element(point_pairs), std::range_error);
}

TEST(query_processing_tests, find_k_nearest_points_given_k_1_returns_k_closest_points)
{
    g_distance_function = &euclidean_distance;
    g_vector_dimensions = 3;

    float* q = new float[3]{ 4, 4, 4 };
    std::vector<Node*> root = {
        new Node{Point(new float[3]{1, 1, 1}, 0)},
        new Node{Point(new float[3]{3, 3, 3}, 1)},
        new Node{Point(new float[3]{4, 4, 4}, 2)},
        new Node{Point(new float[3]{6, 6, 6}, 3)},
        new Node{Point(new float[3]{9, 9, 9}, 4)},
    };

    std::uint32_t k = 1;
    std::uint32_t b = 1;
    std::uint32_t L = 1;

    auto actual = Query_Processing::k_nearest_neighbors(root, q, k, b, L);

    EXPECT_TRUE(actual.size() == 1);
    EXPECT_TRUE(actual[0].first == 2);
    EXPECT_TRUE(actual[0].second == 0);
}
	//
	//		TEST_METHOD(find_k_nearest_points_given_k_2_returns_k_closest_points) {
	//			g_distance_function = &euclidean_distance;
	//			g_vector_dimensions = 3;
	//
	//			float* q = new float[3]{ 4, 4, 4 };
	//			std::vector<Point> points = {
	//				Point(new float[3]{1, 1, 1}, 0),
	//				Point(new float[3]{3, 3, 3}, 1),
	//				Point(new float[3]{4, 4, 4}, 2),
	//				Point(new float[3]{6, 6, 6}, 3),
	//				Point(new float[3]{9, 9, 9}, 4),
	//			};
	//
	//			unsigned int k = 2;
	//
	//			auto actual = find_k_nearest_points(q, points, k);
	//
	//			Assert::IsTrue(actual.size() == 2);
	//
	//			Assert::IsTrue(actual[0].first == 2);
	//			Assert::IsTrue(actual[1].first == 1);
	//			Assert::IsTrue(actual[0].second == 0);
	//		}
	//
	//#pragma endregion
	//
	//#pragma region find_b_nearest_clusters
	//
	//		TEST_METHOD(find_b_nearest_clusters_given_l_b_1_returns_single_closest_cluster) {
	//			unsigned int L = 1;
	//			std::vector<Node*> top_level = get_index(L).top_level;
	//			float* query = new float[3]{ 3, 3, 3 };
	//			unsigned int b = 1;
	//
	//			auto actual = find_b_nearest_clusters(L, top_level, query, b);
	//
	//			Assert::IsTrue(actual.size() == b);
	//			Assert::IsTrue(*actual[0]->representative->descriptor == *query);
	//		}
	//
	//		TEST_METHOD(find_b_nearest_clusters_given_l_2_b_1_returns_single_closest_cluster) {
	//			unsigned int L = 2;
	//			std::vector<Node*> top_level = get_index(L).top_level;
	//			float* query = new float[3]{ 3, 3, 3 };
	//			unsigned int b = 1;
	//
	//			auto actual = find_b_nearest_clusters(L, top_level, query, b);
	//
	//			Assert::IsTrue(actual.size() == b);
	//			Assert::IsTrue(*actual[0]->representative->descriptor == *query);
	//		}
	//
	//		TEST_METHOD(find_b_nearest_clusters_given_l_2_b_2_returns_2_closest_cluster) {
	//			unsigned int L = 2;
	//			std::vector<Node*> top_level = get_index(L).top_level;
	//			float* query = new float[3]{ 3, 3, 3 };
	//			unsigned int b = 2;
	//
	//			auto actual = find_b_nearest_clusters(L, top_level, query, b);
	//
	//			Assert::IsTrue(actual.size() == b);
	//			Assert::IsTrue(*actual[0]->representative->descriptor == *(new float[3]{ 2, 2, 2 }));
	//			Assert::IsTrue(*actual[1]->representative->descriptor == *query);
	//		}
	//
	//#pragma endregion
	//
	//#pragma region scan_node_children
	//
	//		TEST_METHOD(scan_node_children_given_b_1_returns_single_closest_element) {
	//			g_distance_function = &euclidean_distance;
	//			g_vector_dimensions = 3;
	//
	//			float* query = new float[3]{ 3, 3, 3 };
	//			unsigned int b = 1;
	//			Node* node = new Node(new float[3]{ 3, 3, 3 });
	//			node->children = {
	//				new Node(new float[3]{1, 1, 1}),
	//				new Node(new float[3]{2, 2, 2}),
	//				new Node(new float[3]{3, 3, 3}),
	//			};
	//
	//			std::vector<Node*> next_level_best_nodes = {};
	//
	//			scan_node(query, b, node->children, next_level_best_nodes);
	//
	//			float* expected = new float[3]{ 3, 3, 3 };
	//			Assert::IsTrue(next_level_best_nodes.size() == b);
	//			Assert::IsTrue(*next_level_best_nodes[0]->representative->descriptor == *expected);
	//		}
	//
	//		TEST_METHOD(scan_node_given_children_less_than_b_returns_everything) {
	//			g_distance_function = &euclidean_distance;
	//			g_vector_dimensions = 3;
	//
	//			float* query = new float[3]{ 3, 3, 3 };
	//			unsigned int b = 4;
	//			Node* node = new Node(new float[3]{ 3, 3, 3 });
	//			node->children = {
	//				new Node(new float[3]{1, 1, 1}),
	//				new Node(new float[3]{2, 2, 2}),
	//				new Node(new float[3]{3, 3, 3}),
	//			};
	//
	//			std::vector<Node*> next_level_best_nodes = {};
	//
	//			scan_node(query, b, node->children, next_level_best_nodes);
	//
	//			Assert::IsTrue(next_level_best_nodes.size() == node->children.size());
	//		}
	//
	//		TEST_METHOD(scan_node_given_b_2_returns_two_closest_elements) {
	//			g_distance_function = &euclidean_distance;
	//			g_vector_dimensions = 3;
	//
	//			float* query = new float[3]{ 3, 3, 3 };
	//			unsigned int b = 2;
	//			Node* node = new Node(new float[3]{ 3, 3, 3 });
	//			node->children = {
	//				new Node(new float[3]{1, 1, 1}),
	//				new Node(new float[3]{2, 2, 2}),
	//				new Node(new float[3]{6, 6, 6}),
	//			};
	//
	//			std::vector<Node*> next_level_best_nodes = {};
	//
	//			scan_node(query, b, node->children, next_level_best_nodes);
	//
	//			float* first_element = new float[3]{ 1, 1, 1 };
	//			float* second_element = new float[3]{ 2, 2, 2 };
	//
	//			Assert::IsTrue(next_level_best_nodes.size() == b);
	//			Assert::IsTrue(*next_level_best_nodes[0]->representative->descriptor == *first_element);
	//			Assert::IsTrue(*next_level_best_nodes[1]->representative->descriptor == *second_element);
	//		}
	//
	//#pragma endregion
	//	};
// }
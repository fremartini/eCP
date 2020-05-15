#include "pch.h"

#include "CppUnitTest.h"
#include "vector"
#include "../eCP/eCP.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace std;

namespace queryProcessingTests
{
	//	TEST_CLASS(queryProcessingTests)
	//	{
	//	private:
	//
	//		Index get_index(unsigned int L) {
	//			std::vector<std::vector<float>> descriptors;
	//
	//			for (unsigned int i = 0; i < 100; i++) {
	//				descriptors.push_back({ (float)i, (float)i, (float)i });
	//			}
	//
	//			return *eCP_Index(descriptors, L, 0);
	//		}
	//
	//	public:
	//#pragma region find_k_nearest_points
	//
	//		TEST_METHOD(find_k_nearest_points_given_k_1_returns_k_closest_points) {
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
	//			unsigned int k = 1;
	//
	//			auto actual = find_k_nearest_points(q, points, k);
	//
	//			Assert::IsTrue(actual.size() == 1);
	//			Assert::IsTrue(actual[0].first == 2);
	//			Assert::IsTrue(actual[0].second == 0);
	//		}
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
}
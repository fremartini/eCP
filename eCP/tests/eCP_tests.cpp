#include "pch.h"

#include "CppUnitTest.h"
#include "vector"
#include "../eCP/eCP.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace eCPTests
{
	TEST_CLASS(eCPTests)
	{
	private:
		Index* get_index(unsigned int L = 2) {
			std::vector<std::vector<float>> descriptors =
			{
				{59, 59, 59},
				{50, 50, 50},
				{2, 2, 2},
				{6, 6, 6},
				{15, 15, 15},
				{11, 11, 11},
				{31, 31, 31},
				{21, 21, 21},
				{42, 42, 24},
				{24, 24, 24},
				{10, 10, 10},
				{34, 34, 34},
				{25, 25, 25},
				{29, 29, 29},
				{32, 32, 32},
				{40, 40, 40},
				{7, 7, 7},
			};

			return eCP_Index(descriptors, L, 0);
		}

	public:
#pragma region point
		TEST_METHOD(point_comparison_given_different_points_returns_false) {
			Assert::IsFalse(Point(new float[3]{ 1, 1, 1 }, 1) == Point(new float[3]{ 2, 2, 2 }, 2));
		}

		TEST_METHOD(point_comparison_given_same_points_returns_true) {
			Assert::IsTrue(Point(new float[3]{ 1, 1, 1 }, 1) == Point(new float[3]{ 1, 1, 1 }, 1));
		}
#pragma endregion

#pragma region node

		TEST_METHOD(cluster_comparison_given_different_clusters_returns_false) {
			Assert::IsFalse(Node(Point(new float[3]{ 1, 1, 1 }, 0)) == Node(Point(new float[3]{ 2, 2, 2 }, 0)));
		}

		TEST_METHOD(cluster_comparison_given_same_clusters_returns_true) {
			Assert::IsTrue(Node(Point(new float[3]{ 1, 1, 1 }, 0)) == Node(Point(new float[3]{ 1, 1, 1 }, 0)));
		}

#pragma endregion

#pragma region fit

		TEST_METHOD(fit_given_descriptors_has_correct_depth) {
			std::vector<std::vector<float>> descriptors = {
				{1, 1, 1},
				{2, 2, 2}
			};
			unsigned int L = 2;

			Index index = *eCP_Index(descriptors, L, 0);

			Assert::IsTrue(index.L = L);
			//check that the deepest level is 2
			Assert::IsTrue(index.top_level[0]->children[0]->children.size() == 0);
			Assert::IsTrue(index.top_level[0]->children[0]->points.size() != 0);
		}

		TEST_METHOD(fit_given_descriptors_inserts_descriptors) {
			std::vector<std::vector<float>> descriptors = {
				{1, 1, 1},
				{2, 2, 2},
				{3, 3, 3},
			};
			unsigned int L = 1;

			Index index = *eCP_Index(descriptors, L, 0);

			Assert::IsTrue(index.dataset.size() == descriptors.size());
		}
#pragma endregion

#pragma region query
		TEST_METHOD(query_given_k_1_returns_query_point) {
			Index* index = get_index();
			std::vector<float> q = { 5, 5, 5 };
			unsigned int k = 1;
			unsigned int b = 1;

			auto actual = query(index, q, k, b);

			Assert::IsTrue(actual.first.size() == 1);
			Assert::IsTrue(actual.second.size() == 1);

			Assert::IsTrue(*index->dataset[actual.first[0]].descriptor == *new float[3]{ 6, 6, 6 });
		}

		TEST_METHOD(query_given_k_2_returns_closest_points) {
			Index* index = get_index(1);
			std::vector<float> q = { 9, 9, 9 };
			unsigned int k = 2;
			unsigned int b = 1;

			auto actual = query(index, q, k, b);

			Assert::IsTrue(actual.first.size() == 2);
			Assert::IsTrue(actual.second.size() == 2);
		}

#pragma endregion
	};
}
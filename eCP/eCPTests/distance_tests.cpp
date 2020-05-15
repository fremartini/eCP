#include "pch.h"

#include "CppUnitTest.h"
#include "vector"
#include "../eCP/eCP.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace functionsTests
{
	TEST_CLASS(functionsTests)
	{
	private:
		bool cmpf(float A, float B, float epsilon = 0.025)
		{
			return (fabs(A - B) < epsilon);
		}

	public:
#pragma region euclidean_distance
		TEST_METHOD(euclidean_distance_given_2_4d_vectors_returns_accurate_distance)
		{
			//arrange
			g_vector_dimensions = 4;

			float* a = new float[4]{ 2.0, 3.0, 4.0, 2.0 };
			float* b = new float[4]{ 1.0, -2.0, 1.0, 3.0 };

			//act
			float actual = euclidean_distance(a, b);
			float expected = 6.0;

			//assert
			Assert::IsTrue(cmpf(expected, sqrt(actual)));
		}

		TEST_METHOD(euclidean_distance_given_2_18d_vectors_returns_accurate_distance)
		{
			//arrange
			g_vector_dimensions = 18;

			float* a = new float[18]{ 2,5,3,5,2,7,8,7,7,2,9,1,5,9,2,7,2,7 };
			float* b = new float[18]{ 1,7,4,5,6,8,8,2,7,2,9,1,5,8,2,7,2,7 };
			//act
			float actual = euclidean_distance(a, b);
			float expected = 7.0;
			//assert
			Assert::IsTrue(cmpf(expected, sqrt(actual)));
		}
#pragma endregion

#pragma region cosine_similarity

		TEST_METHOD(angular_distance_given_same_vectors_returns_0) {
			g_vector_dimensions = 3;
			float* a = new float[3]{ 1, 1, 1 };

			float actual = angular_distance(a, a);

			Assert::IsTrue(actual == 0);
		}

		TEST_METHOD(angular_distance_given_opposite_vectors_returns_1) {
			g_vector_dimensions = 3;
			float* a = new float[3]{ 1, 1, 1 };
			float* b = new float[3]{ -1, -1, -1 };

			float actual = angular_distance(a, b);

			Assert::IsTrue(cmpf(actual / 3.14, 1));
		}

		TEST_METHOD(angular_distance_given_perpendicular_vectors_returns_correct_correct_value) {
			g_vector_dimensions = 2;
			float* a = new float[2]{ 0, 1 };
			float* b = new float[2]{ 1, 0 };

			float actual = angular_distance(a, b);

			Assert::IsTrue(cmpf(actual / 3.14, 0.5));
		}

		TEST_METHOD(angular_distance_given_2_dimensions_returns_correct_value) {
			g_vector_dimensions = 2;
			float* a = new float[2]{ 5, 4 };
			float* b = new float[2]{ 1, 1 };

			float actual = angular_distance(a, b);

			Assert::IsTrue(cmpf(actual / 3.14, 0.03));
		}

		TEST_METHOD(angular_distance_given_3_dimensions_returns_correct_value) {
			g_vector_dimensions = 3;
			float* a = new float[3]{ 1, 5, 4 };
			float* b = new float[3]{ 9, 9, 7 };

			float actual = angular_distance(a, b);

			Assert::IsTrue(cmpf(actual / 3.14, 0.16));
		}

#pragma endregion
	};
}
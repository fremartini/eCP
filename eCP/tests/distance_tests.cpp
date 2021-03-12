#include <cmath>
#include <gtest/gtest.h>

#include <eCP/index/eCP.hpp>
#include <eCP/index/shared/distance.hpp>
#include <eCP/index/shared/globals.hpp>

/* HELPER FUNCTIONS */

const float EPSILON_ = 0.006f;

// Compare floating point values (cmpf) by using epsilon tolerance of rounding error
bool cmpf(float A, float B, float epsilon = EPSILON_)
{
    auto diff = fabs(A - B);
    return diff < epsilon;
}

/* TESTS */

// Check test gtest framework
TEST(distance_tests, tests_sanity_check)
{
  EXPECT_EQ(2, 1 + 1);
}

TEST(distance_tests, euclidean_distance_given_1d_vectors_returns_correct_distance)
{
    /* This test corresponds to finding the diagonal line between point (3,3) and (4,4) in a 2D coordinate system. */

    globals::g_vector_dimensions = 2;
    float* a = new float[2]{4, 4};
    float* b = new float[2]{3, 3};

    float expected = 1.41;
    float actual = std::sqrt(distance::euclidean_distance(a, b));
    
    EXPECT_NEAR(expected, actual, EPSILON_)
        << "actual: " << actual << " should be eq to expected: " << expected;
}

TEST(distance_tests, euclidean_distance_given_2_4d_vectors_returns_accurate_distance)
{
    //arrange
    globals::g_vector_dimensions = 4;
    float* a = new float[4]{ 2.0, 3.0, 4.0, 2.0 };
    float* b = new float[4]{ 1.0, -2.0, 1.0, 3.0 };

    //act
    float expected = 6.0;
    float actual = std::sqrt(distance::euclidean_distance(a, b));
    
    //assert
    EXPECT_FLOAT_EQ(expected, actual)
        << "actual: " << actual << " should be eq to expected: " << expected;
}

TEST(distance_tests, euclidean_distance_given_2_18d_vectors_returns_accurate_distance)
{
    //arrange
    globals::g_vector_dimensions = 18;
    float* a = new float[18]{ 2,5,3,5,2,7,8,7,7,2,9,1,5,9,2,7,2,7 };
    float* b = new float[18]{ 1,7,4,5,6,8,8,2,7,2,9,1,5,8,2,7,2,7 };

    //act
    float actual = std::sqrt(distance::euclidean_distance(a, b));
    float expected = 7.0;

    //assert
    EXPECT_FLOAT_EQ(expected, actual);
}

TEST(distance_tests, angular_distance_given_same_vectors_returns_0) {
    globals::g_vector_dimensions = 3;
    float* a = new float[3]{ 1, 1, 1 };

    float actual = distance::angular_distance(a, a);

    EXPECT_FLOAT_EQ(0, actual);
}

TEST(distance_tests, angular_distance_given_opposite_vectors_returns_1) {
    globals::g_vector_dimensions = 3;
    float* a = new float[3]{ 1, 1, 1 };
    float* b = new float[3]{ -1, -1, -1 };

    float actual = distance::angular_distance(a, b) / M_PI;

    EXPECT_FLOAT_EQ(1, actual);
}

TEST(distance_tests, angular_distance_given_perpendicular_vectors_returns_correct_correct_value) {
    globals::g_vector_dimensions = 2;
    float* a = new float[2]{ 0, 1 };
    float* b = new float[2]{ 1, 0 };

    float actual = distance::angular_distance(a, b) / M_PI;

    EXPECT_FLOAT_EQ(0.5, actual);
}

TEST(distance_tests, angular_distance_given_2_dimensions_returns_correct_value) {
    globals::g_vector_dimensions = 2;
    float* a = new float[2]{ 5, 4 };
    float* b = new float[2]{ 1, 1 };

    float actual = distance::angular_distance(a, b) / M_PI;

    EXPECT_TRUE(cmpf(0.03, actual));
}

TEST(distance_tests, angular_distance_given_3_dimensions_returns_correct_value) {
    globals::g_vector_dimensions = 3;
    float* a = new float[3]{ 1, 5, 4 };
    float* b = new float[3]{ 9, 9, 7 };

    float actual = distance::angular_distance(a, b) / M_PI;

    EXPECT_NEAR(actual, 0.16, EPSILON_);
}

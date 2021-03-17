#include <gtest/gtest.h>
#include <eCP/utilities/utilities.hpp>
#include <algorithm>

/* Tests */

TEST(utilities_tests, get_random_unique_indexes_given_9_10_returns_set_with_size_9) {
  auto result_set = utilities::get_random_unique_indexes(9, 10);
  EXPECT_EQ(result_set.size(), 9);
}

TEST(utilities_tests, get_random_unique_indexes_given_10_10_returns_complete_set) {
  std::vector<unsigned> expected_numbers {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  auto result_set = utilities::get_random_unique_indexes(10, 10);

  EXPECT_EQ(result_set.size(), 10);

  for (auto& num : expected_numbers) {
    auto it = std::find(result_set.begin(), result_set.end(), num);
    EXPECT_TRUE(it != result_set.end());
  }
}

// !!! Tests below are unnecessary because assertions are used in the function to circumvent this

//TEST(utilities_tests, get_random_unique_indexes_given_0_10_returns_0_elements_in_set) {
//  auto result_set = utilities::get_random_unique_indexes(0, 10);
//  EXPECT_EQ(result_set.size(), 0);
//}

//TEST(utilities_tests, get_random_unique_indexes_given_6_5_throws_invalid_argument_exception) {
//  EXPECT_THROW(utilities::get_random_unique_indexes(6, 5), std::invalid_argument);
//}

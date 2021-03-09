#include <gtest/gtest.h>
#include <eCP/utilities/utilities.hpp>

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
    EXPECT_TRUE(result_set.find(num) != result_set.end());
  }
}

TEST(utilities_tests, get_random_unique_indexes_given_0_10_returns_0_elements_in_set) {
  auto result_set = utilities::get_random_unique_indexes(0, 10);
  EXPECT_EQ(result_set.size(), 0);
}

TEST(utilities_tests, get_random_unique_indexes_given_10_5_returns_0_elements_in_set) {
  auto result_set = utilities::get_random_unique_indexes(10, 5);
  EXPECT_EQ(result_set.size(), 0);
}


#ifndef Q88_UNITTEST_H__
#define Q88_UNITTEST_H__

#include <gtest/gtest.h>

#include "../src/q0088.hpp"

using namespace std;

TEST(q88, sample_input01) {
  vector<int> nums1{1, 2, 3, 0, 0, 0};
  int m = 3;
  vector<int> nums2{2, 5, 6};
  int n = 3;
  vector<int> exp{1, 2, 2, 3, 5, 6};
  l88::Solution solver;
  solver.merge(nums1, m, nums2, n);
  EXPECT_EQ(nums1, exp);
}

TEST(q88, sample_input02) {
  vector<int> nums1{1};
  int m = 1;
  vector<int> nums2{0};
  int n = 0;
  vector<int> exp{1};
  l88::Solution solver;
  solver.merge(nums1, m, nums2, n);
  EXPECT_EQ(nums1, exp);
}

TEST(q88, sample_input03) {
  vector<int> nums1{0};
  int m = 0;
  vector<int> nums2{1};
  int n = 1;
  vector<int> exp{1};
  l88::Solution solver;
  solver.merge(nums1, m, nums2, n);
  EXPECT_EQ(nums1, exp);
}

#endif
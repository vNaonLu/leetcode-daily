
#ifndef Q350_UNITTEST_H__
#define Q350_UNITTEST_H__

#include <gtest/gtest.h>

#include "q0350.hpp"

using namespace std;

TEST(q350, sample_input01) {
  vector<int> nums1{1, 2, 2, 1};
  vector<int> nums2{2, 2};
  vector<int> e{2, 2};
  l350::Solution solver;
  vector<int> out = solver.intersect(nums1, nums2);
  sort(out.begin(), out.end());
  EXPECT_EQ(out, e);
}

TEST(q350, sample_input02) {
  vector<int> nums1{4, 9, 5};
  vector<int> nums2{9, 4, 9, 8, 4};
  vector<int> e{4, 9};
  l350::Solution solver;
  vector<int> out = solver.intersect(nums1, nums2);
  sort(out.begin(), out.end());
  EXPECT_EQ(out, e);
}

#endif
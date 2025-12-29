// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Finding Pairs With a Certain Sum
//
// https://leetcode.com/problems/finding-pairs-with-a-certain-sum/
//
// Question ID: 1865
// Difficult  : Medium
// Solve Date : 2025/07/06 12:28

#include <iosfwd>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1865. Finding Pairs With a Certain Sum|:
//
// You are given two integer arrays |nums1| and |nums2|. You are tasked to
// implement a data structure that supports queries of two types:
//
//  1. Add a positive integer to an element of a given index in the array
//  |nums2|.
//
//  2. Count the number of pairs |(i, j)| such that |nums1[i] + nums2[j]| equals
//  a given value ( |0 <= i < nums1.length| and |0 <= j < nums2.length|).
// Implement the |FindSumPairs| class:
//
//  • |FindSumPairs(int[] nums1, int[] nums2)| Initializes the |FindSumPairs|
//  object with two integer arrays |nums1| and |nums2|.
//
//  • |void add(int index, int val)| Adds |val| to |nums2[index]|, i.e., apply
//  |nums2[index] += val|.
//
//  • |int count(int tot)| Returns the number of pairs |(i, j)| such that
//  |nums1[i] + nums2[j] == tot|.
//
//

LEETCODE_BEGIN_RESOLVING(1865, FindingPairsWithACertainSum, FindSumPairs);

class FindSumPairs {
public:
  FindSumPairs(vector<int> &nums1, vector<int> &nums2)
      : n1{std::move(nums1)}, n2{std::move(nums2)} {
    for (auto x : n2) {
      ++m[x];
    }
  }

  void add(int index, int val) {
    --m[n2[index]];
    n2[index] += val;
    ++m[n2[index]];
  }

  int count(int tot) {
    int res = 0;
    for (auto x : n1) {
      res += m[tot - x];
    }
    return res;
  }

private:
  vector<int>             n1;
  vector<int>             n2;
  unordered_map<int, int> m;
};

LEETCODE_END_RESOLVING(FindSumPairs);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums1.length <= 1000|
// * |1 <= nums2.length <= 10⁵|
// * |1 <= nums1[i] <= 10⁹|
// * |1 <= nums2[i] <= 10⁵|
// * |0 <= index < nums2.length|
// * |1 <= val <= 10⁵|
// * |1 <= tot <= 10⁹|
// * At most |1000| calls are made to |add| and |count| each.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["FindSumPairs", "count", "add", "count", "count", "add", "add",
//  "count"]
// [[[1, 1, 2, 2, 2, 3], [1, 4, 5, 2, 5, 4]], [7], [3, 2], [8], [4], [0, 1], [1,
// 1], [7]] Output: [null, 8, null, 2, 1, null, null, 11]
//

LEETCODE_SOLUTION_UNITTEST(1865, FindingPairsWithACertainSum, example_1) {
  vector<int> s0_nums1       = {1, 1, 2, 2, 2, 3};
  vector<int> s0_nums2       = {1, 4, 5, 2, 5, 4};
  auto        find_sum_pairs = MakeFindSumPairs(s0_nums1, s0_nums2);
  int         s1_tot         = 7;
  int         s1_expect      = 8;
  int         s1_actual      = find_sum_pairs->count(s1_tot);
  LCD_EXPECT_EQ(s1_expect, s1_actual);
  int s2_index = 3;
  int s2_val   = 2;
  find_sum_pairs->add(s2_index, s2_val);
  int s3_tot    = 8;
  int s3_expect = 2;
  int s3_actual = find_sum_pairs->count(s3_tot);
  LCD_EXPECT_EQ(s3_expect, s3_actual);
  int s4_tot    = 4;
  int s4_expect = 1;
  int s4_actual = find_sum_pairs->count(s4_tot);
  LCD_EXPECT_EQ(s4_expect, s4_actual);
  int s5_index = 0;
  int s5_val   = 1;
  find_sum_pairs->add(s5_index, s5_val);
  int s6_index = 1;
  int s6_val   = 1;
  find_sum_pairs->add(s6_index, s6_val);
  int s7_tot    = 7;
  int s7_expect = 11;
  int s7_actual = find_sum_pairs->count(s7_tot);
  LCD_EXPECT_EQ(s7_expect, s7_actual);
}

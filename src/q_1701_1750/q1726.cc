// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Tuple with Same Product
//
// https://leetcode.com/problems/tuple-with-same-product/
//
// Question ID: 1726
// Difficult  : Medium
// Solve Date : 2025/02/06 20:08

#include <iosfwd>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1726. Tuple with Same Product|:
//
// Given an array |nums| of distinct positive integers, return the number of
// tuples |(a, b, c, d)| such that |a * b = c * d| where |a|, |b|, |c|, and |d|
// are elements of |nums|, and |a != b != c != d|.
//
//

LEETCODE_BEGIN_RESOLVING(1726, TupleWithSameProduct, Solution);

class Solution {
public:
  int tupleSameProduct(vector<int> &nums) {
    unordered_map<int, int> mp;
    int                     n = nums.size();
    mp.reserve(n * (n - 1) / 2);
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        int mul = nums[i] * nums[j];
        ++mp[mul];
      }
    }
    int res = 0;
    for (auto [_, cnt] : mp) {
      if (cnt >= 2) {
        res += cnt * (cnt - 1) / 2;
      }
    }
    return res * 8;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 1000|
// * |1 <= nums[i] <= 10⁴|
// * All elements in |nums| are distinct.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,3,4,6]
// Output: 8
//

LEETCODE_SOLUTION_UNITTEST(1726, TupleWithSameProduct, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 3, 4, 6};
  int         expect   = 8;
  int         actual   = solution->tupleSameProduct(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,4,5,10]
// Output: 16
//

LEETCODE_SOLUTION_UNITTEST(1726, TupleWithSameProduct, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 4, 5, 10};
  int         expect   = 16;
  int         actual   = solution->tupleSameProduct(nums);
  LCD_EXPECT_EQ(expect, actual);
}

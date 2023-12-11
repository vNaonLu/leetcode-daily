// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find the Distinct Difference Array
//
// https://leetcode.com/problems/find-the-distinct-difference-array/
//
// Question ID: 2670
// Difficult  : Easy
// Solve Date : 2023/12/10 14:49

#include <iosfwd>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2670. Find the Distinct Difference Array|:
//
// You are given a 0-indexed array |nums| of length |n|.
// The distinct difference array of |nums| is an array |diff| of length |n| such
// that |diff[i]| is equal to the number of distinct elements in the suffix
// |nums[i + 1, ..., n - 1]| subtracted from the number of distinct elements in
// the prefix |nums[0, ..., i]|. Return the distinct difference array of |nums|.
// Note that |nums[i, ..., j]| denotes the subarray of |nums| starting at index
// |i| and ending at index |j| inclusive. Particularly, if |i > j| then |nums[i,
// ..., j]| denotes an empty subarray.
//
//

LEETCODE_BEGIN_RESOLVING(2670, FindTheDistinctDifferenceArray, Solution);

class Solution {
public:
  vector<int> distinctDifferenceArray(vector<int> &nums) {
    int                     n = nums.size();
    vector<int>             cnt1(n, 0);
    vector<int>             cnt2(n, 0);
    unordered_map<int, int> x;
    unordered_map<int, int> y;
    for (int i = 0; i < n; ++i) {
      x[nums[i]]         = 1;
      y[nums[n - i - 1]] = 1;
      cnt1[i]            = x.size();
      cnt2[n - i - 1]    = y.size();
    }
    vector<int> res(n, 0);
    for (int i = 0; i < n - 1; ++i) {
      res[i] = cnt1[i] - cnt2[i + 1];
    }
    res[n - 1] = cnt1[n - 1];
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n == nums.length <= 50|
// * |1 <= nums[i] <= 50|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3,4,5]
// Output: [-3,-1,1,3,5]
//
// For index i = 0, there is 1 element in the prefix and 4 distinct elements in
// the suffix. Thus, diff[0] = 1 - 4 = -3. For index i = 1, there are 2 distinct
// elements in the prefix and 3 distinct elements in the suffix. Thus, diff[1] =
// 2 - 3 = -1. For index i = 2, there are 3 distinct elements in the prefix and
// 2 distinct elements in the suffix. Thus, diff[2] = 3 - 2 = 1. For index i =
// 3, there are 4 distinct elements in the prefix and 1 distinct element in the
// suffix. Thus, diff[3] = 4 - 1 = 3. For index i = 4, there are 5 distinct
// elements in the prefix and no elements in the suffix. Thus, diff[4] = 5 - 0
// = 5.

LEETCODE_SOLUTION_UNITTEST(2670, FindTheDistinctDifferenceArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4, 5};
  vector<int> expect   = {-3, -1, 1, 3, 5};
  vector<int> actual   = solution->distinctDifferenceArray(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [3,2,3,4,2]
// Output: [-2,-1,0,2,3]
//
// For index i = 0, there is 1 element in the prefix and 3 distinct elements in
// the suffix. Thus, diff[0] = 1 - 3 = -2. For index i = 1, there are 2 distinct
// elements in the prefix and 3 distinct elements in the suffix. Thus, diff[1] =
// 2 - 3 = -1. For index i = 2, there are 2 distinct elements in the prefix and
// 2 distinct elements in the suffix. Thus, diff[2] = 2 - 2 = 0. For index i =
// 3, there are 3 distinct elements in the prefix and 1 distinct element in the
// suffix. Thus, diff[3] = 3 - 1 = 2. For index i = 4, there are 3 distinct
// elements in the prefix and no elements in the suffix. Thus, diff[4] = 3 - 0
// = 3.

LEETCODE_SOLUTION_UNITTEST(2670, FindTheDistinctDifferenceArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 2, 3, 4, 2};
  vector<int> expect   = {-2, -1, 0, 2, 3};
  vector<int> actual   = solution->distinctDifferenceArray(nums);
  LCD_EXPECT_EQ(expect, actual);
}

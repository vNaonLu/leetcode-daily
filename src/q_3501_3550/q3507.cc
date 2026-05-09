// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Minimum Pair Removal to Sort Array I
//
// https://leetcode.com/problems/minimum-pair-removal-to-sort-array-i/
//
// Question ID: 3507
// Difficult  : Easy
// Solve Date : 2026/01/22 20:36

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3507. Minimum Pair Removal to Sort Array I|:
//
// Given an array |nums|, you can perform the following operation any number of
// times:
//
//  • Select the adjacent pair with the minimum sum in |nums|. If multiple such
//  pairs exist, choose the leftmost one.
//
//  • Replace the pair with their sum.
// Return the minimum number of operations needed to make the array
// non-decreasing. An array is said to be non-decreasing if each element is
// greater than or equal to its previous element (if it exists).
//
//

LEETCODE_BEGIN_RESOLVING(3507, MinimumPairRemovalToSortArrayI, Solution);

class Solution {
public:
  int minimumPairRemoval(vector<int> &nums) {
    int res = 0;
    while (!is_sorted(nums.begin(), nums.end())) {
      res += 1;
      auto merge = nums.begin();
      auto it    = merge + 1;
      int  mn    = numeric_limits<int>::max();
      while (it != nums.end()) {
        if (*(it - 1) + *it < mn) {
          mn    = *(it - 1) + *it;
          merge = it - 1;
        }
        ++it;
      }
      *merge += *(merge + 1);
      ++merge;
      std::move(merge + 1, nums.end(), merge);
      nums.resize(nums.size() - 1);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 50|
// * |-1000 <= nums[i] <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [5,2,3,1]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3507, MinimumPairRemovalToSortArrayI, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {5, 2, 3, 1};
  int         expect   = 2;
  int         actual   = solution->minimumPairRemoval(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,2]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(3507, MinimumPairRemovalToSortArrayI, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 2};
  int         expect   = 0;
  int         actual   = solution->minimumPairRemoval(nums);
  LCD_EXPECT_EQ(expect, actual);
}

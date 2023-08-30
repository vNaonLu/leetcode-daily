// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Replacements to Sort the Array
//
// https://leetcode.com/problems/minimum-replacements-to-sort-the-array/
//
// Question ID: 2366
// Difficult  : Hard
// Solve Date : 2023/08/30 20:09

#include <cmath>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2366. Minimum Replacements to Sort the Array|:
//
// You are given a 0-indexed integer array |nums|. In one operation you can
// replace any element of the array with any two elements that sum to it.
//
//  • For example, consider |nums = [5,6,7]|. In one operation, we can replace
//  |nums[1]| with |2| and |4| and convert |nums| to |[5,2,4,7]|.
// Return the minimum number of operations to make an array that is sorted in
// non-decreasing order.
//
//

LEETCODE_BEGIN_RESOLVING(2366, MinimumReplacementsToSortTheArray, Solution);

class Solution {
public:
  long long minimumReplacement(vector<int> &nums) {
    int64_t res = 0;
    int64_t mx  = nums.back();
    for (auto it = nums.rbegin() + 1; it != nums.rend(); ++it) {
      if (*it > mx) {
        int p = ceil(*it / double(mx));
        res += p - 1;
        mx = *it / p;
      } else {
        mx = *it;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |1 <= nums[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [3,9,3]
// Output: 2
//
// Here are the steps to sort the array in non-decreasing order:
// - From [3,9,3], replace the 9 with 3 and 6 so the array becomes [3,3,6,3]
// - From [3,3,6,3], replace the 6 with 3 and 3 so the array becomes [3,3,3,3,3]
// There are 2 steps to sort the array in non-decreasing order. Therefore, we
// return 2.

LEETCODE_SOLUTION_UNITTEST(2366, MinimumReplacementsToSortTheArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 9, 3};
  long long   expect   = 2;
  long long   actual   = solution->minimumReplacement(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,3,4,5]
// Output: 0
//
// The array is already in non-decreasing order. Therefore, we return 0.

LEETCODE_SOLUTION_UNITTEST(2366, MinimumReplacementsToSortTheArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4, 5};
  long long   expect   = 0;
  long long   actual   = solution->minimumReplacement(nums);
  LCD_EXPECT_EQ(expect, actual);
}

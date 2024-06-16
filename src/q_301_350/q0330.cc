// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Patching Array
//
// https://leetcode.com/problems/patching-array/
//
// Question ID: 330
// Difficult  : Hard
// Solve Date : 2024/06/16 13:58

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |330. Patching Array|:
//
// Given a sorted integer array |nums| and an integer |n|, add/patch elements to
// the array such that any number in the range |[1, n]| inclusive can be formed
// by the sum of some elements in the array. Return the minimum number of
// patches required.
//
//

LEETCODE_BEGIN_RESOLVING(330, PatchingArray, Solution);

class Solution {
public:
  int minPatches(vector<int> &nums, int n) {
    int     res = 0;
    int     idx = 0;
    int64_t nxt = 1;
    while (nxt <= n) {
      if (idx < nums.size() && nums[idx] <= nxt) {
        nxt += nums[idx++];
      } else {
        nxt += nxt;
        ++res;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 1000|
// * |1 <= nums[i] <= 10⁴|
// * |nums| is sorted in ascending order.
// * |1 <= n <= 2³¹ - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,3], n = 6
// Output: 1
// Explanation:
// Combinations of nums are [1], [3], [1,3], which form possible sums of: 1,
// 3, 4. Now if we add/patch 2 to nums, the combinations are: [1], [2], [3],
// [1,3], [2,3], [1,2,3]. Possible sums are 1, 2, 3, 4, 5, 6, which now covers
// the range [1, 6]. So we only need 1 patch.
//

LEETCODE_SOLUTION_UNITTEST(330, PatchingArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 3};
  int         n        = 6;
  int         expect   = 1;
  int         actual   = solution->minPatches(nums, n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,5,10], n = 20
// Output: 2
// Explanation: The two patches can be [2, 4].
//

LEETCODE_SOLUTION_UNITTEST(330, PatchingArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 5, 10};
  int         n        = 20;
  int         expect   = 2;
  int         actual   = solution->minPatches(nums, n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,2,2], n = 5
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(330, PatchingArray, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 2};
  int         n        = 5;
  int         expect   = 0;
  int         actual   = solution->minPatches(nums, n);
  LCD_EXPECT_EQ(expect, actual);
}

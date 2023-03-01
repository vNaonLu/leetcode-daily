// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Swaps to Group All 1's Together II
//
// https://leetcode.com/problems/minimum-swaps-to-group-all-1s-together-ii/
//
// Question ID: 2134
// Difficult  : Medium
// Solve Date : 2022/02/16 18:17

#include <iosfwd>
#include <limits>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2134. Minimum Swaps to Group All 1's Together II|:
//
// A swap is defined as taking two distinct positions in an array and swapping
// the values in them. A circular array is defined as an array where we consider
// the first element and the last element to be adjacent. Given a binary
// circular array |nums|, return the minimum number of swaps required to group
// all |1|'s present in the array together at any location.  
//

LEETCODE_BEGIN_RESOLVING(2134, MinimumSwapsToGroupAll1STogetherII, Solution);

class Solution {
public:
  int minSwaps(vector<int> &nums) {
    int res     = numeric_limits<int>::max(),
        one_cnt = count(nums.begin(), nums.end(), 1), curr = 0;
    if (one_cnt == 0)
      return 0;
    for (int l = 0, r = 0; l < nums.size(); r = (r + 1) % nums.size()) {
      curr += !nums[r];
      if (r - l + 1 == one_cnt || r < l) {
        res = min(res, curr);
        curr -= !nums[l++];
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |nums[i]| is either |0| or |1|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [0,1,0,1,1,0,0]
// Output: 1
//
// Here are a few of the ways to group all the 1's together:
// [0,0,1,1,1,0,0] using 1 swap.
// [0,1,1,1,0,0,0] using 1 swap.
// [1,1,0,0,0,0,1] using 2 swaps (using the circular property of the array).
// There is no way to group all 1's together with 0 swaps.
// Thus, the minimum number of swaps required is 1.

LEETCODE_SOLUTION_UNITTEST(2134, MinimumSwapsToGroupAll1STogetherII,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {0, 1, 0, 1, 1, 0, 0};
  int         expect   = 1;
  int         actual   = solution->minSwaps(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [0,1,1,1,0,0,1,1,0]
// Output: 2
//
// Here are a few of the ways to group all the 1's together:
// [1,1,1,0,0,0,0,1,1] using 2 swaps (using the circular property of the array).
// [1,1,1,1,1,0,0,0,0] using 2 swaps.
// There is no way to group all 1's together with 0 or 1 swaps.
// Thus, the minimum number of swaps required is 2.

LEETCODE_SOLUTION_UNITTEST(2134, MinimumSwapsToGroupAll1STogetherII,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {0, 1, 1, 1, 0, 0, 1, 1, 0};
  int         expect   = 2;
  int         actual   = solution->minSwaps(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,1,0,0,1]
// Output: 0
//
// All the 1's are already grouped together due to the circular property of the
// array. Thus, the minimum number of swaps required is 0.

LEETCODE_SOLUTION_UNITTEST(2134, MinimumSwapsToGroupAll1STogetherII,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 0, 0, 1};
  int         expect   = 0;
  int         actual   = solution->minSwaps(nums);
  LCD_EXPECT_EQ(expect, actual);
}

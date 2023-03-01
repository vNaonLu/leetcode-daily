// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Difference Between Largest and Smallest Value in Three Moves
//
// https://leetcode.com/problems/minimum-difference-between-largest-and-smallest-value-in-three-moves/
//
// Question ID: 1509
// Difficult  : Medium
// Solve Date : 2022/02/16 18:35

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1509. Minimum Difference Between Largest and Smallest Value
// in Three Moves|:
//
// You are given an integer array |nums|.
// In one move, you can choose one element of |nums| and change it to any value.
// Return the minimum difference between the largest and smallest value of
// |nums| after performing at most three moves.  
//

LEETCODE_BEGIN_RESOLVING(
    1509, MinimumDifferenceBetweenLargestAndSmallestValueInThreeMoves,
    Solution);

class Solution {
public:
  int minDifference(vector<int> &nums) {
    int n = nums.size();
    sort(nums.begin(), nums.end());
    if (nums.size() <= 4)
      return 0;
    return min({nums[n - 4] - nums[0], nums[n - 3] - nums[1],
                nums[n - 2] - nums[2], nums[n - 1] - nums[3]});
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |-10⁹ <= nums[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [5,3,2,4]
// Output: 0
//
// We can make at most 3 moves.
// In the first move, change 2 to 3. nums becomes [5,3,3,4].
// In the second move, change 4 to 3. nums becomes [5,3,3,3].
// In the third move, change 5 to 3. nums becomes [3,3,3,3].
// After performing 3 moves, the difference between the minimum and maximum is 3
// - 3 = 0.

LEETCODE_SOLUTION_UNITTEST(
    1509, MinimumDifferenceBetweenLargestAndSmallestValueInThreeMoves,
    example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {5, 3, 2, 4};
  int         expect   = 0;
  int         actual   = solution->minDifference(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,5,0,10,14]
// Output: 1
//
// We can make at most 3 moves.
// In the first move, change 5 to 0. nums becomes [1,0,0,10,14].
// In the second move, change 10 to 0. nums becomes [1,0,0,0,14].
// In the third move, change 14 to 1. nums becomes [1,0,0,0,1].
// After performing 3 moves, the difference between the minimum and maximum is 1
// - 0 = 0. It can be shown that there is no way to make the difference 0 in 3
// moves.

LEETCODE_SOLUTION_UNITTEST(
    1509, MinimumDifferenceBetweenLargestAndSmallestValueInThreeMoves,
    example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 5, 0, 10, 14};
  int         expect   = 1;
  int         actual   = solution->minDifference(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [3,100,20]
// Output: 0
//
// We can make at most 3 moves.
// In the first move, change 100 to 7. nums becomes [4,7,20].
// In the second move, change 20 to 7. nums becomes [4,7,7].
// In the third move, change 4 to 3. nums becomes [7,7,7].
// After performing 3 moves, the difference between the minimum and maximum is 7
// - 7 = 0.

LEETCODE_SOLUTION_UNITTEST(
    1509, MinimumDifferenceBetweenLargestAndSmallestValueInThreeMoves,
    example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 100, 20};
  int         expect   = 0;
  int         actual   = solution->minDifference(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Limit of Balls in a Bag
//
// https://leetcode.com/problems/minimum-limit-of-balls-in-a-bag/
//
// Question ID: 1760
// Difficult  : Medium
// Solve Date : 2022/07/16 15:15

#include <iosfwd>
#include <limits>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1760. Minimum Limit of Balls in a Bag|:
//
// You are given an integer array |nums| where the |iᵗʰ| bag contains |nums[i]|
// balls. You are also given an integer |maxOperations|. You can perform the
// following operation at most |maxOperations| times:
//
//  • Take any bag of balls and divide it into two new bags with a positive
//  number of balls.
//
//
//    • For example, a bag of |5| balls can become two new bags of |1| and |4|
//    balls, or two new bags of |2| and |3| balls.
//
//
// Your penalty is the maximum number of balls in a bag. You want to minimize
// your penalty after the operations. Return the minimum possible penalty after
// performing the operations.
//

LEETCODE_BEGIN_RESOLVING(1760, MinimumLimitOfBallsInABag, Solution);

class Solution {
public:
  int minimumSize(vector<int> &nums, int maxOperations) {
    int res = numeric_limits<int>::max();
    int l = 1, r = 1e9 + 1;

    while (l <= r) {
      int m   = l + (r - l) / 2;
      int opt = 0;

      for (auto &x : nums) {
        if (x > m) {
          opt += x / m;
          if (x % m == 0) {
            --opt;
          }
        }
      }

      if (opt <= maxOperations) {
        res = min(res, m);
        r   = m - 1;
      } else {
        l = m + 1;
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
// * |1 <= maxOperations, nums[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [9], maxOperations = 2
// Output: 3
//
// - Divide the bag with 9 balls into two bags of sizes 6 and 3. [9] -> [6,3].
// - Divide the bag with 6 balls into two bags of sizes 3 and 3. [6,3] ->
// [3,3,3]. The bag with the most number of balls has 3 balls, so your penalty
// is 3 and you should return 3.

LEETCODE_SOLUTION_UNITTEST(1760, MinimumLimitOfBallsInABag, example_1) {
  auto        solution      = MakeSolution();
  vector<int> nums          = {9};
  int         maxOperations = 2;
  int         expect        = 3;
  int         actual        = solution->minimumSize(nums, maxOperations);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,4,8,2], maxOperations = 4
// Output: 2
//
// - Divide the bag with 8 balls into two bags of sizes 4 and 4. [2,4,8,2] ->
// [2,4,4,4,2].
// - Divide the bag with 4 balls into two bags of sizes 2 and 2. [2,4,4,4,2] ->
// [2,2,2,4,4,2].
// - Divide the bag with 4 balls into two bags of sizes 2 and 2. [2,2,2,4,4,2]
// -> [2,2,2,2,2,4,2].
// - Divide the bag with 4 balls into two bags of sizes 2 and 2. [2,2,2,2,2,4,2]
// -> [2,2,2,2,2,2,2,2]. The bag with the most number of balls has 2 balls, so
// your penalty is 2, and you should return 2.

LEETCODE_SOLUTION_UNITTEST(1760, MinimumLimitOfBallsInABag, example_2) {
  auto        solution      = MakeSolution();
  vector<int> nums          = {2, 4, 8, 2};
  int         maxOperations = 4;
  int         expect        = 2;
  int         actual        = solution->minimumSize(nums, maxOperations);
  LCD_EXPECT_EQ(expect, actual);
}

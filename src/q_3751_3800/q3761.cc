// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Minimum Absolute Distance Between Mirror Pairs
//
// https://leetcode.com/problems/minimum-absolute-distance-between-mirror-pairs/
//
// Question ID: 3761
// Difficult  : Medium
// Solve Date : 2026/04/17 14:11

#include <iosfwd>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3761. Minimum Absolute Distance Between Mirror Pairs|:
//
// You are given an integer array |nums|.
// A mirror pair is a pair of indices |(i, j)| such that:
//
//  • |0 <= i < j < nums.length|, and
//
//  • |reverse(nums[i]) == nums[j]|, where |reverse(x)| denotes the integer
//  formed by reversing the digits of |x|. Leading zeros are omitted after
//  reversing, for example |reverse(120) = 21|.
// Return the minimum absolute distance between the indices of any mirror pair.
// The absolute distance between indices |i| and |j| is |abs(i - j)|. If no
// mirror pair exists, return |-1|.
//
//

LEETCODE_BEGIN_RESOLVING(3761, MinimumAbsoluteDistanceBetweenMirrorPairs,
                         Solution);

class Solution {
public:
  int minMirrorPairDistance(vector<int> &nums) {
    int                     res = 100000, i = 0;
    unordered_map<int, int> seen;

    for (int &n : nums) {
      int r;
      if (seen.count(n))
        res = min(res, i - seen[n]);

      for (r = 0; n; n /= 10)
        r = r * 10 + (n % 10);

      seen[r] = i++;
    }

    return -(res == 100000) | res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |1 <= nums[i] <= 10⁹|​​​​​​​
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [12,21,45,33,54]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(3761, MinimumAbsoluteDistanceBetweenMirrorPairs,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {12, 21, 45, 33, 54};
  int         expect   = 1;
  int         actual   = solution->minMirrorPairDistance(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [120,21]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(3761, MinimumAbsoluteDistanceBetweenMirrorPairs,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {120, 21};
  int         expect   = 1;
  int         actual   = solution->minMirrorPairDistance(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [21,120]
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(3761, MinimumAbsoluteDistanceBetweenMirrorPairs,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {21, 120};
  int         expect   = -1;
  int         actual   = solution->minMirrorPairDistance(nums);
  LCD_EXPECT_EQ(expect, actual);
}

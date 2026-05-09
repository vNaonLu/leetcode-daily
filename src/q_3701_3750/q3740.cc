// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Minimum Distance Between Three Equal Elements I
//
// https://leetcode.com/problems/minimum-distance-between-three-equal-elements-i/
//
// Question ID: 3740
// Difficult  : Easy
// Solve Date : 2026/04/10 18:40

#include <iosfwd>
#include <map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3740. Minimum Distance Between Three Equal Elements I|:
//
// You are given an integer array |nums|.
// A tuple |(i, j, k)| of 3 distinct indices is good if |nums[i] == nums[j] ==
// nums[k]|. The distance of a good tuple is |abs(i - j) + abs(j - k) + abs(k -
// i)|, where |abs(x)| denotes the absolute value of |x|. Return an integer
// denoting the minimum possible distance of a good tuple. If no good tuples
// exist, return |-1|.
//
//

LEETCODE_BEGIN_RESOLVING(3740, MinimumDistanceBetweenThreeEqualElementsI,
                         Solution);

class Solution {
public:
  int minimumDistance(vector<int> &nums) {
    map<int, vector<int>> idx;
    for (int i = 0; i < nums.size(); ++i) {
      idx[nums[i]].push_back(i);
    }

    optional<int> res;
    for (auto &[x, pos] : idx) {
      if (pos.size() < 3) {
        continue;
      }

      for (int i = 2; i < pos.size(); ++i) {
        int diff = pos[i] * 2 - pos[i - 2] * 2;
        res      = min(res.value_or(diff), diff);
      }
    }
    return res.value_or(-1);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n == nums.length <= 100|
// * |1 <= nums[i] <= n|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,1,1,3]
// Output: 6
//

LEETCODE_SOLUTION_UNITTEST(3740, MinimumDistanceBetweenThreeEqualElementsI,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 1, 1, 3};
  int         expect   = 6;
  int         actual   = solution->minimumDistance(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,1,2,3,2,1,2]
// Output: 8
//

LEETCODE_SOLUTION_UNITTEST(3740, MinimumDistanceBetweenThreeEqualElementsI,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 2, 3, 2, 1, 2};
  int         expect   = 8;
  int         actual   = solution->minimumDistance(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1]
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(3740, MinimumDistanceBetweenThreeEqualElementsI,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1};
  int         expect   = -1;
  int         actual   = solution->minimumDistance(nums);
  LCD_EXPECT_EQ(expect, actual);
}

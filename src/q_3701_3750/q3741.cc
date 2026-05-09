// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Minimum Distance Between Three Equal Elements II
//
// https://leetcode.com/problems/minimum-distance-between-three-equal-elements-ii/
//
// Question ID: 3741
// Difficult  : Medium
// Solve Date : 2026/04/11 10:15

#include <iosfwd>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3741. Minimum Distance Between Three Equal Elements II|:
//
// You are given an integer array |nums|.
// A tuple |(i, j, k)| of 3 distinct indices is good if |nums[i] == nums[j] ==
// nums[k]|. The distance of a good tuple is |abs(i - j) + abs(j - k) + abs(k -
// i)|, where |abs(x)| denotes the absolute value of |x|. Return an integer
// denoting the minimum possible distance of a good tuple. If no good tuples
// exist, return |-1|.
//
//

LEETCODE_BEGIN_RESOLVING(3741, MinimumDistanceBetweenThreeEqualElementsII,
                         Solution);

class Solution {
public:
  int minimumDistance(vector<int> &nums) {
    unordered_map<int, vector<int>> mp;
    int                             n = nums.size();

    for (int i = 0; i < n; i++) {
      mp[nums[i]].push_back(i);
    }

    int mini = numeric_limits<int>::max();

    for (auto &it : mp) {
      vector<int> &temp = it.second;
      int          m    = temp.size();

      if (m >= 3) {
        for (int i = 0; i < m - 2; i++) {
          int a = temp[i];
          int b = temp[i + 1];
          int c = temp[i + 2];

          int diff = 2 * (max({a, b, c}) - min({a, b, c}));
          mini     = min(mini, diff);
        }
      }
    }

    return mini == numeric_limits<int>::max() ? -1 : mini;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n == nums.length <= 10⁵|
// * |1 <= nums[i] <= n|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,1,1,3]
// Output: 6
//

LEETCODE_SOLUTION_UNITTEST(3741, MinimumDistanceBetweenThreeEqualElementsII,
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

LEETCODE_SOLUTION_UNITTEST(3741, MinimumDistanceBetweenThreeEqualElementsII,
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

LEETCODE_SOLUTION_UNITTEST(3741, MinimumDistanceBetweenThreeEqualElementsII,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1};
  int         expect   = -1;
  int         actual   = solution->minimumDistance(nums);
  LCD_EXPECT_EQ(expect, actual);
}

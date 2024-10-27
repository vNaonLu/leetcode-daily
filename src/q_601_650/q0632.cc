// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Smallest Range Covering Elements from K Lists
//
// https://leetcode.com/problems/smallest-range-covering-elements-from-k-lists/
//
// Question ID: 632
// Difficult  : Hard
// Solve Date : 2024/10/13 22:33

#include <algorithm>
#include <iosfwd>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |632. Smallest Range Covering Elements from K Lists|:
//
// You have |k| lists of sorted integers in non-decreasing order. Find the
// smallest range that includes at least one number from each of the |k| lists.
// We define the range |[a, b]| is smaller than range |[c, d]| if |b - a < d -
// c| or |a < c| if |b - a == d - c|.
//
//

LEETCODE_BEGIN_RESOLVING(632, SmallestRangeCoveringElementsFromKLists,
                         Solution);

class Solution {
public:
  vector<int> smallestRange(vector<vector<int>> &nums) {
    vector<pair<int, int>> merged;
    for (int i = 0; i < nums.size(); ++i) {
      for (auto x : nums[i]) {
        merged.emplace_back(x, i);
      }
    }
    sort(merged.begin(), merged.end());
    unordered_map<int, int> count;
    int                     lo      = 0;
    int                     hi      = 0;
    int                     k       = nums.size();
    int                     covered = 0;
    int                     mn      = numeric_limits<int>::max();
    vector<int>             res{0, 0};
    while (hi < merged.size()) {
      int idx = merged[hi].second;
      ++count[idx];
      if (count[idx] == 1) {
        ++covered;
      }
      ++hi;

      while (covered == k) {
        int r_lo = merged[lo].first;
        int r_hi = merged[hi - 1].first;

        if (r_hi - r_lo < mn) {
          mn     = r_hi - r_lo;
          res[0] = r_lo;
          res[1] = r_hi;
        }

        int lo_idx = merged[lo].second;
        --count[lo_idx];
        if (count[lo_idx] == 0) {
          --covered;
        }
        ++lo;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |nums.length == k|
// * |1 <= k <= 3500|
// * |1 <= nums[i].length <= 50|
// * |-10⁵ <= nums[i][j] <= 10⁵|
// * |nums[i]| is sorted in non-decreasing order.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [[4,10,15,24,26],[0,9,12,20],[5,18,22,30]]
// Output: [20,24]
//

LEETCODE_SOLUTION_UNITTEST(632, SmallestRangeCoveringElementsFromKLists,
                           example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> nums     = {
      {4, 10, 15, 24, 26},
      {0, 9, 12, 20},
      {5, 18, 22, 30}
  };
  vector<int> expect = {20, 24};
  vector<int> actual = solution->smallestRange(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [[1,2,3],[1,2,3],[1,2,3]]
// Output: [1,1]
//

LEETCODE_SOLUTION_UNITTEST(632, SmallestRangeCoveringElementsFromKLists,
                           example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> nums     = {
      {1, 2, 3},
      {1, 2, 3},
      {1, 2, 3}
  };
  vector<int> expect = {1, 1};
  vector<int> actual = solution->smallestRange(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// Copyright 2025 Naon Lu
//
// This file describes the solution of
// House Robber IV
//
// https://leetcode.com/problems/house-robber-iv/
//
// Question ID: 2560
// Difficult  : Medium
// Solve Date : 2025/03/16 03:37

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2560. House Robber IV|:
//
// There are several consecutive houses along a street, each of which has some
// money inside. There is also a robber, who wants to steal money from the
// homes, but he refuses to steal from adjacent homes. The capability of the
// robber is the maximum amount of money he steals from one house of all the
// houses he robbed. You are given an integer array |nums| representing how much
// money is stashed in each house. More formally, the |iᵗʰ| house from the left
// has |nums[i]| dollars. You are also given an integer |k|, representing the
// minimum number of houses the robber will steal from. It is always possible to
// steal at least |k| houses. Return the minimum capability of the robber out of
// all the possible ways to steal at least |k| houses.
//
//

LEETCODE_BEGIN_RESOLVING(2560, HouseRobberIV, Solution);

class Solution {
public:
  int minCapability(vector<int> &nums, int k) {
    int lo  = 1;
    int hi  = *max_element(nums.begin(), nums.end());
    int res = hi;
    while (lo <= hi) {
      int mid = lo + (hi - lo) / 2;
      if (canRob(nums, mid, k)) {
        res = mid;
        hi  = mid - 1;
      } else {
        lo = mid + 1;
      }
    }
    return res;
  }

private:
  bool canRob(vector<int> const &nums, int mid, int k) {
    int cnt = 0;
    int n   = nums.size();
    for (int i = 0; i < n; ++i) {
      if (nums[i] <= mid) {
        ++cnt;
        ++i;
      }
    }
    return cnt >= k;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |1 <= nums[i] <= 10⁹|
// * |1 <= k <= (nums.length + 1)/2|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,3,5,9], k = 2
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(2560, HouseRobberIV, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 3, 5, 9};
  int         k        = 2;
  int         expect   = 5;
  int         actual   = solution->minCapability(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,7,9,3,1], k = 2
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(2560, HouseRobberIV, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 7, 9, 3, 1};
  int         k        = 2;
  int         expect   = 2;
  int         actual   = solution->minCapability(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

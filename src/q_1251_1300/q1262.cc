// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Greatest Sum Divisible by Three
//
// https://leetcode.com/problems/greatest-sum-divisible-by-three/
//
// Question ID: 1262
// Difficult  : Medium
// Solve Date : 2025/11/23 13:40

#include <algorithm>
#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1262. Greatest Sum Divisible by Three|:
//
// Given an integer array |nums|, return the maximum possible sum of elements of
// the array such that it is divisible by three.
//
//

LEETCODE_BEGIN_RESOLVING(1262, GreatestSumDivisibleByThree, Solution);

class Solution {
public:
  int maxSumDivThree(vector<int> &nums) {
    sort(nums.begin(), nums.end());
    vector<int> g[2];
    g[0] = {0};
    g[1] = {0};

    int sum = 0;
    for (auto x : nums) {
      sum += x;
      if (x % 3 == 1 && g[0].size() < 3)
        g[0].push_back(x);
      if (x % 3 == 2 && g[1].size() < 3)
        g[1].push_back(x);
    }
    int ans = 0;

    int s1 = 0;
    for (auto p : g[0]) {
      s1 += p;
      int s2 = 0;
      for (auto q : g[1]) {
        s2 += q;
        if ((sum - s1 - s2) % 3 == 0) {
          ans = max(ans, sum - s1 - s2);
        }
      }
    }
    return ans;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 4 * 10⁴|
// * |1 <= nums[i] <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [3,6,5,1,8]
// Output: 18
//

LEETCODE_SOLUTION_UNITTEST(1262, GreatestSumDivisibleByThree, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 6, 5, 1, 8};
  int         expect   = 18;
  int         actual   = solution->maxSumDivThree(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [4]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(1262, GreatestSumDivisibleByThree, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4};
  int         expect   = 0;
  int         actual   = solution->maxSumDivThree(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,2,3,4,4]
// Output: 12
//

LEETCODE_SOLUTION_UNITTEST(1262, GreatestSumDivisibleByThree, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4, 4};
  int         expect   = 12;
  int         actual   = solution->maxSumDivThree(nums);
  LCD_EXPECT_EQ(expect, actual);
}

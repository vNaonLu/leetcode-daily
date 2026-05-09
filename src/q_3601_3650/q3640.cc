// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Trionic Array II
//
// https://leetcode.com/problems/trionic-array-ii/
//
// Question ID: 3640
// Difficult  : Hard
// Solve Date : 2026/02/04 21:42

#include <iosfwd>
#include <tuple>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3640. Trionic Array II|:
//
// You are given an integer array |nums| of length |n|.
// A trionic subarray is a contiguous subarray |nums[l...r]| (with |0 <= l < r <
// n|) for which there exist indices |l < p < q < r| such that:
//
//  • |nums[l...p]| is strictly increasing,
//
//  • |nums[p...q]| is strictly decreasing,
//
//  • |nums[q...r]| is strictly increasing.
// Return the maximum sum of any trionic subarray in |nums|.
//
//

LEETCODE_BEGIN_RESOLVING(3640, TrionicArrayII, Solution);

class Solution {
public:
  vector<tuple<int, int, long long>> decompose(vector<int> &nums) {
    int                                n = (int)nums.size();
    vector<tuple<int, int, long long>> subarrays;

    int       l   = 0;
    long long sum = nums[0];

    for (int i = 1; i < n; i++) {
      if (nums[i - 1] <= nums[i]) {
        subarrays.push_back({l, i - 1, sum});
        l   = i;
        sum = 0;
      }
      sum += nums[i];
    }
    subarrays.push_back({l, n - 1, sum});
    return subarrays;
  }
  long long maxSumTrionic(vector<int> &nums) {
    int             n = (int)nums.size();
    vector<int64_t> maxEndingAt(n);
    for (int i = 0; i < n; i++) {
      maxEndingAt[i] = nums[i];
      if (i > 0 && nums[i - 1] < nums[i]) {
        if (maxEndingAt[i - 1] > 0) {
          maxEndingAt[i] += maxEndingAt[i - 1];
        }
      }
    }
    vector<int64_t> maxStartingAt(n);
    for (int i = n - 1; i >= 0; i--) {
      maxStartingAt[i] = nums[i];
      if (i < n - 1 && nums[i] < nums[i + 1]) {
        if (maxStartingAt[i + 1] > 0) {
          maxStartingAt[i] += maxStartingAt[i + 1];
        }
      }
    }
    vector<tuple<int, int, long long>> PQS = decompose(nums);
    long long                          ans = numeric_limits<int64_t>::min();
    for (auto [p, q, sum] : PQS) {

      if (p > 0 && nums[p - 1] < nums[p] && q < n - 1 &&
          nums[q] < nums[q + 1] && p < q) {
        ans = max(ans, maxEndingAt[p - 1] + sum + maxStartingAt[q + 1]);
      }
    }
    return ans;
  }
};

LEETCODE_END_RESOLVING(Solution);

// [Example #1]
//  Input: nums = [0,-2,-1,-3,0,2,-1]
// Output: -4
//

LEETCODE_SOLUTION_UNITTEST(3640, TrionicArrayII, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {0, -2, -1, -3, 0, 2, -1};
  long long   expect   = -4;
  long long   actual   = solution->maxSumTrionic(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,4,2,7]
// Output: 14
//

LEETCODE_SOLUTION_UNITTEST(3640, TrionicArrayII, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 4, 2, 7};
  long long   expect   = 14;
  long long   actual   = solution->maxSumTrionic(nums);
  LCD_EXPECT_EQ(expect, actual);
}

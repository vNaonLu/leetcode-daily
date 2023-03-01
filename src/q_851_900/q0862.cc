// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Shortest Subarray with Sum at Least K
//
// https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/
//
// Question ID: 862
// Difficult  : Hard
// Solve Date : 2022/02/21 22:34

#include <array>
#include <deque>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |862. Shortest Subarray with Sum at Least K|:
//
// Given an integer array |nums| and an integer |k|, return the length of the
// shortest non-empty subarray of |nums| with a sum of at least |k|. If there is
// no such subarray, return |-1|. A subarray is a contiguous part of an array.  
//

LEETCODE_BEGIN_RESOLVING(862, ShortestSubarrayWithSumAtLeastK, Solution);

class Solution {
public:
  int shortestSubarray(vector<int> &nums, int k) {
    int               res = nums.size() + 1;
    deque<int>        q;
    vector<long long> summaries(nums.size() + 1);
    for (int i = 0; i < nums.size(); ++i) {
      summaries[i + 1] = summaries[i] + nums[i];
    }
    for (int i = 0; i < summaries.size(); ++i) {
      while (q.empty() == false && summaries[i] <= summaries[q.back()]) {
        q.pop_back();
      }
      while (q.empty() == false && summaries[i] >= summaries[q.front()] + k) {
        res = min(res, i - q.front());
        q.pop_front();
      }
      q.push_back(i);
    }
    return res == nums.size() + 1 ? -1 : res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |-10⁵ <= nums[i] <= 10⁵|
// * |1 <= k <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1], k = 1
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(862, ShortestSubarrayWithSumAtLeastK, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1};
  int         k        = 1;
  int         expect   = 1;
  int         actual   = solution->shortestSubarray(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2], k = 4
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(862, ShortestSubarrayWithSumAtLeastK, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2};
  int         k        = 4;
  int         expect   = -1;
  int         actual   = solution->shortestSubarray(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [2,-1,2], k = 3
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(862, ShortestSubarrayWithSumAtLeastK, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, -1, 2};
  int         k        = 3;
  int         expect   = 3;
  int         actual   = solution->shortestSubarray(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Longest Subsequence With Limited Sum
//
// https://leetcode.com/problems/longest-subsequence-with-limited-sum/
//
// Question ID: 2389
// Difficult  : Easy
// Solve Date : 2022/12/25 14:43

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2389. Longest Subsequence With Limited Sum|:
//
// You are given an integer array |nums| of length |n|, and an integer array
// |queries| of length |m|. Return an array |answer| of length |m| where
// |answer[i]| is the maximum size of a subsequence that you can take from
// |nums| such that the sum of its elements is less than or equal to
// |queries[i]|. A subsequence is an array that can be derived from another
// array by deleting some or no elements without changing the order of the
// remaining elements.
//

LEETCODE_BEGIN_RESOLVING(2389, LongestSubsequenceWithLimitedSum, Solution);

class Solution {
private:
  vector<int> getPreSum(const vector<int> &n) {
    auto res = n;
    for (int i = 1; i < res.size(); ++i) {
      res[i] += res[i - 1];
    }
    return res;
  }

public:
  vector<int> answerQueries(vector<int> &nums, vector<int> &queries) {
    sort(nums.begin(), nums.end());
    auto presum = getPreSum(nums);
    auto res    = vector<int>(queries.size(), 0);
    for (int i = 0; i < res.size(); ++i) {
      for (int j = 0; j < nums.size(); ++j) {
        if (presum[j] <= queries[i]) {
          res[i] = j + 1;
        } else {
          break;
        }
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == nums.length|
// * |m == queries.length|
// * |1 <= n, m <= 1000|
// * |1 <= nums[i], queries[i] <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [4,5,2,1], queries = [3,10,21]
// Output: [2,3,4]
//
// We answer the queries as follows:
// - The subsequence [2,1] has a sum less than or equal to 3. It can be proven
// that 2 is the maximum size of such a subsequence, so answer[0] = 2.
// - The subsequence [4,5,1] has a sum less than or equal to 10. It can be
// proven that 3 is the maximum size of such a subsequence, so answer[1] = 3.
// - The subsequence [4,5,2,1] has a sum less than or equal to 21. It can be
// proven that 4 is the maximum size of such a subsequence, so answer[2] = 4.

LEETCODE_SOLUTION_UNITTEST(2389, LongestSubsequenceWithLimitedSum, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 5, 2, 1};
  vector<int> queries  = {3, 10, 21};
  vector<int> expect   = {2, 3, 4};
  vector<int> actual   = solution->answerQueries(nums, queries);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,3,4,5], queries = [1]
// Output: [0]
//
// The empty subsequence is the only subsequence that has a sum less than or
// equal to 1, so answer[0] = 0.

LEETCODE_SOLUTION_UNITTEST(2389, LongestSubsequenceWithLimitedSum, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 3, 4, 5};
  vector<int> queries  = {1};
  vector<int> expect   = {0};
  vector<int> actual   = solution->answerQueries(nums, queries);
  LCD_EXPECT_EQ(expect, actual);
}

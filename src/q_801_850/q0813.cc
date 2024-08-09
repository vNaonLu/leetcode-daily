// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Largest Sum of Averages
//
// https://leetcode.com/problems/largest-sum-of-averages/
//
// Question ID: 813
// Difficult  : Medium
// Solve Date : 2024/08/05 22:09

#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |813. Largest Sum of Averages|:
//
// You are given an integer array |nums| and an integer |k|. You can partition
// the array into at most |k| non-empty adjacent subarrays. The score of a
// partition is the sum of the averages of each subarray. Note that the
// partition must use every integer in |nums|, and that the score is not
// necessarily an integer. Return the maximum score you can achieve of all the
// possible partitions. Answers within |10⁻⁶| of the actual answer will be
// accepted.
//
//

LEETCODE_BEGIN_RESOLVING(813, LargestSumOfAverages, Solution);

class Solution {
public:
  double largestSumOfAverages(vector<int> &nums, int k) {
    int n = nums.size();
    partial_sum(nums.begin(), nums.end(), nums.begin());
    vector<vector<double>> dp(n + 1, vector<double>(k + 1, -1));
    return helper(nums, &dp, 0, k - 1);
  }

private:
  double helper(vector<int> const &nums, vector<vector<double>> *dp, int id,
                int k) {
    if (k == 0) {
      int sum = nums.back() - (id ? nums[id - 1] : 0);
      int len = nums.size() - id;
      return sum * 1.0 / len;
    }
    double *res = &(*dp)[id][k];
    if (*res != -1) {
      return *res;
    }

    for (int i = id; i < nums.size(); ++i) {
      int    sum = nums[i] - (id ? nums[id - 1] : 0);
      int    len = i - id + 1;
      double avg = sum * 1.0 / len;
      *res       = max(*res, avg + helper(nums, dp, i + 1, k - 1));
    }
    return *res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 100|
// * |1 <= nums[i] <= 10⁴|
// * |1 <= k <= nums.length|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [9,1,2,3,9], k = 3
// Output: 20.00000
//

LEETCODE_SOLUTION_UNITTEST(813, LargestSumOfAverages, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {9, 1, 2, 3, 9};
  int         k        = 3;
  double      expect   = 20.00000;
  double      actual   = solution->largestSumOfAverages(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,3,4,5,6,7], k = 4
// Output: 20.50000
//

LEETCODE_SOLUTION_UNITTEST(813, LargestSumOfAverages, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4, 5, 6, 7};
  int         k        = 4;
  double      expect   = 20.50000;
  double      actual   = solution->largestSumOfAverages(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

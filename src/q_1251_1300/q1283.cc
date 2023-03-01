// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find the Smallest Divisor Given a Threshold
//
// https://leetcode.com/problems/find-the-smallest-divisor-given-a-threshold/
//
// Question ID: 1283
// Difficult  : Medium
// Solve Date : 2022/07/18 18:54

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1283. Find the Smallest Divisor Given a Threshold|:
//
// Given an array of integers |nums| and an integer |threshold|, we will choose
// a positive integer |divisor|, divide all the array by it, and sum the
// division's result. Find the smallest |divisor| such that the result mentioned
// above is less than or equal to |threshold|. Each result of the division is
// rounded to the nearest integer greater than or equal to that element. (For
// example: |7/3 = 3| and |10/2 = 5|). The test cases are generated sothat there
// will be an answer.
//

LEETCODE_BEGIN_RESOLVING(1283, FindTheSmallestDivisorGivenAThreshold, Solution);

class Solution {
private:
  bool helper(vector<int> &vs, int threshold, int curr) {
    int res = 0;
    for (auto &x : vs) {
      if (x % curr == 0) {
        res += x / curr;
      } else {
        res += x / curr + 1;
      }
    }

    return res <= threshold;
  }

public:
  int smallestDivisor(vector<int> &nums, int threshold) {
    int L = 1, R = *max_element(nums.begin(), nums.end());
    while (L <= R) {
      int M = L + (R - L) / 2;

      if (helper(nums, threshold, M)) {
        R = M - 1;
      } else {
        L = M + 1;
      }
    }

    return R + 1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 5 * 10⁴|
// * |1 <= nums[i] <= 10⁶|
// * |nums.length <= threshold <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,5,9], threshold = 6
// Output: 5
//
// We can get a sum to 17 (1+2+5+9) if the divisor is 1.
// If the divisor is 4 we can get a sum of 7 (1+1+2+3) and if the divisor is 5
// the sum will be 5 (1+1+1+2).

LEETCODE_SOLUTION_UNITTEST(1283, FindTheSmallestDivisorGivenAThreshold,
                           example_1) {
  auto        solution  = MakeSolution();
  vector<int> nums      = {1, 2, 5, 9};
  int         threshold = 6;
  int         expect    = 5;
  int         actual    = solution->smallestDivisor(nums, threshold);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [44,22,33,11,1], threshold = 5
// Output: 44
//

LEETCODE_SOLUTION_UNITTEST(1283, FindTheSmallestDivisorGivenAThreshold,
                           example_2) {
  auto        solution  = MakeSolution();
  vector<int> nums      = {44, 22, 33, 11, 1};
  int         threshold = 5;
  int         expect    = 44;
  int         actual    = solution->smallestDivisor(nums, threshold);
  LCD_EXPECT_EQ(expect, actual);
}

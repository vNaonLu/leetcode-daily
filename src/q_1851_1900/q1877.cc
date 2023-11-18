// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimize Maximum Pair Sum in Array
//
// https://leetcode.com/problems/minimize-maximum-pair-sum-in-array/
//
// Question ID: 1877
// Difficult  : Medium
// Solve Date : 2023/11/18 12:49

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1877. Minimize Maximum Pair Sum in Array|:
//
// The pair sum of a pair |(a,b)| is equal to |a + b|. The maximum pair sum is
// the largest pair sum in a list of pairs.
//
//
//
//  • For example, if we have pairs |(1,5)|, |(2,3)|, and |(4,4)|, the maximum
//  pair sum would be |max(1+5, 2+3, 4+4) = max(6, 5, 8) = 8|.
//
//
// Given an array |nums| of even length |n|, pair up the elements of |nums| into
// |n / 2| pairs such that:
//
//
//
//  • Each element of |nums| is in exactly one pair, and
//
//  • The maximum pair sum is minimized.
//
//
// Return the minimized maximum pair sum after optimally pairing up the
// elements.
//
//
//

LEETCODE_BEGIN_RESOLVING(1877, MinimizeMaximumPairSumInArray, Solution);

class Solution {
public:
  int minPairSum(vector<int> &nums) {
    sort(nums.begin(), nums.end());
    int lo  = 0;
    int hi  = nums.size() - 1;
    int res = 0;
    while (lo < hi) {
      res = max(res, nums[lo++] + nums[hi--]);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == nums.length|
// * |2 <= n <= 10⁵|
// * |n| is even.
// * |1 <= nums[i] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [3,5,2,3]
// Output: 7
//
// The elements can be paired up into pairs (3,3) and (5,2).
// The maximum pair sum is max(3+3, 5+2) = max(6, 7) = 7.

LEETCODE_SOLUTION_UNITTEST(1877, MinimizeMaximumPairSumInArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 5, 2, 3};
  int         expect   = 7;
  int         actual   = solution->minPairSum(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [3,5,4,2,4,6]
// Output: 8
//
// The elements can be paired up into pairs (3,5), (4,4), and (6,2).
// The maximum pair sum is max(3+5, 4+4, 6+2) = max(8, 8, 8) = 8.

LEETCODE_SOLUTION_UNITTEST(1877, MinimizeMaximumPairSumInArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 5, 4, 2, 4, 6};
  int         expect   = 8;
  int         actual   = solution->minPairSum(nums);
  LCD_EXPECT_EQ(expect, actual);
}

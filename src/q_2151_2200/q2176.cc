// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Count Equal and Divisible Pairs in an Array
//
// https://leetcode.com/problems/count-equal-and-divisible-pairs-in-an-array/
//
// Question ID: 2176
// Difficult  : Easy
// Solve Date : 2023/03/16 15:21

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2176. Count Equal and Divisible Pairs in an Array|:
//
// Given a 0-indexed integer array |nums| of length |n| and an integer |k|,
// return the number of pairs |(i, j)| where |0 <= i < j < n|, such that
// |nums[i] == nums[j]| and |(i * j)| is divisible by |k|.
//

LEETCODE_BEGIN_RESOLVING(2176, CountEqualAndDivisiblePairsInAnArray, Solution);

class Solution {
public:
  int countPairs(vector<int> &nums, int k) {
    int res = 0;
    for (int i = 0; i < nums.size(); ++i) {
      for (int j = i + 1; j < nums.size(); ++j) {
        if (nums[i] == nums[j] && ((i * j) % k == 0)) {
          ++res;
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
// * |1 <= nums.length <= 100|
// * |1 <= nums[i], k <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [3,1,2,2,2,1,3], k = 2
// Output: 4
//
// There are 4 pairs that meet all the requirements:
// - nums[0] == nums[6], and 0 * 6 == 0, which is divisible by 2.
// - nums[2] == nums[3], and 2 * 3 == 6, which is divisible by 2.
// - nums[2] == nums[4], and 2 * 4 == 8, which is divisible by 2.
// - nums[3] == nums[4], and 3 * 4 == 12, which is divisible by 2.

LEETCODE_SOLUTION_UNITTEST(2176, CountEqualAndDivisiblePairsInAnArray,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 1, 2, 2, 2, 1, 3};
  int         k        = 2;
  int         expect   = 4;
  int         actual   = solution->countPairs(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,3,4], k = 1
// Output: 0
//
// Since no value in nums is repeated, there are no pairs (i,j) that meet all
// the requirements.

LEETCODE_SOLUTION_UNITTEST(2176, CountEqualAndDivisiblePairsInAnArray,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4};
  int         k        = 1;
  int         expect   = 0;
  int         actual   = solution->countPairs(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

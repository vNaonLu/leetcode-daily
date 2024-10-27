// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Make Sum Divisible by P
//
// https://leetcode.com/problems/make-sum-divisible-by-p/
//
// Question ID: 1590
// Difficult  : Medium
// Solve Date : 2024/10/03 15:23

#include <iosfwd>
#include <numeric>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1590. Make Sum Divisible by P|:
//
// Given an array of positive integers |nums|, remove the smallest subarray
// (possibly empty) such that the sum of the remaining elements is divisible by
// |p|. It is not allowed to remove the whole array. Return the length of the
// smallest subarray that you need to remove, or |-1| if it's impossible. A
// subarray is defined as a contiguous block of elements in the array.
//
//

LEETCODE_BEGIN_RESOLVING(1590, MakeSumDivisibleByP, Solution);

class Solution {
public:
  int minSubarray(vector<int> &nums, int p) {
    int64_t sum = accumulate(nums.begin(), nums.end(), 0l);

    int rem = sum % p;
    if (rem == 0) {
      return 0;
    }

    unordered_map<int, int> prefix;
    prefix[0]          = -1;
    int64_t prefix_sum = 0;
    int     res        = nums.size();
    for (int i = 0; i < nums.size(); ++i) {
      prefix_sum += nums[i];
      int curr = prefix_sum % p;
      int targ = (curr - rem + p) % p;

      if (auto find = prefix.find(targ); find != prefix.end()) {
        res = min(res, i - find->second);
      }

      prefix[curr] = i;
    }

    return res == nums.size() ? -1 : res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |1 <= nums[i] <= 10⁹|
// * |1 <= p <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [3,1,4,2], p = 6
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(1590, MakeSumDivisibleByP, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 1, 4, 2};
  int         p        = 6;
  int         expect   = 1;
  int         actual   = solution->minSubarray(nums, p);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [6,3,5,2], p = 9
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(1590, MakeSumDivisibleByP, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {6, 3, 5, 2};
  int         p        = 9;
  int         expect   = 2;
  int         actual   = solution->minSubarray(nums, p);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,2,3], p = 3
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(1590, MakeSumDivisibleByP, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3};
  int         p        = 3;
  int         expect   = 0;
  int         actual   = solution->minSubarray(nums, p);
  LCD_EXPECT_EQ(expect, actual);
}

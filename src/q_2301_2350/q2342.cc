// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Max Sum of a Pair With Equal Sum of Digits
//
// https://leetcode.com/problems/max-sum-of-a-pair-with-equal-sum-of-digits/
//
// Question ID: 2342
// Difficult  : Medium
// Solve Date : 2025/02/12 21:00

#include <algorithm>
#include <iosfwd>
#include <map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2342. Max Sum of a Pair With Equal Sum of Digits|:
//
// You are given a 0-indexed array |nums| consisting of positive integers. You
// can choose two indices |i| and |j|, such that |i != j|, and the sum of digits
// of the number |nums[i]| is equal to that of |nums[j]|. Return the maximum
// value of |nums[i] + nums[j]| that you can obtain over all possible indices
// |i| and |j| that satisfy the conditions.
//
//

LEETCODE_BEGIN_RESOLVING(2342, MaxSumOfAPairWithEqualSumOfDigits, Solution);

class Solution {
public:
  int maximumSum(vector<int> &nums) {
    map<int, vector<int>> mp;
    for (auto x : nums) {
      int d = 0;
      int p = x;
      while (p) {
        d += p % 10;
        p /= 10;
      }

      mp[d].emplace_back(x);
    }

    for (auto &[_, v] : mp) {
      sort(v.begin(), v.end());
    }

    int res = -1;
    for (auto &[_, v] : mp) {
      if (v.size() < 2) {
        continue;
      }

      res = max<int>(res, v.back() + v[v.size() - 2]);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |1 <= nums[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [18,43,36,13,7]
// Output: 54
//

LEETCODE_SOLUTION_UNITTEST(2342, MaxSumOfAPairWithEqualSumOfDigits, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {18, 43, 36, 13, 7};
  int         expect   = 54;
  int         actual   = solution->maximumSum(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [10,12,19,14]
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(2342, MaxSumOfAPairWithEqualSumOfDigits, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {10, 12, 19, 14};
  int         expect   = -1;
  int         actual   = solution->maximumSum(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input:
//  [368,369,307,304,384,138,90,279,35,396,114,328,251,364,300,191,438,467,183]
// Output: 835
//

LEETCODE_SOLUTION_UNITTEST(2342, MaxSumOfAPairWithEqualSumOfDigits,
                           extra_testcase_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {368, 369, 307, 304, 384, 138, 90,  279, 35, 396,
                          114, 328, 251, 364, 300, 191, 438, 467, 183};
  int         expect   = 835;
  int         actual   = solution->maximumSum(nums);
  LCD_EXPECT_EQ(expect, actual);
}

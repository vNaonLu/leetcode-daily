// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Find the Sum of Encrypted Integers
//
// https://leetcode.com/problems/find-the-sum-of-encrypted-integers/
//
// Question ID: 3079
// Difficult  : Easy
// Solve Date : 2024/03/17 14:45

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3079. Find the Sum of Encrypted Integers|:
//
// You are given an integer array |nums| containing positive integers. We define
// a function |encrypt| such that |encrypt(x)| replaces every digit in |x| with
// the largest digit in |x|. For example, |encrypt(523) = 555| and |encrypt(213)
// = 333|. Return the sum of encrypted elements.
//
//

LEETCODE_BEGIN_RESOLVING(3079, FindTheSumOfEncryptedIntegers, Solution);

class Solution {
public:
  int sumOfEncryptedInt(vector<int> &nums) {
    int res = 0;
    for (auto x : nums) {
      res += encrypt(x);
    }
    return res;
  }

private:
  int encrypt(int x) {
    int d = 0;
    int m = 0;
    while (x) {
      m = max(m, x % 10);
      x /= 10;
      ++d;
    }
    while (d) {
      x = x * 10 + m;
      --d;
    }
    return x;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 50|
// * |1 <= nums[i] <= 1000|
///////////////////////////////////////////////////////////////////////////////

LEETCODE_SOLUTION_UNITTEST(3079, FindTheSumOfEncryptedIntegers, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3};
  int         expect   = 6;
  int         actual   = solution->sumOfEncryptedInt(nums);
  LCD_EXPECT_EQ(expect, actual);
}

LEETCODE_SOLUTION_UNITTEST(3079, FindTheSumOfEncryptedIntegers, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {10, 21, 31};
  int         expect   = 66;
  int         actual   = solution->sumOfEncryptedInt(nums);
  LCD_EXPECT_EQ(expect, actual);
}

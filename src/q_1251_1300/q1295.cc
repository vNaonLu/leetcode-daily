// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find Numbers with Even Number of Digits
//
// https://leetcode.com/problems/find-numbers-with-even-number-of-digits/
//
// Question ID: 1295
// Difficult  : Easy
// Solve Date : 2022/10/24 21:19

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1295. Find Numbers with Even Number of Digits|:
//
// Given an array |nums| of integers, return how many of them contain an even
// number of digits.
//

LEETCODE_BEGIN_RESOLVING(1295, FindNumbersWithEvenNumberOfDigits, Solution);

class Solution {
private:
  bool isEvenDigit(int x) {
    auto res = (int)0;
    do {
      ++res;
      x /= 10;
    } while (x != 0);
    return (res & 1) == 0;
  }

public:
  int findNumbers(vector<int> &nums) {
    auto res = (int)0;
    for (auto x : nums) {
      if (isEvenDigit(x)) {
        ++res;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 500|
// * |1 <= nums[i] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [12,345,2,6,7896]
// Output: 2
// Explanation:
// 12 contains 2 digits (even number of digits).
// 345 contains 3 digits (odd number of digits).
// 2 contains 1 digit (odd number of digits).
// 6 contains 1 digit (odd number of digits).
// 7896 contains 4 digits (even number of digits).
// Therefore only 12 and 7896 contain an even number of digits.
//

LEETCODE_SOLUTION_UNITTEST(1295, FindNumbersWithEvenNumberOfDigits, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {12, 345, 2, 6, 7896};
  int         expect   = 2;
  int         actual   = solution->findNumbers(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [555,901,482,1771]
// Output: 1
//
// Only 1771 contains an even number of digits.

LEETCODE_SOLUTION_UNITTEST(1295, FindNumbersWithEvenNumberOfDigits, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {555, 901, 482, 1771};
  int         expect   = 1;
  int         actual   = solution->findNumbers(nums);
  LCD_EXPECT_EQ(expect, actual);
}

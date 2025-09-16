// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Replace Non-Coprime Numbers in Array
//
// https://leetcode.com/problems/replace-non-coprime-numbers-in-array/
//
// Question ID: 2197
// Difficult  : Hard
// Solve Date : 2025/09/16 10:51

#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2197. Replace Non-Coprime Numbers in Array|:
//
// You are given an array of integers |nums|. Perform the following steps:
//
//  1. Find any two adjacent numbers in |nums| that are non-coprime.
//
//  2. If no such numbers are found, stop the process.
//
//  3. Otherwise, delete the two numbers and replace them with their LCM (Least
//  Common Multiple).
//
//  4. Repeat this process as long as you keep finding two adjacent non-coprime
//  numbers.
// Return the final modified array. It can be shown that replacing adjacent
// non-coprime numbers in any arbitrary order will lead to the same result. The
// test cases are generated such that the values in the final array are less
// than or equal to |10⁸|. Two values |x| and |y| are non-coprime if |GCD(x, y)
// > 1| where |GCD(x, y)| is the Greatest Common Divisor of |x| and |y|.
//
//

LEETCODE_BEGIN_RESOLVING(2197, ReplaceNonCoprimeNumbersInArray, Solution);

class Solution {
public:
  vector<int> replaceNonCoprimes(vector<int> &nums) {
    vector<int> result;
    for (int num : nums) {
      result.push_back(num);
      while (result.size() > 1) {
        int a = result.back();
        int b = result[result.size() - 2];
        int g = gcd(a, b);
        if (g > 1) {
          result.pop_back();
          result.pop_back();
          long long lcm = (long long)a / g * b;
          result.push_back((int)lcm);
        } else {
          break;
        }
      }
    }
    return result;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |1 <= nums[i] <= 10⁵|
// * The test cases are generated such that the values in the final array are
// less than or equal to |10⁸|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [6,4,3,2,7,6,2]
// Output: [12,7,6]
//

LEETCODE_SOLUTION_UNITTEST(2197, ReplaceNonCoprimeNumbersInArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {6, 4, 3, 2, 7, 6, 2};
  vector<int> expect   = {12, 7, 6};
  vector<int> actual   = solution->replaceNonCoprimes(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,2,1,1,3,3,3]
// Output: [2,1,1,3]
//

LEETCODE_SOLUTION_UNITTEST(2197, ReplaceNonCoprimeNumbersInArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 2, 1, 1, 3, 3, 3};
  vector<int> expect   = {2, 1, 1, 3};
  vector<int> actual   = solution->replaceNonCoprimes(nums);
  LCD_EXPECT_EQ(expect, actual);
}

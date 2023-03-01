// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Reordered Power of 2
//
// https://leetcode.com/problems/reordered-power-of-2/
//
// Question ID: 869
// Difficult  : Medium
// Solve Date : 2022/08/26 13:11

#include <cmath>
#include <iosfwd>
#include <set>
#include <unordered_set>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |869. Reordered Power of 2|:
//
// You are given an integer |n|. We reorder the digits in any order (including
// the original order) such that the leading digit is not zero. Return |true| if
// and only if we can do this so that the resulting number is a power of two.
//

LEETCODE_BEGIN_RESOLVING(869, ReorderedPowerOf2, Solution);

class Solution {
private:
  inline const static unordered_set<int> hashes{
      10,         100,        10000,     100000000,  1000010,    1100,
      1010000,    100000110,  1100100,   100110,     10111,      100010101,
      1001010001, 1100000110, 101011010, 111001100,  2201000,    10001121,
      1020210,    200110200,  111110011, 1010100211, 1000031011, 401001001,
      32000120,   223100,     212010011, 120011220,  102221100,  1111101111};

  int hashNumber(int n) {
    auto res = int(0);
    while (n != 0) {
      res += int(pow(10, n % 10));
      n /= 10;
    }
    return res;
  }

public:
  bool reorderedPowerOf2(int n) {
    return hashes.find(hashNumber(n)) != hashes.end();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 1
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(869, ReorderedPowerOf2, example_1) {
  auto solution = MakeSolution();
  int  n        = 1;
  bool expect   = true;
  bool actual   = solution->reorderedPowerOf2(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 10
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(869, ReorderedPowerOf2, example_2) {
  auto solution = MakeSolution();
  int  n        = 10;
  bool expect   = false;
  bool actual   = solution->reorderedPowerOf2(n);
  LCD_EXPECT_EQ(expect, actual);
}

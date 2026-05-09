// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Minimum Operations to Equalize Binary String
//
// https://leetcode.com/problems/minimum-operations-to-equalize-binary-string/
//
// Question ID: 3666
// Difficult  : Hard
// Solve Date : 2026/02/27 13:56

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3666. Minimum Operations to Equalize Binary String|:
//
// You are given a binary string |s|, and an integer |k|.
// In one operation, you must choose exactly |k| different indices and flip each
// |'0'| to |'1'| and each |'1'| to |'0'|. Return the minimum number of
// operations required to make all characters in the string equal to |'1'|. If
// it is not possible, return -1.
//
//

LEETCODE_BEGIN_RESOLVING(3666, MinimumOperationsToEqualizeBinaryString,
                         Solution);

class Solution {
public:
  int minOperations(string s, int k) {
    int zero = 0;
    int len  = s.length();

    for (int i = 0; i < len; i++)
      zero += ~s[i] & 1;

    if (!zero)
      return 0;

    if (len == k)
      return ((zero == len) << 1) - 1;

    int base = len - k;

    int odd = max((zero + k - 1) / k, (len - zero + base - 1) / base);

    odd += ~odd & 1;

    int even = max((zero + k - 1) / k, (zero + base - 1) / base);

    even += even & 1;

    int res = numeric_limits<int>::max();

    if ((k & 1) == (zero & 1))
      res = min(res, odd);

    if (~zero & 1)
      res = min(res, even);

    return res == numeric_limits<int>::max() ? -1 : res;
  }
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10^{​​​​​​​5}|
// * |s[i]| is either |'0'| or |'1'|.
// * |1 <= k <= s.length|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "110", k = 1
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(3666, MinimumOperationsToEqualizeBinaryString,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "110";
  int    k        = 1;
  int    expect   = 1;
  int    actual   = solution->minOperations(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "0101", k = 3
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3666, MinimumOperationsToEqualizeBinaryString,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "0101";
  int    k        = 3;
  int    expect   = 2;
  int    actual   = solution->minOperations(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "101", k = 2
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(3666, MinimumOperationsToEqualizeBinaryString,
                           example_3) {
  auto   solution = MakeSolution();
  string s        = "101";
  int    k        = 2;
  int    expect   = -1;
  int    actual   = solution->minOperations(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

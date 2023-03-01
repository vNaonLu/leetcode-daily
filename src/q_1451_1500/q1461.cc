// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Check If a String Contains All Binary Codes of Size K
//
// https://leetcode.com/problems/check-if-a-string-contains-all-binary-codes-of-size-k/
//
// Question ID: 1461
// Difficult  : Medium
// Solve Date : 2022/05/31 18:19

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1461. Check If a String Contains All Binary Codes of Size K|:
//
// Given a binary string |s| and an integer |k|, return |true| if every binary
// code of length |k| is a substring of |s|. Otherwise, return |false|.
//

LEETCODE_BEGIN_RESOLVING(1461, CheckIfAStringContainsAllBinaryCodesOfSizeK,
                         Solution);

class Solution {
public:
  bool hasAllCodes(string s, int k) {
    int          res = 1 << k;
    vector<bool> memo(res);
    int          mask = res - 1, hash = 0;

    for (int i = 0; i < s.size(); ++i) {
      hash = ((hash << 1) & mask) | (s[i] - '0');

      if (i >= k - 1 && !memo[hash]) {
        memo[hash] = true;
        if (--res == 0) {
          return true;
        }
      }
    }

    return false;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 5 * 10⁵|
// * |s[i]| is either |'0'| or |'1'|.
// * |1 <= k <= 20|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "00110110", k = 2
// Output: true
//
// The binary codes of length 2 are "00", "01", "10" and "11". They can be all
// found as substrings at indices 0, 1, 3 and 2 respectively.

LEETCODE_SOLUTION_UNITTEST(1461, CheckIfAStringContainsAllBinaryCodesOfSizeK,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "00110110";
  int    k        = 2;
  bool   expect   = true;
  bool   actual   = solution->hasAllCodes(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "0110", k = 1
// Output: true
//
// The binary codes of length 1 are "0" and "1", it is clear that both exist as
// a substring.

LEETCODE_SOLUTION_UNITTEST(1461, CheckIfAStringContainsAllBinaryCodesOfSizeK,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "0110";
  int    k        = 1;
  bool   expect   = true;
  bool   actual   = solution->hasAllCodes(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "0110", k = 2
// Output: false
//
// The binary code "00" is of length 2 and does not exist in the array.

LEETCODE_SOLUTION_UNITTEST(1461, CheckIfAStringContainsAllBinaryCodesOfSizeK,
                           example_3) {
  auto   solution = MakeSolution();
  string s        = "0110";
  int    k        = 2;
  bool   expect   = false;
  bool   actual   = solution->hasAllCodes(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

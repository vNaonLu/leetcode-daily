// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Maximize the Number of Partitions After Operations
//
// https://leetcode.com/problems/maximize-the-number-of-partitions-after-operations/
//
// Question ID: 3003
// Difficult  : Hard
// Solve Date : 2025/10/17 18:56

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3003. Maximize the Number of Partitions After Operations|:
//
// You are given a string |s| and an integer |k|.
// First, you are allowed to change at most one index in |s| to another
// lowercase English letter. After that, do the following partitioning operation
// until |s| is empty:
//
//  • Choose the longest prefix of |s| containing at most |k| distinct
//  characters.
//
//  • Delete the prefix from |s| and increase the number of partitions by one.
//  The remaining characters (if any) in |s| maintain their initial order.
// Return an integer denoting the maximum number of resulting partitions after
// the operations by optimally choosing at most one index to change.
//
//

LEETCODE_BEGIN_RESOLVING(3003, MaximizeTheNumberOfPartitionsAfterOperations,
                         Solution);

class Solution {
public:
  int maxPartitionsAfterOperations(string s, int k) {
    if (k == 26)
      return 1;

    int         n = s.length();
    vector<int> leftMask(n), leftDup(n), leftParts(n);

    int mask = 0, dup = 0, parts = 1;
    for (int i = 0; i < n; i++) {
      int bit = 1 << (s[i] - 'a');
      dup |= mask & bit;
      mask |= bit;
      if (__builtin_popcount(mask) > k) {
        mask = bit;
        dup  = 0;
        parts++;
      }
      leftMask[i]  = mask;
      leftDup[i]   = dup;
      leftParts[i] = parts;
    }

    int result = parts;
    mask = dup = parts = 0;

    for (int i = n - 1; i >= 0; i--) {
      int bit = 1 << (s[i] - 'a');
      dup |= mask & bit;
      mask |= bit;

      int bitCount = __builtin_popcount(mask);
      if (bitCount > k) {
        mask = bit;
        dup  = 0;
        parts++;
        bitCount = 1;
      }

      if (bitCount == k) {
        if ((bit & dup) && (bit & leftDup[i]) &&
            (__builtin_popcount(leftMask[i]) == k) &&
            ((leftMask[i] | mask) != 0x3FFFFFF)) {
          result = max(result, parts + leftParts[i] + 2);
        } else if (dup) {
          result = max(result, parts + leftParts[i] + 1);
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
// * |1 <= s.length <= 10⁴|
// * |s| consists only of lowercase English letters.
// * |1 <= k <= 26|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "accca", k = 2
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(3003, MaximizeTheNumberOfPartitionsAfterOperations,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "accca";
  int    k        = 2;
  int    expect   = 3;
  int    actual   = solution->maxPartitionsAfterOperations(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "aabaab", k = 3
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(3003, MaximizeTheNumberOfPartitionsAfterOperations,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "aabaab";
  int    k        = 3;
  int    expect   = 1;
  int    actual   = solution->maxPartitionsAfterOperations(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "xxyz", k = 1
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(3003, MaximizeTheNumberOfPartitionsAfterOperations,
                           example_3) {
  auto   solution = MakeSolution();
  string s        = "xxyz";
  int    k        = 1;
  int    expect   = 4;
  int    actual   = solution->maxPartitionsAfterOperations(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

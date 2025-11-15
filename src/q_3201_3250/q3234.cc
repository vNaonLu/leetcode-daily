// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Count the Number of Substrings With Dominant Ones
//
// https://leetcode.com/problems/count-the-number-of-substrings-with-dominant-ones/
//
// Question ID: 3234
// Difficult  : Medium
// Solve Date : 2025/11/15 16:11

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3234. Count the Number of Substrings With Dominant Ones|:
//
// You are given a binary string |s|.
// Return the number of substrings with dominant ones.
// A string has dominant ones if the number of ones in the string is greater
// than or equal to the square of the number of zeros in the string.
//
//

LEETCODE_BEGIN_RESOLVING(3234, CountTheNumberOfSubstringsWithDominantOnes,
                         Solution);

class Solution {
public:
  int numberOfSubstrings(string s) {
    int         n = s.size();
    vector<int> zero;
    for (int i = 0; i < n; i++) {
      if (s[i] == '0')
        zero.push_back(i);
    }
    int ones = n - zero.size();
    zero.push_back(n);

    int res = 0, sid = 0;

    for (int left = 0; left < n; left++) {

      for (int id = sid; id < zero.size() - 1; id++) {
        int cnt0 = id - sid + 1;
        if (cnt0 * cnt0 > ones)
          break;
        int p = zero[id], q = zero[id + 1];
        int cnt1 = zero[id] - left - (id - sid);
        if (cnt1 >= cnt0 * cnt0) {
          res += q - p;
        } else {
          res += max(q - p - (cnt0 * cnt0 - cnt1), 0);
        }
      }
      if (s[left] == '0') {
        sid++;
      } else {

        res += zero[sid] - left;
        ones--;
      }
    }
    return res;
  }
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 4 * 10⁴|
// * |s| consists only of characters |'0'| and |'1'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "00011"
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(3234, CountTheNumberOfSubstringsWithDominantOnes,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "00011";
  int    expect   = 5;
  int    actual   = solution->numberOfSubstrings(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "101101"
// Output: 16
//

LEETCODE_SOLUTION_UNITTEST(3234, CountTheNumberOfSubstringsWithDominantOnes,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "101101";
  int    expect   = 16;
  int    actual   = solution->numberOfSubstrings(s);
  LCD_EXPECT_EQ(expect, actual);
}

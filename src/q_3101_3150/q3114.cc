// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Latest Time You Can Obtain After Replacing Characters
//
// https://leetcode.com/problems/latest-time-you-can-obtain-after-replacing-characters/
//
// Question ID: 3114
// Difficult  : Easy
// Solve Date : 2024/04/15 21:28

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3114. Latest Time You Can Obtain After Replacing Characters|:
//
// You are given a string |s| representing a 12-hour format time where some of
// the digits (possibly none) are replaced with a |"?"|. 12-hour times are
// formatted as |"HH:MM"|, where |HH| is between |00| and |11|, and |MM| is
// between |00| and |59|. The earliest 12-hour time is |00:00|, and the latest
// is |11:59|. You have to replace all the |"?"| characters in |s| with digits
// such that the time we obtain by the resulting string is a valid 12-hour
// format time and is the latest possible. Return the resulting string.
//
//

LEETCODE_BEGIN_RESOLVING(3114, LatestTimeYouCanObtainAfterReplacingCharacters,
                         Solution);

class Solution {
public:
  string findLatestTime(string s) {
    if (s[4] == '?') {
      s[4] = '9';
    }

    if (s[3] == '?') {
      s[3] = '5';
    }

    if (s[1] == '?' && s[0] == '?') {
      s[0] = '1';
      s[1] = '1';
    } else if (s[1] == '?') {
      s[1] = s[0] == '0' ? '9' : '1';
    } else if (s[0] == '?') {
      s[0] = (s[1] == '1' || s[1] == '0') ? '1' : '0';
    }
    return s;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |s.length == 5|
// * |s[2]| is equal to the character |":"|.
// * All characters except |s[2]| are digits or |"?"| characters.
// * The input is generated such that there is at least one time between
// |"00:00"| and |"11:59"| that you can obtain after replacing the |"?"|
// characters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "1?:?4"
// Output: "11:54"
//

LEETCODE_SOLUTION_UNITTEST(3114, LatestTimeYouCanObtainAfterReplacingCharacters,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "1?:?4";
  string expect   = "11:54";
  string actual   = solution->findLatestTime(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "0?:5?"
// Output: "09:59"
//

LEETCODE_SOLUTION_UNITTEST(3114, LatestTimeYouCanObtainAfterReplacingCharacters,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "0?:5?";
  string expect   = "09:59";
  string actual   = solution->findLatestTime(s);
  LCD_EXPECT_EQ(expect, actual);
}

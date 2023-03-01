// Copyright 2023 Naon Lu
//
// This file describes the solution of
// License Key Formatting
//
// https://leetcode.com/problems/license-key-formatting/
//
// Question ID: 482
// Difficult  : Easy
// Solve Date : 2022/07/22 23:34

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |482. License Key Formatting|:
//
// You are given a license key represented as a string |s| that consists of only
// alphanumeric characters and dashes. The string is separated into |n + 1|
// groups by |n| dashes. You are also given an integer |k|. We want to reformat
// the string |s| such that each group contains exactly |k| characters, except
// for the first group, which could be shorter than |k| but still must contain
// at least one character. Furthermore, there must be a dash inserted between
// two groups, and you should convert all lowercase letters to uppercase. Return
// the reformatted license key.
//

LEETCODE_BEGIN_RESOLVING(482, LicenseKeyFormatting, Solution);

class Solution {
public:
  string licenseKeyFormatting(string s, int k) {
    string res;

    ++k;
    for (auto it = s.rbegin(); it != s.rend(); ++it) {
      if (*it != '-') {
        if ((res.size() + 1) % k == 0) {
          res.push_back('-');
        }

        res.push_back(toupper(*it));
      }
    }
    reverse(res.begin(), res.end());

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁵|
// * |s| consists of English letters, digits, and dashes |'-'|.
// * |1 <= k <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "5F3Z-2e-9-w", k = 4
// Output: "5F3Z-2E9W"
//
// The string s has been split into two parts, each part has 4 characters.
// Note that the two extra dashes are not needed and can be removed.

LEETCODE_SOLUTION_UNITTEST(482, LicenseKeyFormatting, example_1) {
  auto   solution = MakeSolution();
  string s        = "5F3Z-2e-9-w";
  int    k        = 4;
  string expect   = "5F3Z-2E9W";
  string actual   = solution->licenseKeyFormatting(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "2-5g-3-J", k = 2
// Output: "2-5G-3J"
//
// The string s has been split into three parts, each part has 2 characters
// except the first part as it could be shorter as mentioned above.

LEETCODE_SOLUTION_UNITTEST(482, LicenseKeyFormatting, example_2) {
  auto   solution = MakeSolution();
  string s        = "2-5g-3-J";
  int    k        = 2;
  string expect   = "2-5G-3J";
  string actual   = solution->licenseKeyFormatting(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

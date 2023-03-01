// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Compare Version Numbers
//
// https://leetcode.com/problems/compare-version-numbers/
//
// Question ID: 165
// Difficult  : Medium
// Solve Date : 2022/02/25 16:04

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |165. Compare Version Numbers|:
//
// Given two version numbers,  |version1| and |version2|, compare them.
// Version numbers consist of one or more revisions joined by a dot  |'.'|. Each
// revision consists of digits and may contain leading zeros. Every revision
// contains at least one character. Revisions are 0-indexed from left to right,
// with the leftmost revision being revision 0, the next revision being revision
// 1, and so on. For example  |2.5.33| and  |0.1| are valid version numbers. To
// compare version numbers, compare their revisions in left-to-right order.
// Revisions are compared using their integer value ignoring any leading zeros.
// This means that revisions  |1| and  |001| are considered equal. If a version
// number does not specify a revision at an index, then treat the revision as 
// |0|. For example, version  |1.0| is less than version  |1.1| because their
// revision 0s are the same, but their revision 1s are  |0| and 
// |1| respectively, and  |0 < 1|. Return the following:
//
//  • If |version1 < version2|, return |-1|.
//
//  • If |version1 > version2|, return |1|.
//
//  • Otherwise, return |0|.
//  
//

LEETCODE_BEGIN_RESOLVING(165, CompareVersionNumbers, Solution);

class Solution {
public:
  int compareVersion(string version1, string version2) {
    int  v1 = 0, v2 = 0;
    auto i1 = version1.begin();
    auto i2 = version2.begin();
    while (i1 != version1.end() || i2 != version2.end()) {
      if (i1 != version1.end() && *i1 != '.') {
        v1 = v1 * 10 + (*i1 - '0');
        ++i1;
      }
      if (i2 != version2.end() && *i2 != '.') {
        v2 = v2 * 10 + (*i2 - '0');
        ++i2;
      }

      if ((i1 == version1.end() || *i1 == '.') &&
          (i2 == version2.end() || *i2 == '.')) {
        if (v1 > v2)
          return 1;
        else if (v1 < v2)
          return -1;
        if (i1 != version1.end()) {
          ++i1;
        }
        if (i2 != version2.end()) {
          ++i2;
        }
        v1 = 0;
        v2 = 0;
      }
    }

    return 0;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= version1.length, version2.length <= 500|
// * |version1| and |version2| only contain digits and |'.'|.
// * |version1| and |version2| are valid version numbers.
// * All the given revisions in  |version1| and |version2| can be stored
// in a 32-bit integer.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: version1 = "1.01", version2 = "1.001"
// Output: 0
//
// Ignoring leading zeroes, both "01" and "001" represent the same integer "1".

LEETCODE_SOLUTION_UNITTEST(165, CompareVersionNumbers, example_1) {
  auto   solution = MakeSolution();
  string version1 = "1.01";
  string version2 = "1.001";
  int    expect   = 0;
  int    actual   = solution->compareVersion(version1, version2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: version1 = "1.0", version2 = "1.0.0"
// Output: 0
//
// version1 does not specify revision 2, which means it is treated as "0".

LEETCODE_SOLUTION_UNITTEST(165, CompareVersionNumbers, example_2) {
  auto   solution = MakeSolution();
  string version1 = "1.0";
  string version2 = "1.0.0";
  int    expect   = 0;
  int    actual   = solution->compareVersion(version1, version2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: version1 = "0.1", version2 = "1.1"
// Output: -1
//
// version1's revision 0 is "0", while version2's revision 0 is "1". 0 < 1, so
// version1 < version2.

LEETCODE_SOLUTION_UNITTEST(165, CompareVersionNumbers, example_3) {
  auto   solution = MakeSolution();
  string version1 = "0.1";
  string version2 = "1.1";
  int    expect   = -1;
  int    actual   = solution->compareVersion(version1, version2);
  LCD_EXPECT_EQ(expect, actual);
}

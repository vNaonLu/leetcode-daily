// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Excel Sheet Column Number
//
// https://leetcode.com/problems/excel-sheet-column-number/
//
// Question ID: 171
// Difficult  : Easy
// Solve Date : 2022/02/22 18:01

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |171. Excel Sheet Column Number|:
//
// Given a string |columnTitle| that represents the column title as appears in
// an Excel sheet, return its corresponding column number. For example: A -> 1
// B -> 2
// C -> 3
// ...
// Z -> 26
// AA -> 27
// AB -> 28
// ...
//  
//

LEETCODE_BEGIN_RESOLVING(171, ExcelSheetColumnNumber, Solution);

class Solution {
public:
  int titleToNumber(string columnTitle) {
    int res = 0;
    for (const auto &c : columnTitle) {
      res = res * 26 + (c - 'A' + 1);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= columnTitle.length <= 7|
// * |columnTitle| consists only of uppercase English letters.
// * |columnTitle| is in the range |["A", "FXSHRXW"]|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: columnTitle = "A"
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(171, ExcelSheetColumnNumber, example_1) {
  auto   solution    = MakeSolution();
  string columnTitle = "A";
  int    expect      = 1;
  int    actual      = solution->titleToNumber(columnTitle);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: columnTitle = "AB"
// Output: 28
//

LEETCODE_SOLUTION_UNITTEST(171, ExcelSheetColumnNumber, example_2) {
  auto   solution    = MakeSolution();
  string columnTitle = "AB";
  int    expect      = 28;
  int    actual      = solution->titleToNumber(columnTitle);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: columnTitle = "ZY"
// Output: 701
//

LEETCODE_SOLUTION_UNITTEST(171, ExcelSheetColumnNumber, example_3) {
  auto   solution    = MakeSolution();
  string columnTitle = "ZY";
  int    expect      = 701;
  int    actual      = solution->titleToNumber(columnTitle);
  LCD_EXPECT_EQ(expect, actual);
}

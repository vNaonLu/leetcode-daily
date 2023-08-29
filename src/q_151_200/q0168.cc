// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Excel Sheet Column Title
//
// https://leetcode.com/problems/excel-sheet-column-title/
//
// Question ID: 168
// Difficult  : Easy
// Solve Date : 2023/08/22 17:51

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |168. Excel Sheet Column Title|:
//
// Given an integer |columnNumber|, return its corresponding column title as it
// appears in an Excel sheet. For example: A -> 1 B -> 2 C -> 3
// ...
// Z -> 26
// AA -> 27
// AB -> 28
// ...
//
//

LEETCODE_BEGIN_RESOLVING(168, ExcelSheetColumnTitle, Solution);

class Solution {
public:
  string convertToTitle(int columnNumber) {
    string res;
    while (columnNumber > 0) {
      columnNumber = columnNumber - 1;
      res.push_back('A' + columnNumber % 26);
      columnNumber /= 26;
    }
    reverse(res.begin(), res.end());
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= columnNumber <= 2³¹ - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: columnNumber = 1
// Output: "A"
//

LEETCODE_SOLUTION_UNITTEST(168, ExcelSheetColumnTitle, example_1) {
  auto   solution     = MakeSolution();
  int    columnNumber = 1;
  string expect       = "A";
  string actual       = solution->convertToTitle(columnNumber);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: columnNumber = 28
// Output: "AB"
//

LEETCODE_SOLUTION_UNITTEST(168, ExcelSheetColumnTitle, example_2) {
  auto   solution     = MakeSolution();
  int    columnNumber = 28;
  string expect       = "AB";
  string actual       = solution->convertToTitle(columnNumber);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: columnNumber = 701
// Output: "ZY"
//

LEETCODE_SOLUTION_UNITTEST(168, ExcelSheetColumnTitle, example_3) {
  auto   solution     = MakeSolution();
  int    columnNumber = 701;
  string expect       = "ZY";
  string actual       = solution->convertToTitle(columnNumber);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: 52
// Output: "AZ"
//

LEETCODE_SOLUTION_UNITTEST(168, ExcelSheetColumnTitle, extra_testcase_1) {
  auto   solution     = MakeSolution();
  int    columnNumber = 52;
  string expect       = "AZ";
  string actual       = solution->convertToTitle(columnNumber);
  LCD_EXPECT_EQ(expect, actual);
}

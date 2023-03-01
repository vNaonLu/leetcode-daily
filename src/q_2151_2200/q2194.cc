// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Cells in a Range on an Excel Sheet
//
// https://leetcode.com/problems/cells-in-a-range-on-an-excel-sheet/
//
// Question ID: 2194
// Difficult  : Easy
// Solve Date : 2023/02/21 18:45

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2194. Cells in a Range on an Excel Sheet|:
//
// A cell |(r, c)| of an excel sheet is represented as a string |"<col><row>"|
// where:
//
//  • |<col>| denotes the column number |c| of the cell. It is represented by
//  alphabetical letters.
//
//
//    • For example, the |1ˢᵗ| column is denoted by |'A'|, the |2ⁿᵈ| by |'B'|,
//    the |3ʳᵈ| by |'C'|, and so on.
//
//
//
//  • |<row>| is the row number |r| of the cell. The |rᵗʰ| row is represented by
//  the integer |r|.
// You are given a string |s|inthe format |"<col1><row1>:<col2><row2>"|, where
// |<col1>| represents the column |c1|, |<row1>| represents the row |r1|,
// |<col2>| represents the column |c2|, and |<row2>| represents the row |r2|,
// such that |r1 <= r2| and |c1 <= c2|. Return the list of cells |(x, y)| such
// that |r1 <= x <= r2| and |c1 <= y <= c2|. The cells should be represented
// asstrings in the format mentioned above and be sorted in non-decreasing order
// first by columns and then by rows.
//

LEETCODE_BEGIN_RESOLVING(2194, CellsInARangeOnAnExcelSheet, Solution);

class Solution {
public:
  vector<string> cellsInRange(string s) {
    vector<string> res;
    auto           beg     = s[0];
    auto           end     = s[3] + 1;
    auto           num_beg = s[1];
    auto           num_end = s[4] + 1;
    string         tmp(2, 0);
    for (tmp[0] = beg; tmp[0] < end; ++tmp[0]) {
      for (tmp[1] = num_beg; tmp[1] < num_end; ++tmp[1]) {
        res.emplace_back(tmp);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |s.length == 5|
// * |'A' <= s[0] <= s[3] <= 'Z'|
// * |'1' <= s[1] <= s[4] <= '9'|
// * |s| consists of uppercase English letters, digits and |':'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "K1:L2"
// Output: ["K1","K2","L1","L2"]
//
// The above diagram shows the cells which should be present in the list.
// The red arrows denote the order in which the cells should be presented.

LEETCODE_SOLUTION_UNITTEST(2194, CellsInARangeOnAnExcelSheet, example_1) {
  auto           solution = MakeSolution();
  string         s        = "K1:L2";
  vector<string> expect   = {"K1", "K2", "L1", "L2"};
  vector<string> actual   = solution->cellsInRange(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "A1:F1"
// Output: ["A1","B1","C1","D1","E1","F1"]
//
// The above diagram shows the cells which should be present in the list.
// The red arrow denotes the order in which the cells should be presented.

LEETCODE_SOLUTION_UNITTEST(2194, CellsInARangeOnAnExcelSheet, example_2) {
  auto           solution = MakeSolution();
  string         s        = "A1:F1";
  vector<string> expect   = {"A1", "B1", "C1", "D1", "E1", "F1"};
  vector<string> actual   = solution->cellsInRange(s);
  LCD_EXPECT_EQ(expect, actual);
}

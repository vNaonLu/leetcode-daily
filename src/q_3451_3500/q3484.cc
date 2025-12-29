// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Design Spreadsheet
//
// https://leetcode.com/problems/design-spreadsheet/
//
// Question ID: 3484
// Difficult  : Medium
// Solve Date : 2025/09/19 19:58

#include <cctype>
#include <iosfwd>
#include <string>
#include <string_view>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3484. Design Spreadsheet|:
//
//

LEETCODE_BEGIN_RESOLVING(3484, DesignSpreadsheet, Spreadsheet);

class Spreadsheet {
public:
  Spreadsheet(int rows) { (void)rows; }

  void setCell(string cell, int value) { cells_[cell] = value; }

  void resetCell(string cell) { cells_.erase(cell); }

  int getValue(string formula) {
    string_view sv = formula;
    sv             = sv.substr(1);
    if (auto eq = sv.find("+"); eq != string_view::npos) {
      auto cell1 = sv.substr(0, eq);
      auto cell2 = sv.substr(eq + 1);

      auto value1 = 0;
      auto value2 = 0;

      if (!isdigit(cell1[0])) {
        value1 = cells_[string(cell1)];
      } else {
        value1 = stoi(string(cell1));
      }

      if (!isdigit(cell2[0])) {
        value2 = cells_[string(cell2)];
      } else {
        value2 = stoi(string(cell2));
      }

      return value1 + value2;
    }

    return 0;
  }

private:
  unordered_map<string, int> cells_;
};

LEETCODE_END_RESOLVING(Spreadsheet);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= rows <= 10³|
// * |0 <= value <= 10⁵|
// * The formula is always in the format |"=X+Y"|, where |X| and |Y| are either
// valid cell references or non-negative integers with values less than or equal
// to |10⁵|.
// * Each cell reference consists of a capital letter from |'A'| to |'Z'|
// followed by a row number between |1| and |rows|.
// * At most |10⁴| calls will be made in total to |setCell|, |resetCell|, and
// |getValue|.
///////////////////////////////////////////////////////////////////////////////

LEETCODE_SOLUTION_UNITTEST(3484, DesignSpreadsheet, example_1) {
  int  rows         = 3;
  auto spread_sheet = MakeSpreadsheet(rows);
  LCD_EXPECT_EQ(12, spread_sheet->getValue("=5+7"));
  spread_sheet->setCell("A1", 10);
  LCD_EXPECT_EQ(16, spread_sheet->getValue("=A1+6"));
  spread_sheet->setCell("B2", 15);
  LCD_EXPECT_EQ(25, spread_sheet->getValue("=A1+B2"));
  spread_sheet->resetCell("A1");
  LCD_EXPECT_EQ(15, spread_sheet->getValue("=A1+B2"));
}

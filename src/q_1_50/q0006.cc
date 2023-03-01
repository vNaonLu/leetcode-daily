// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Zigzag Conversion
//
// https://leetcode.com/problems/zigzag-conversion/
//
// Question ID: 6
// Difficult  : Medium
// Solve Date : 2021/10/10 13:46

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |6. Zigzag Conversion|:
//
// The string |"PAYPALISHIRING"| is written in a zigzag pattern on a given
// number of rows like this: (you may want to display this pattern in a fixed
// font for better legibility) P   A   H   N A P L S I I G Y   I   R And then
// read line by line: |"PAHNAPLSIIGYIR"| Write the code that will take a string
// and make this conversion given a number of rows: string convert(string s, int
// numRows);  
//

LEETCODE_BEGIN_RESOLVING(6, ZigzagConversion, Solution);

class Solution {
public:
  string convert(string s, int numRows) {
    if (numRows == 1)
      return s;
    string res;
    int    cycle = 2 * numRows - 2;
    for (int i = 0; i < numRows; ++i) {
      for (int j = 0; j + i < s.size(); j += cycle) {
        res.push_back(s[j + i]);
        if (i != 0 && i != numRows - 1 && j + cycle - i < s.size())
          res.push_back(s[j + cycle - i]);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 1000|
// * |s| consists of English letters (lower-case and upper-case), |','| and
// |'.'|.
// * |1 <= numRows <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "PAYPALISHIRING", numRows = 3
// Output: "PAHNAPLSIIGYIR"
//

LEETCODE_SOLUTION_UNITTEST(6, ZigzagConversion, example_1) {
  auto   solution = MakeSolution();
  string s        = "PAYPALISHIRING";
  int    numRows  = 3;
  string expect   = "PAHNAPLSIIGYIR";
  string actual   = solution->convert(s, numRows);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "PAYPALISHIRING", numRows = 4
// Output: "PINALSIGYAHRPI"
//
// P I N
// A L S I G
// Y A H R
// P I

LEETCODE_SOLUTION_UNITTEST(6, ZigzagConversion, example_2) {
  auto   solution = MakeSolution();
  string s        = "PAYPALISHIRING";
  int    numRows  = 4;
  string expect   = "PINALSIGYAHRPI";
  string actual   = solution->convert(s, numRows);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "A", numRows = 1
// Output: "A"
//

LEETCODE_SOLUTION_UNITTEST(6, ZigzagConversion, example_3) {
  auto   solution = MakeSolution();
  string s        = "A";
  int    numRows  = 1;
  string expect   = "A";
  string actual   = solution->convert(s, numRows);
  LCD_EXPECT_EQ(expect, actual);
}

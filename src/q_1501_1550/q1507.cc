// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Reformat Date
//
// https://leetcode.com/problems/reformat-date/
//
// Question ID: 1507
// Difficult  : Easy
// Solve Date : 2022/03/03 18:13

#include <iosfwd>
#include <map>
#include <string>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1507. Reformat Date|:
//
// Given a |date| string in the form  |Day Month Year|, where:
//
//  • |Day| is in the set |{"1st", "2nd", "3rd", "4th", ..., "30th", "31st"}|.
//
//  • |Month| is in the set |{"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul",
//  "Aug", "Sep", "Oct", "Nov", "Dec"}|.
//
//  • |Year| is in the range |[1900, 2100]|.
// Convert the date string to the format |YYYY-MM-DD|, where:
//
//  • |YYYY| denotes the 4 digit year.
//
//  • |MM| denotes the 2 digit month.
//
//  • |DD| denotes the 2 digit day.
//  
//

LEETCODE_BEGIN_RESOLVING(1507, ReformatDate, Solution);

class Solution {
private:
  unordered_map<string, int> months = {
      {"Jan",  1},
      {"Feb",  2},
      {"Mar",  3},
      {"Apr",  4},
      {"May",  5},
      {"Jun",  6},
      {"Jul",  7},
      {"Aug",  8},
      {"Sep",  9},
      {"Oct", 10},
      {"Nov", 11},
      {"Dec", 12}
  };
  std::vector<std::string_view> suffixes = {"st", "nd", "rd", "th"};

public:
  string reformatDate(string date) {
    size_t suffix_pos = std::string::npos;

    for (const auto &suffix : suffixes) {
      suffix_pos = date.find(suffix);
      if (suffix_pos != std::string::npos)
        break;
    }

    auto day   = std::stoi(date.substr(0, suffix_pos));
    auto month = months[date.substr(suffix_pos + 3, 3)];
    auto year  = date.substr(suffix_pos + 7, 4);

    char res[20];
    snprintf(res, 20, "%s-%02d-%02d", year.c_str(), month, day);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The given dates are guaranteed to be valid, so no error handling is
// necessary.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: date = "20th Oct 2052"
// Output: "2052-10-20"
//

LEETCODE_SOLUTION_UNITTEST(1507, ReformatDate, example_1) {
  auto   solution = MakeSolution();
  string date     = "20th Oct 2052";
  string expect   = "2052-10-20";
  string actual   = solution->reformatDate(date);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: date = "6th Jun 1933"
// Output: "1933-06-06"
//

LEETCODE_SOLUTION_UNITTEST(1507, ReformatDate, example_2) {
  auto   solution = MakeSolution();
  string date     = "6th Jun 1933";
  string expect   = "1933-06-06";
  string actual   = solution->reformatDate(date);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: date = "26th May 1960"
// Output: "1960-05-26"
//

LEETCODE_SOLUTION_UNITTEST(1507, ReformatDate, example_3) {
  auto   solution = MakeSolution();
  string date     = "26th May 1960";
  string expect   = "1960-05-26";
  string actual   = solution->reformatDate(date);
  LCD_EXPECT_EQ(expect, actual);
}

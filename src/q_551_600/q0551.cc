// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Student Attendance Record I
//
// https://leetcode.com/problems/student-attendance-record-i/
//
// Question ID: 551
// Difficult  : Easy
// Solve Date : 2023/06/19 19:39

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |551. Student Attendance Record I|:
//
// You are given a string |s| representing an attendance record for a student
// where each character signifies whether the student was absent, late, or
// present on that day. The record only contains the following three characters:
//
//  • |'A'|: Absent.
//
//  • |'L'|: Late.
//
//  • |'P'|: Present.
// The student is eligible for an attendance award if they meet both of the
// following criteria:
//
//  • The student was absent ( |'A'|) for strictly fewer than 2 days total.
//
//  • The student was never late ( |'L'|) for 3 or more consecutive days.
// Return |true| if the student is eligible for an attendance award, or |false|
// otherwise.
//
//

LEETCODE_BEGIN_RESOLVING(551, StudentAttendanceRecordI, Solution);

class Solution {
public:
  bool checkRecord(string s) {
    int absent_cnt       = 0;
    int consecutive_late = 0;
    for (auto c : s) {
      switch (c) {
      case 'A': {
        consecutive_late = 0;
        ++absent_cnt;
      } break;
      case 'L': {
        ++consecutive_late;
      } break;
      default: {
        consecutive_late = 0;
      } break;
      }
      if (absent_cnt >= 2 || consecutive_late >= 3) {
        return false;
      }
    }
    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 1000|
// * |s[i]| is either |'A'|, |'L'|, or |'P'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "PPALLP"
// Output: true
//
// The student has fewer than 2 absences and was never late 3 or more
// consecutive days.

LEETCODE_SOLUTION_UNITTEST(551, StudentAttendanceRecordI, example_1) {
  auto   solution = MakeSolution();
  string s        = "PPALLP";
  bool   expect   = true;
  bool   actual   = solution->checkRecord(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "PPALLL"
// Output: false
//
// The student was late 3 consecutive days in the last 3 days, so is not
// eligible for the award.

LEETCODE_SOLUTION_UNITTEST(551, StudentAttendanceRecordI, example_2) {
  auto   solution = MakeSolution();
  string s        = "PPALLL";
  bool   expect   = false;
  bool   actual   = solution->checkRecord(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: "AA"
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(551, StudentAttendanceRecordI, extra_testcase_1) {
  auto   solution = MakeSolution();
  string s        = "AA";
  bool   expect   = false;
  bool   actual   = solution->checkRecord(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #2]
//  Input: "LALL"
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(551, StudentAttendanceRecordI, extra_testcase_2) {
  auto   solution = MakeSolution();
  string s        = "LALL";
  bool   expect   = true;
  bool   actual   = solution->checkRecord(s);
  LCD_EXPECT_EQ(expect, actual);
}

// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Student Attendance Record II
//
// https://leetcode.com/problems/student-attendance-record-ii/
//
// Question ID: 552
// Difficult  : Hard
// Solve Date : 2024/05/26 14:11

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |552. Student Attendance Record II|:
//
// An attendance record for a student can be represented as a string where each
// character signifies whether the student was absent, late, or present on that
// day. The record only contains the following three characters:
//
//  • |'A'|: Absent.
//
//  • |'L'|: Late.
//
//  • |'P'|: Present.
// Any student is eligible for an attendance award if they meet both of the
// following criteria:
//
//  • The student was absent ( |'A'|) for strictly fewer than 2 days total.
//
//  • The student was never late ( |'L'|) for 3 or more consecutive days.
// Given an integer |n|, return the number of possible attendance records of
// length |n| that make a student eligible for an attendance award. The answer
// may be very large, so return it modulo |10⁹ + 7|.
//
//

LEETCODE_BEGIN_RESOLVING(552, StudentAttendanceRecordII, Solution);

class Solution {
public:
  int checkRecord(int n) {
    vector<vector<vector<int>>> dp(2,
                                   vector<vector<int>>(2, vector<int>(3, 0)));

    for (int j = 0; j < 2; ++j) {
      for (int k = 0; k < 3; ++k) {
        dp[0][j][k] = 1;
      }
    }

    for (int i = 1; i <= n; ++i) {
      for (int j = 0; j < 2; ++j) {
        for (int k = 0; k < 3; ++k) {
          int64_t ret = dp[(i - 1) & 1][j][0];
          ret += (k < 2 ? dp[(i - 1) & 1][j][k + 1] : 0);
          ret += (j == 0 ? dp[(i - 1) & 1][j + 1][0] : 0);
          dp[i & 1][j][k] = ret % kMod;
        }
      }
    }
    return dp[n & 1][0][0];
  }

private:
  static constexpr int64_t kMod = 1e9 + 7;
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 2
// Output: 8
//

LEETCODE_SOLUTION_UNITTEST(552, StudentAttendanceRecordII, example_1) {
  auto solution = MakeSolution();
  int  n        = 2;
  int  expect   = 8;
  int  actual   = solution->checkRecord(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 1
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(552, StudentAttendanceRecordII, example_2) {
  auto solution = MakeSolution();
  int  n        = 1;
  int  expect   = 3;
  int  actual   = solution->checkRecord(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 10101
// Output: 183236316
//

LEETCODE_SOLUTION_UNITTEST(552, StudentAttendanceRecordII, example_3) {
  auto solution = MakeSolution();
  int  n        = 10101;
  int  expect   = 183236316;
  int  actual   = solution->checkRecord(n);
  LCD_EXPECT_EQ(expect, actual);
}

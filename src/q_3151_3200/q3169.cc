// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Count Days Without Meetings
//
// https://leetcode.com/problems/count-days-without-meetings/
//
// Question ID: 3169
// Difficult  : Medium
// Solve Date : 2025/03/24 21:55

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3169. Count Days Without Meetings|:
//
//

LEETCODE_BEGIN_RESOLVING(3169, CountDaysWithoutMeetings, Solution);

class Solution {
public:
  int countDays(int days, vector<vector<int>> &meetings) {
    sort(meetings.begin(), meetings.end());
    int res = 0;
    int beg = -1;
    int end = -1;
    for (auto x : meetings) {
      int b = x[0];
      int e = x[1];
      if (b > end) {
        if (end != -1) {
          res += end - beg + 1;
        }
        beg = b;
        end = e;
      } else {
        end = max(end, e);
      }
    }

    if (-1 != end) {
      res += end - beg + 1;
    }
    return days - res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= days <= 10⁹|
// * |1 <= meetings.length <= 10⁵|
// * |meetings[i].length == 2|
// * |1 <= meetings[i][0] <= meetings[i][1] <= days|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: days = 10, meetings = [[5,7],[1,3],[9,10]]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3169, CountDaysWithoutMeetings, example_1) {
  auto                solution = MakeSolution();
  int                 days     = 10;
  vector<vector<int>> meetings = {
      {5,  7},
      {1,  3},
      {9, 10}
  };
  int expect = 2;
  int actual = solution->countDays(days, meetings);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: days = 5, meetings = [[2,4],[1,3]]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(3169, CountDaysWithoutMeetings, example_2) {
  auto                solution = MakeSolution();
  int                 days     = 5;
  vector<vector<int>> meetings = {
      {2, 4},
      {1, 3}
  };
  int expect = 1;
  int actual = solution->countDays(days, meetings);
  LCD_EXPECT_EQ(expect, actual);
}

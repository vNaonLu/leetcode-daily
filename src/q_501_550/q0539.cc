// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Time Difference
//
// https://leetcode.com/problems/minimum-time-difference/
//
// Question ID: 539
// Difficult  : Medium
// Solve Date : 2022/02/20 14:33

#include <algorithm>
#include <iosfwd>
#include <limits>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |539. Minimum Time Difference|:
//
// Given a list of 24-hour clock time points in "HH:MM" format, return the
// minimum minutes difference between any two time-points in the list.  
//

LEETCODE_BEGIN_RESOLVING(539, MinimumTimeDifference, Solution);

class Solution {
public:
  int findMinDifference(vector<string> &timePoints) {
    vector<int> minutes;
    for (const auto &s : timePoints) {
      int h, m;
      sscanf(s.c_str(), "%d:%d", &h, &m);
      minutes.emplace_back(h * 60 + m);
      minutes.emplace_back((h + 24) * 60 + m); // adds next day
    }
    sort(minutes.begin(), minutes.end());
    int res = numeric_limits<int>::max();
    for (int i = 1; i < minutes.size(); ++i) {
      res = min(res, minutes[i] - minutes[i - 1]);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= timePoints.length <= 2 * 10⁴|
// * |timePoints[i]| is in the format "HH:MM".
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: timePoints = ["23:59","00:00"]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(539, MinimumTimeDifference, example_1) {
  auto           solution   = MakeSolution();
  vector<string> timePoints = {"23:59", "00:00"};
  int            expect     = 1;
  int            actual     = solution->findMinDifference(timePoints);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: timePoints = ["00:00","23:59","00:00"]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(539, MinimumTimeDifference, example_2) {
  auto           solution   = MakeSolution();
  vector<string> timePoints = {"00:00", "23:59", "00:00"};
  int            expect     = 0;
  int            actual     = solution->findMinDifference(timePoints);
  LCD_EXPECT_EQ(expect, actual);
}

// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Determine if Two Events Have Conflict
//
// https://leetcode.com/problems/determine-if-two-events-have-conflict/
//
// Question ID: 2446
// Difficult  : Easy
// Solve Date : 2023/03/09 21:06

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2446. Determine if Two Events Have Conflict|:
//
// You are given two arrays of strings that represent two inclusive events that
// happened on the same day, |event1| and |event2|, where:
//
//  • |event1 = [startTime₁, endTime₁]| and
//
//  • |event2 = [startTime₂, endTime₂]|.
// Event times are valid 24 hours format in the form of |HH:MM|.
// A conflict happens when two events have some non-empty intersection (i.e.,
// some moment is common to both events). Return |true| if there is a conflict
// between two events. Otherwise, return |false|.
//

LEETCODE_BEGIN_RESOLVING(2446, DetermineIfTwoEventsHaveConflict, Solution);

class Solution {
private:
  int toMinutes(const string &time) {
    static constexpr int kHourToMinutes = 60;
    return stoi(time.substr(0, 2)) * kHourToMinutes + stoi(time.substr(3, 2));
  }

public:
  bool haveConflict(vector<string> &event1, vector<string> &event2) {
    auto begin1  = toMinutes(event1[0]);
    auto elapse1 = toMinutes(event1[1]) - begin1;
    auto begin2  = toMinutes(event2[0]);
    auto elapse2 = toMinutes(event2[1]) - begin2;
    return (begin2 >= begin1 && begin2 <= begin1 + elapse1) ||
           (begin1 >= begin2 && begin1 <= begin2 + elapse2);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |evnet1.length == event2.length == 2.|
// * |event1[i].length == event2[i].length == 5|
// * |startTime₁ <= endTime₁|
// * |startTime₂ <= endTime₂|
// * All the event times follow the |HH:MM| format.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: event1 = ["01:15","02:00"], event2 = ["02:00","03:00"]
// Output: true
//
// The two events intersect at time 2:00.

LEETCODE_SOLUTION_UNITTEST(2446, DetermineIfTwoEventsHaveConflict, example_1) {
  auto           solution = MakeSolution();
  vector<string> event1   = {"01:15", "02:00"};
  vector<string> event2   = {"02:00", "03:00"};
  bool           expect   = true;
  bool           actual   = solution->haveConflict(event1, event2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: event1 = ["01:00","02:00"], event2 = ["01:20","03:00"]
// Output: true
//
// The two events intersect starting from 01:20 to 02:00.

LEETCODE_SOLUTION_UNITTEST(2446, DetermineIfTwoEventsHaveConflict, example_2) {
  auto           solution = MakeSolution();
  vector<string> event1   = {"01:00", "02:00"};
  vector<string> event2   = {"01:20", "03:00"};
  bool           expect   = true;
  bool           actual   = solution->haveConflict(event1, event2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: event1 = ["10:00","11:00"], event2 = ["14:00","15:00"]
// Output: false
//
// The two events do not intersect.

LEETCODE_SOLUTION_UNITTEST(2446, DetermineIfTwoEventsHaveConflict, example_3) {
  auto           solution = MakeSolution();
  vector<string> event1   = {"10:00", "11:00"};
  vector<string> event2   = {"14:00", "15:00"};
  bool           expect   = false;
  bool           actual   = solution->haveConflict(event1, event2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: event1 = ["15:19","17:56"], event2 = ["14:11","20:02"]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(2446, DetermineIfTwoEventsHaveConflict,
                           extra_testcase_1) {
  auto           solution = MakeSolution();
  vector<string> event1   = {"15:19", "17:56"};
  vector<string> event2   = {"14:11", "20:02"};
  bool           expect   = true;
  bool           actual   = solution->haveConflict(event1, event2);
  LCD_EXPECT_EQ(expect, actual);
}

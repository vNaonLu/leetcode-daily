// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Button with Longest Push Time
//
// https://leetcode.com/problems/button-with-longest-push-time/
//
// Question ID: 3386
// Difficult  : Easy
// Solve Date : 2024/12/26 15:19

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3386. Button with Longest Push Time|:
//
// You are given a 2D array |events| which represents a sequence of events where
// a child pushes a series of buttons on a keyboard. Each |events[i] = [indexᵢ,
// timeᵢ]| indicates that the button at index |indexᵢ| was pressed at time
// |timeᵢ|.
//
//  • The array is sorted in increasing order of |time|.
//
//  • The time taken to press a button is the difference in time between
//  consecutive button presses. The time for the first button is simply the time
//  at which it was pressed.
// Return the |index| of the button that took the longest time to push. If
// multiple buttons have the same longest time, return the button with the
// smallest |index|.
//
//

LEETCODE_BEGIN_RESOLVING(3386, ButtonWithLongestPushTime, Solution);

class Solution {
public:
  int buttonWithLongestTime(vector<vector<int>> &events) {
    int res     = 1e9;
    int pressed = 0;
    int prev_t  = 0;
    for (auto &v : events) {
      auto idx = v[0];
      auto t   = v[1];

      if (pressed < (t - prev_t)) {
        pressed = t - prev_t;
        res     = idx;
      } else if (pressed == (t - prev_t)) {
        pressed = t - prev_t;
        res     = min(res, idx);
      }
      prev_t = t;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= events.length <= 1000|
// * |events[i] == [indexᵢ, timeᵢ]|
// * |1 <= indexᵢ, timeᵢ <= 10⁵|
// * The input is generated such that |events| is sorted in increasing order of
// |timeᵢ|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: events = [[1,2],[2,5],[3,9],[1,15]]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(3386, ButtonWithLongestPushTime, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> events   = {
      {1,  2},
      {2,  5},
      {3,  9},
      {1, 15}
  };
  int expect = 1;
  int actual = solution->buttonWithLongestTime(events);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: events = [[10,5],[1,7]]
// Output: 10
//

LEETCODE_SOLUTION_UNITTEST(3386, ButtonWithLongestPushTime, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> events   = {
      {10, 5},
      { 1, 7}
  };
  int expect = 10;
  int actual = solution->buttonWithLongestTime(events);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [[10,4],[1,6],[7,14]]
// Output: 7
//

LEETCODE_SOLUTION_UNITTEST(3386, ButtonWithLongestPushTime, extra_testcase_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> events   = {
      {10,  4},
      { 1,  6},
      { 7, 14}
  };
  int expect = 7;
  int actual = solution->buttonWithLongestTime(events);
  LCD_EXPECT_EQ(expect, actual);
}

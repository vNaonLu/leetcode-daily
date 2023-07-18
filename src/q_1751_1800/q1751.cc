// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Number of Events That Can Be Attended II
//
// https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended-ii/
//
// Question ID: 1751
// Difficult  : Hard
// Solve Date : 2023/07/15 21:55

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1751. Maximum Number of Events That Can Be Attended II|:
//
// You are given an array of |events| where |events[i] = [startDayᵢ, endDayᵢ,
// valueᵢ]|. The |iᵗʰ| event starts at |startDayᵢ|_{ }and ends at |endDayᵢ|, and
// if you attend this event, you will receive a value of |valueᵢ|. You are also
// given an integer |k| which represents the maximum number of events you can
// attend. You can only attend one event at a time. If you choose to attend an
// event, you must attend the entire event. Note that the end day is inclusive:
// that is, you cannot attend two events where one of them starts and the other
// ends on the same day. Return the maximum sum of values that you can receive
// by attending events.
//
//

LEETCODE_BEGIN_RESOLVING(1751, MaximumNumberOfEventsThatCanBeAttendedII,
                         Solution);

class Solution {
public:
  int maxValue(vector<vector<int>> &events, int k) {
    sort(events.begin(), events.end());
    vector<vector<int>> dp(events.size(), vector<int>(k + 1, -1));
    return help(events, k, 0, dp);
  }

private:
  int help(vector<vector<int>> &e, int k, int i, vector<vector<int>> &dp) {
    if (i >= e.size()) {
      return 0;
    }

    if (dp[i][k] != -1) {
      return dp[i][k];
    }

    int res = help(e, k, i + 1, dp);
    if (k) {
      vector<int> tmp = {e[i][1], numeric_limits<int>::max(),
                         numeric_limits<int>::max()};
      int         in  = upper_bound(e.begin(), e.end(), tmp) - e.begin();
      res             = max(res, e[i][2] + help(e, k - 1, in, dp));
    }
    return dp[i][k] = res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= k <= events.length|
// * |1 <= k * events.length <= 10⁶|
// * |1 <= startDayᵢ <= endDayᵢ <= 10⁹|
// * |1 <= valueᵢ <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: events = [[1,2,4],[3,4,3],[2,3,1]], k = 2
// Output: 7
//
// Choose the green events, 0 and 1 (0-indexed) for a total value of 4 + 3 = 7.

LEETCODE_SOLUTION_UNITTEST(1751, MaximumNumberOfEventsThatCanBeAttendedII,
                           example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> events   = {
      {1, 2, 4},
      {3, 4, 3},
      {2, 3, 1}
  };
  int k      = 2;
  int expect = 7;
  int actual = solution->maxValue(events, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: events = [[1,2,4],[3,4,3],[2,3,10]], k = 2
// Output: 10
//
// Choose event 2 for a total value of 10.
// Notice that you cannot attend any other event as they overlap, and that you
// do not have to attend k events.

LEETCODE_SOLUTION_UNITTEST(1751, MaximumNumberOfEventsThatCanBeAttendedII,
                           example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> events   = {
      {1, 2,  4},
      {3, 4,  3},
      {2, 3, 10}
  };
  int k      = 2;
  int expect = 10;
  int actual = solution->maxValue(events, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: events = [[1,1,1],[2,2,2],[3,3,3],[4,4,4]], k = 3
// Output: 9
//
// Although the events do not overlap, you can only attend 3 events. Pick the
// highest valued three.

LEETCODE_SOLUTION_UNITTEST(1751, MaximumNumberOfEventsThatCanBeAttendedII,
                           example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> events   = {
      {1, 1, 1},
      {2, 2, 2},
      {3, 3, 3},
      {4, 4, 4}
  };
  int k      = 3;
  int expect = 9;
  int actual = solution->maxValue(events, k);
  LCD_EXPECT_EQ(expect, actual);
}

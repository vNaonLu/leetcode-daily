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
    sort(
        events.begin(), events.end(),
        [](const vector<int> &a, const vector<int> &b) { return a[1] < b[1]; });
    int                 n = events.size();
    vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));

    for (int i = 1; i <= n; ++i) {
      int prev = binarySearch(events, events[i - 1][0]);

      for (int j = 1; j <= k; ++j) {
        dp[i][j] = max(dp[i - 1][j], dp[prev + 1][j - 1] + events[i - 1][2]);
      }
    }

    return dp[n][k];
  }

private:
  int binarySearch(vector<vector<int>> &events, int currentStart) {
    int left = 0, right = events.size() - 1;
    int result = -1;

    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (events[mid][1] < currentStart) {
        result = mid;
        left   = mid + 1;
      } else {
        right = mid - 1;
      }
    }

    return result;
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

// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Two Best Non-Overlapping Events
//
// https://leetcode.com/problems/two-best-non-overlapping-events/
//
// Question ID: 2054
// Difficult  : Medium
// Solve Date : 2024/12/08 14:10

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2054. Two Best Non-Overlapping Events|:
//
// You are given a 0-indexed 2D integer array of |events| where |events[i] =
// [startTimeᵢ, endTimeᵢ, valueᵢ]|. The |iᵗʰ| event starts at |startTimeᵢ|_{
// }and ends at |endTimeᵢ|, and if you attend this event, you will receive a
// value of |valueᵢ|. You can choose at most two non-overlapping events to
// attend such that the sum of their values is maximized. Return this maximum
// sum. Note that the start time and end time is inclusive: that is, you cannot
// attend two events where one of them starts and the other ends at the same
// time. More specifically, if you attend an event with end time |t|, the next
// event must start at or after |t + 1|.
//
//

LEETCODE_BEGIN_RESOLVING(2054, TwoBestNonOverlappingEvents, Solution);

class Solution {
public:
  int maxTwoEvents(vector<vector<int>> &events) {
    int n = events.size();
    sort(events.begin(), events.end(),
         [](const auto &a, const auto &b) { return a[0] < b[0]; });

    vector<int> suffix(n);
    suffix[n - 1] = events[n - 1][2];

    for (int i = n - 2; i >= 0; --i) {
      suffix[i] = max(events[i][2], suffix[i + 1]);
    }

    int res = 0;
    for (int i = 0; i < n; ++i) {
      int lo   = i + 1;
      int hi   = n - 1;
      int next = -1;

      while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (events[mid][0] > events[i][1]) {
          next = mid;
          hi   = mid - 1;
        } else {
          lo = mid + 1;
        }
      }

      if (next != -1) {
        res = max(res, events[i][2] + suffix[next]);
      }

      res = max(res, events[i][2]);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= events.length <= 10⁵|
// * |events[i].length == 3|
// * |1 <= startTimeᵢ <= endTimeᵢ <= 10⁹|
// * |1 <= valueᵢ <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: events = [[1,3,2],[4,5,2],[2,4,3]]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(2054, TwoBestNonOverlappingEvents, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> events   = {
      {1, 3, 2},
      {4, 5, 2},
      {2, 4, 3}
  };
  int expect = 4;
  int actual = solution->maxTwoEvents(events);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: events = [[1,3,2],[4,5,2],[1,5,5]]
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(2054, TwoBestNonOverlappingEvents, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> events   = {
      {1, 3, 2},
      {4, 5, 2},
      {1, 5, 5}
  };
  int expect = 5;
  int actual = solution->maxTwoEvents(events);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: events = [[1,5,3],[1,5,1],[6,6,5]]
// Output: 8
//

LEETCODE_SOLUTION_UNITTEST(2054, TwoBestNonOverlappingEvents, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> events   = {
      {1, 5, 3},
      {1, 5, 1},
      {6, 6, 5}
  };
  int expect = 8;
  int actual = solution->maxTwoEvents(events);
  LCD_EXPECT_EQ(expect, actual);
}

// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Maximum Number of Events That Can Be Attended
//
// https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended/
//
// Question ID: 1353
// Difficult  : Medium
// Solve Date : 2025/07/07 19:02

#include <algorithm>
#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1353. Maximum Number of Events That Can Be Attended|:
//
// You are given an array of |events| where |events[i] = [startDayᵢ, endDayᵢ]|.
// Every event |i| starts at |startDayᵢ|_{ }and ends at |endDayᵢ|. You can
// attend an event |i| at any day |d| where |startTimeᵢ <= d <= endTimeᵢ|. You
// can only attend one event at any time |d|. Return the maximum number of
// events you can attend.
//
//

LEETCODE_BEGIN_RESOLVING(1353, MaximumNumberOfEventsThatCanBeAttended,
                         Solution);

class Solution {
public:
  int maxEvents(vector<vector<int>> &events) {
    sort(events.begin(), events.end());
    priority_queue<int, vector<int>, greater<int>> heap;
    int                                            i    = 0;
    int                                            n    = events.size();
    int                                            res  = 0;
    int                                            last = 0;
    for (auto &e : events) {
      last = max(last, e[1]);
    }

    for (int d = 1; d <= last; ++d) {
      while (i < n && events[i][0] == d) {
        heap.push(events[i][1]);
        ++i;
      }
      while (!heap.empty() && heap.top() < d) {
        heap.pop();
      }

      if (!heap.empty()) {
        heap.pop();
        ++res;
      }

      if (i == n && heap.empty()) {
        break;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= events.length <= 10⁵|
// * |events[i].length == 2|
// * |1 <= startDayᵢ <= endDayᵢ <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: events = [[1,2],[2,3],[3,4]]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(1353, MaximumNumberOfEventsThatCanBeAttended,
                           example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> events   = {
      {1, 2},
      {2, 3},
      {3, 4}
  };
  int expect = 3;
  int actual = solution->maxEvents(events);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: events= [[1,2],[2,3],[3,4],[1,2]]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(1353, MaximumNumberOfEventsThatCanBeAttended,
                           example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> events   = {
      {1, 2},
      {2, 3},
      {3, 4},
      {1, 2}
  };
  int expect = 4;
  int actual = solution->maxEvents(events);
  LCD_EXPECT_EQ(expect, actual);
}

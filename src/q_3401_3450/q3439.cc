// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Reschedule Meetings for Maximum Free Time I
//
// https://leetcode.com/problems/reschedule-meetings-for-maximum-free-time-i/
//
// Question ID: 3439
// Difficult  : Medium
// Solve Date : 2025/07/09 12:14

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3439. Reschedule Meetings for Maximum Free Time I|:
//
// You are given an integer |eventTime| denoting the duration of an event, where
// the event occurs from time |t = 0| to time |t = eventTime|. You are also
// given two integer arrays |startTime| and |endTime|, each of length |n|. These
// represent the start and end time of |n| non-overlapping meetings, where the
// |iᵗʰ| meeting occurs during the time |[startTime[i], endTime[i]]|. You can
// reschedule at most |k| meetings by moving their start time while maintaining
// the same duration, to maximize the longest continuous period of free time
// during the event. The relative order of all the meetings should stay the same
// and they should remain non-overlapping. Return the maximum amount of free
// time possible after rearranging the meetings. Note that the meetings can not
// be rescheduled to a time outside the event.
//
//

LEETCODE_BEGIN_RESOLVING(3439, RescheduleMeetingsForMaximumFreeTimeI, Solution);

class Solution {
public:
  int maxFreeTime(int eventTime, int k, vector<int> &startTime,
                  vector<int> &endTime) {
    int         n = startTime.size();
    vector<int> gap(n + 1);
    for (int i = 1; i < n; ++i) {
      gap[i] = startTime[i] - endTime[i - 1];
    }
    gap[0] = startTime[0];
    gap[n] = eventTime - endTime[n - 1];

    int i   = 0;
    int j   = k;
    int res = 0;
    int sum = 0;
    for (int w = i; w <= n && w <= j; ++w) {
      sum += gap[w];
    }
    res = max(res, sum);

    while (j < n) {
      sum -= gap[i++];
      sum += gap[++j];
      res = max(res, sum);
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= eventTime <= 10⁹|
// * |n == startTime.length == endTime.length|
// * |2 <= n <= 10⁵|
// * |1 <= k <= n|
// * |0 <= startTime[i] < endTime[i] <= eventTime|
// * |endTime[i] <= startTime[i + 1]| where |i| lies in the range |[0, n - 2]|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: eventTime = 5, k = 1, startTime = [1,3], endTime = [2,5]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3439, RescheduleMeetingsForMaximumFreeTimeI,
                           example_1) {
  auto        solution  = MakeSolution();
  int         eventTime = 5;
  int         k         = 1;
  vector<int> startTime = {1, 3};
  vector<int> endTime   = {2, 5};
  int         expect    = 2;
  int         actual = solution->maxFreeTime(eventTime, k, startTime, endTime);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: eventTime = 10, k = 1, startTime = [0,2,9], endTime = [1,4,10]
// Output: 6
//

LEETCODE_SOLUTION_UNITTEST(3439, RescheduleMeetingsForMaximumFreeTimeI,
                           example_2) {
  auto        solution  = MakeSolution();
  int         eventTime = 10;
  int         k         = 1;
  vector<int> startTime = {0, 2, 9};
  vector<int> endTime   = {1, 4, 10};
  int         expect    = 6;
  int         actual = solution->maxFreeTime(eventTime, k, startTime, endTime);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: eventTime = 5, k = 2, startTime = [0,1,2,3,4], endTime = [1,2,3,4,5]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(3439, RescheduleMeetingsForMaximumFreeTimeI,
                           example_3) {
  auto        solution  = MakeSolution();
  int         eventTime = 5;
  int         k         = 2;
  vector<int> startTime = {0, 1, 2, 3, 4};
  vector<int> endTime   = {1, 2, 3, 4, 5};
  int         expect    = 0;
  int         actual = solution->maxFreeTime(eventTime, k, startTime, endTime);
  LCD_EXPECT_EQ(expect, actual);
}

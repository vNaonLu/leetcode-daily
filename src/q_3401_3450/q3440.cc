// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Reschedule Meetings for Maximum Free Time II
//
// https://leetcode.com/problems/reschedule-meetings-for-maximum-free-time-ii/
//
// Question ID: 3440
// Difficult  : Medium
// Solve Date : 2025/07/10 21:42

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3440. Reschedule Meetings for Maximum Free Time II|:
//
//

LEETCODE_BEGIN_RESOLVING(3440, RescheduleMeetingsForMaximumFreeTimeII,
                         Solution);
class Solution {
public:
  int maxFreeTime(int eventTime, vector<int> &startTime, vector<int> &endTime) {
    vector<int> gap(1, startTime[0]);
    for (int i = 1; i < startTime.size(); ++i)
      gap.push_back(startTime[i] - endTime[i - 1]);
    gap.push_back(eventTime - endTime.back());

    vector<int> largestRight(gap.size(), 0);
    for (int i = gap.size() - 2; i >= 0; --i)
      largestRight[i] = max(largestRight[i + 1], gap[i + 1]);

    int ans = 0, largestLeft = 0;
    for (int i = 1; i < gap.size(); ++i) {
      int curGap = endTime[i - 1] - startTime[i - 1];
      if (curGap <= max(largestLeft, largestRight[i]))
        ans = max(ans, gap[i - 1] + gap[i] + curGap);
      ans         = max(ans, gap[i - 1] + gap[i]);
      largestLeft = max(largestLeft, gap[i - 1]);
    }
    return ans;
  }
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= eventTime <= 10⁹|
// * |n == startTime.length == endTime.length|
// * |2 <= n <= 10⁵|
// * |0 <= startTime[i] < endTime[i] <= eventTime|
// * |endTime[i] <= startTime[i + 1]| where |i| lies in the range |[0, n - 2]|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: eventTime = 5, startTime = [1,3], endTime = [2,5]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3440, RescheduleMeetingsForMaximumFreeTimeII,
                           example_1) {
  auto        solution  = MakeSolution();
  int         eventTime = 5;
  vector<int> startTime = {1, 3};
  vector<int> endTime   = {2, 5};
  int         expect    = 2;
  int         actual    = solution->maxFreeTime(eventTime, startTime, endTime);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: eventTime = 10, startTime = [0,7,9], endTime = [1,8,10]
// Output: 7
//

LEETCODE_SOLUTION_UNITTEST(3440, RescheduleMeetingsForMaximumFreeTimeII,
                           example_2) {
  auto        solution  = MakeSolution();
  int         eventTime = 10;
  vector<int> startTime = {0, 7, 9};
  vector<int> endTime   = {1, 8, 10};
  int         expect    = 7;
  int         actual    = solution->maxFreeTime(eventTime, startTime, endTime);
  LCD_EXPECT_EQ(expect, actual);
}

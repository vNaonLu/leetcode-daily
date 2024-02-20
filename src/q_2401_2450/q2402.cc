// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Meeting Rooms III
//
// https://leetcode.com/problems/meeting-rooms-iii/
//
// Question ID: 2402
// Difficult  : Hard
// Solve Date : 2024/02/18 16:15

#include <algorithm>
#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2402. Meeting Rooms III|:
//
// You are given an integer |n|. There are |n| rooms numbered from |0| to |n -
// 1|. You are given a 2D integer array |meetings| where |meetings[i] = [startᵢ,
// endᵢ]| means that a meeting will be held during the half-closed time interval
// |[startᵢ, endᵢ)|. All the values of |startᵢ| are unique. Meetings are
// allocated to rooms in the following manner:
//
//  1. Each meeting will take place in the unused room with the lowest number.
//
//  2. If there are no available rooms, the meeting will be delayed until a room
//  becomes free. The delayed meeting should have the same duration as the
//  original meeting.
//
//  3. When a room becomes unused, meetings that have an earlier original start
//  time should be given the room.
// Return the number of the room that held the most meetings. If there are
// multiple rooms, return the room with the lowest number. A half-closed
// interval |[a, b)| is the interval between |a| and |b| including |a| and not
// including |b|.
//
//

LEETCODE_BEGIN_RESOLVING(2402, MeetingRoomsIII, Solution);

class Solution {
public:
  int mostBooked(int n, vector<vector<int>> &meetings) {
    vector<int>                                    res(n, 0);
    priority_queue<int, vector<int>, greater<int>> avail;
    priority_queue<pair<int64_t, int>, vector<pair<int64_t, int>>,
                   greater<pair<int64_t, int>>>
        busy;

    for (int i = 0; i < n; ++i) {
      avail.emplace(i);
    }

    sort(meetings.begin(), meetings.end());

    for (auto &v : meetings) {
      int start = v[0];
      int end   = v[1];

      while (busy.size() > 0 && busy.top().first <= start) {
        avail.emplace(busy.top().second);
        busy.pop();
      }

      if (avail.size() > 0) {
        int t = avail.top();
        avail.pop();
        ++res[t];
        busy.emplace(end, t);
      } else {
        auto [end1, index] = busy.top();
        busy.pop();

        ++res[index];
        busy.emplace(end1 + end - start, index);
      }
    }

    return max_element(res.begin(), res.end()) - res.begin();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 100|
// * |1 <= meetings.length <= 10⁵|
// * |meetings[i].length == 2|
// * |0 <= startᵢ < endᵢ <= 5 * 10⁵|
// * All the values of |startᵢ| are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 2, meetings = [[0,10],[1,5],[2,7],[3,4]]
// Output: 0
//
// - At time 0, both rooms are not being used. The first meeting starts in room
// 0.
// - At time 1, only room 1 is not being used. The second meeting starts in
// room 1.
// - At time 2, both rooms are being used. The third meeting is delayed.
// - At time 3, both rooms are being used. The fourth meeting is delayed.
// - At time 5, the meeting in room 1 finishes. The third meeting starts in room
// 1 for the time period [5,10).
// - At time 10, the meetings in both rooms finish. The fourth meeting starts in
// room 0 for the time period [10,11). Both rooms 0 and 1 held 2 meetings, so we
// return 0.

LEETCODE_SOLUTION_UNITTEST(2402, MeetingRoomsIII, example_1) {
  auto                solution = MakeSolution();
  int                 n        = 2;
  vector<vector<int>> meetings = {
      {0, 10},
      {1,  5},
      {2,  7},
      {3,  4}
  };
  int expect = 0;
  int actual = solution->mostBooked(n, meetings);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 3, meetings = [[1,20],[2,10],[3,5],[4,9],[6,8]]
// Output: 1
//
// - At time 1, all three rooms are not being used. The first meeting starts in
// room 0.
// - At time 2, rooms 1 and 2 are not being used. The second meeting starts in
// room 1.
// - At time 3, only room 2 is not being used. The third meeting starts in
// room 2.
// - At time 4, all three rooms are being used. The fourth meeting is delayed.
// - At time 5, the meeting in room 2 finishes. The fourth meeting starts in
// room 2 for the time period [5,10).
// - At time 6, all three rooms are being used. The fifth meeting is delayed.
// - At time 10, the meetings in rooms 1 and 2 finish. The fifth meeting starts
// in room 1 for the time period [10,12). Room 0 held 1 meeting while rooms 1
// and 2 each held 2 meetings, so we return 1.

LEETCODE_SOLUTION_UNITTEST(2402, MeetingRoomsIII, example_2) {
  auto                solution = MakeSolution();
  int                 n        = 3;
  vector<vector<int>> meetings = {
      {1, 20},
      {2, 10},
      {3,  5},
      {4,  9},
      {6,  8}
  };
  int expect = 1;
  int actual = solution->mostBooked(n, meetings);
  LCD_EXPECT_EQ(expect, actual);
}

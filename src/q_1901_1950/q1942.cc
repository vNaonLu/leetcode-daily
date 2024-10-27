// Copyright 2024 Naon Lu
//
// This file describes the solution of
// The Number of the Smallest Unoccupied Chair
//
// https://leetcode.com/problems/the-number-of-the-smallest-unoccupied-chair/
//
// Question ID: 1942
// Difficult  : Medium
// Solve Date : 2024/10/11 21:44

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1942. The Number of the Smallest Unoccupied Chair|:
//
// There is a party where |n| friends numbered from |0| to |n - 1| are
// attending. There is an infinite number of chairs in this party that are
// numbered from |0| to |infinity|. When a friend arrives at the party, they sit
// on the unoccupied chair with the smallest number.
//
//  • For example, if chairs |0|, |1|, and |5| are occupied when a friend comes,
//  they will sit on chair number |2|.
// When a friend leaves the party, their chair becomes unoccupied at the moment
// they leave. If another friend arrives at that same moment, they can sit in
// that chair. You are given a 0-indexed 2D integer array |times| where
// |times[i] = [arrivalᵢ, leavingᵢ]|, indicating the arrival and leaving times
// of the |iᵗʰ| friend respectively, and an integer |targetFriend|. All arrival
// times are distinct. Return the chair number that the friend numbered
// |targetFriend| will sit on.
//
//

LEETCODE_BEGIN_RESOLVING(1942, TheNumberOfTheSmallestUnoccupiedChair, Solution);

class Solution {
public:
  int smallestChair(vector<vector<int>> &times, int targetFriend) {
    int                               n = times.size();
    vector<pair<pair<int, int>, int>> events;
    for (int i = 0; i < n; i++) {
      events.push_back({
          {times[i][0], 1},
          i
      });
      events.push_back({
          {times[i][1], -1},
          i
      });
    }

    sort(events.begin(), events.end());

    vector<int>                                    assignedChairs(n, -1);
    priority_queue<int, vector<int>, greater<int>> availableChairs;

    for (int i = 0; i < n; i++) {
      availableChairs.push(i);
    }

    for (auto &event : events) {
      int type   = event.first.second;
      int person = event.second;

      if (person == targetFriend && type == 1) {
        return availableChairs.top();
      }

      if (type == 1) {
        assignedChairs[person] = availableChairs.top();
        availableChairs.pop();
      } else {
        availableChairs.push(assignedChairs[person]);
        assignedChairs[person] = -1;
      }
    }

    return -1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == times.length|
// * |2 <= n <= 10⁴|
// * |times[i].length == 2|
// * |1 <= arrivalᵢ < leavingᵢ <= 10⁵|
// * |0 <= targetFriend <= n - 1|
// * Each |arrivalᵢ| time is distinct.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: times = [[1,4],[2,3],[4,6]], targetFriend = 1
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(1942, TheNumberOfTheSmallestUnoccupiedChair,
                           example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> times    = {
      {1, 4},
      {2, 3},
      {4, 6}
  };
  int targetFriend = 1;
  int expect       = 1;
  int actual       = solution->smallestChair(times, targetFriend);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: times = [[3,10],[1,5],[2,6]], targetFriend = 0
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(1942, TheNumberOfTheSmallestUnoccupiedChair,
                           example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> times    = {
      {3, 10},
      {1,  5},
      {2,  6}
  };
  int targetFriend = 0;
  int expect       = 2;
  int actual       = solution->smallestChair(times, targetFriend);
  LCD_EXPECT_EQ(expect, actual);
}

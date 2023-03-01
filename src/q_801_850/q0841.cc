// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Keys and Rooms
//
// https://leetcode.com/problems/keys-and-rooms/
//
// Question ID: 841
// Difficult  : Medium
// Solve Date : 2021/10/07 10:57

#include <iosfwd>
#include <stack>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |841. Keys and Rooms|:
//
// There are |n| rooms labeled from |0| to |n - 1| and all the rooms are locked
// except for room |0|. Your goal is to visit all the rooms. However, you cannot
// enter a locked room without having its key. When you visit a room, you may
// find a set of distinct keys in it. Each key has a number on it, denoting
// which room it unlocks, and you can take all of them with you to unlock the
// other rooms. Given an array |rooms| where |rooms[i]| is the set of keys that
// you can obtain if you visited room |i|, return |true| if you can visit all
// the rooms, or |false| otherwise.  
//

LEETCODE_BEGIN_RESOLVING(841, KeysAndRooms, Solution);

class Solution {
public:
  bool canVisitAllRooms(vector<vector<int>> &rooms) {
    int                n = rooms.size();
    stack<vector<int>> keys;
    vector<int>        reachable(n, false);
    reachable[0] = true;
    keys.push(rooms[0]);
    while (!keys.empty()) {
      auto rms = keys.top();
      keys.pop();
      for (auto it = rms.begin(); it != rms.end(); ++it) {
        if (!reachable[*it]) {
          reachable[*it] = true;
          keys.push(rooms[*it]);
        }
      }
    }
    for (const auto &r : reachable)
      if (!r)
        return false;
    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == rooms.length|
// * |2 <= n <= 1000|
// * |0 <= rooms[i].length <= 1000|
// * |1 <= sum(rooms[i].length) <= 3000|
// * |0 <= rooms[i][j] < n|
// * All the values of |rooms[i]| are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: rooms = [[1],[2],[3],[]]
// Output: true
//
// We visit room 0 and pick up key 1.
// We then visit room 1 and pick up key 2.
// We then visit room 2 and pick up key 3.
// We then visit room 3.
// Since we were able to visit every room, we return true.

LEETCODE_SOLUTION_UNITTEST(841, KeysAndRooms, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> rooms    = {{1}, {2}, {3}, {}};
  bool                expect   = true;
  bool                actual   = solution->canVisitAllRooms(rooms);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: rooms = [[1,3],[3,0,1],[2],[0]]
// Output: false
//
// We can not enter room number 2 since the only key that unlocks it is in that
// room.

LEETCODE_SOLUTION_UNITTEST(841, KeysAndRooms, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> rooms    = {
      {1, 3},
      {3, 0, 1},
      {2},
      {0}
  };
  bool expect = false;
  bool actual = solution->canVisitAllRooms(rooms);
  LCD_EXPECT_EQ(expect, actual);
}

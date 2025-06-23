// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Find Minimum Time to Reach Last Room I
//
// https://leetcode.com/problems/find-minimum-time-to-reach-last-room-i/
//
// Question ID: 3341
// Difficult  : Medium
// Solve Date : 2025/05/07 20:16

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3341. Find Minimum Time to Reach Last Room I|:
//
// There is a dungeon with |n x m| rooms arranged as a grid.
// You are given a 2D array |moveTime| of size |n x m|, where |moveTime[i][j]|
// represents the minimum time in seconds when you can start moving to that
// room. You start from the room |(0, 0)| at time |t = 0| and can move to an
// adjacent room. Moving between adjacent rooms takes exactly one second. Return
// the minimum time to reach the room |(n - 1, m - 1)|. Two rooms are adjacent
// if they share a common wall, either horizontally or vertically.
//
//

LEETCODE_BEGIN_RESOLVING(3341, FindMinimumTimeToReachLastRoomI, Solution);

class Solution {
public:
  int minTimeToReach(vector<vector<int>> &moveTime) {
    int                 n = moveTime.size(), m = moveTime[0].size();
    vector<vector<int>> dp(n, vector<int>(m, numeric_limits<int>::max()));
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> minh;
    minh.push({0, 0, 0});
    moveTime[0][0] = 0;

    vector<vector<int>> directions = {
        { 1,  0},
        { 0,  1},
        {-1,  0},
        { 0, -1}
    };
    while (!minh.empty()) {
      auto current = minh.top();
      minh.pop();
      int currTime = current[0];
      int currRow  = current[1];
      int currCol  = current[2];
      if (currTime >= dp[currRow][currCol])
        continue;
      if (currRow == n - 1 && currCol == m - 1)
        return currTime;
      dp[currRow][currCol] = currTime;

      for (auto &direction : directions) {
        int nextRow = currRow + direction[0];
        int nextCol = currCol + direction[1];
        if (nextRow >= 0 && nextRow < n && nextCol >= 0 && nextCol < m &&
            dp[nextRow][nextCol] == numeric_limits<int>::max()) {
          int nextTime = max(moveTime[nextRow][nextCol], currTime) + 1;
          minh.push({nextTime, nextRow, nextCol});
        }
      }
    }
    return -1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= n == moveTime.length <= 50|
// * |2 <= m == moveTime[i].length <= 50|
// * |0 <= moveTime[i][j] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: moveTime = [[0,4],[4,4]]
// Output: 6
//

LEETCODE_SOLUTION_UNITTEST(3341, FindMinimumTimeToReachLastRoomI, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> moveTime = {
      {0, 4},
      {4, 4}
  };
  int expect = 6;
  int actual = solution->minTimeToReach(moveTime);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: moveTime = [[0,0,0],[0,0,0]]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(3341, FindMinimumTimeToReachLastRoomI, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> moveTime = {
      {0, 0, 0},
      {0, 0, 0}
  };
  int expect = 3;
  int actual = solution->minTimeToReach(moveTime);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: moveTime = [[0,1],[1,2]]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(3341, FindMinimumTimeToReachLastRoomI, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> moveTime = {
      {0, 1},
      {1, 2}
  };
  int expect = 3;
  int actual = solution->minTimeToReach(moveTime);
  LCD_EXPECT_EQ(expect, actual);
}

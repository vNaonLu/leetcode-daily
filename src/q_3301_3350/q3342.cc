// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Find Minimum Time to Reach Last Room II
//
// https://leetcode.com/problems/find-minimum-time-to-reach-last-room-ii/
//
// Question ID: 3342
// Difficult  : Medium
// Solve Date : 2025/05/08 14:03

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3342. Find Minimum Time to Reach Last Room II|:
//
//

LEETCODE_BEGIN_RESOLVING(3342, FindMinimumTimeToReachLastRoomII, Solution);

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
          int cost     = (currRow + currCol) % 2 + 1;
          int start    = max(moveTime[nextRow][nextCol], currTime);
          int nextTime = start + cost;
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
// * |2 <= n == moveTime.length <= 750|
// * |2 <= m == moveTime[i].length <= 750|
// * |0 <= moveTime[i][j] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

LEETCODE_SOLUTION_UNITTEST(3342, FindMinimumTimeToReachLastRoomII, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> moveTime = {
      {0, 4},
      {4, 4}
  };
  int expect = 7;
  int actual = solution->minTimeToReach(moveTime);
  LCD_EXPECT_EQ(expect, actual);
}

LEETCODE_SOLUTION_UNITTEST(3342, FindMinimumTimeToReachLastRoomII, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> moveTime = {
      {0, 0, 0, 0},
      {0, 0, 0, 0}
  };
  int expect = 6;
  int actual = solution->minTimeToReach(moveTime);
  LCD_EXPECT_EQ(expect, actual);
}

LEETCODE_SOLUTION_UNITTEST(3342, FindMinimumTimeToReachLastRoomII, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> moveTime = {
      {0, 1},
      {1, 2}
  };
  int expect = 4;
  int actual = solution->minTimeToReach(moveTime);
  LCD_EXPECT_EQ(expect, actual);
}
